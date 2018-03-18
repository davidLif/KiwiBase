/*
 * Rebalance.cpp
 *
 *  Created on: Mar 12, 2018
 *      Author: david
 */

#include "Rebalance.h"
#include "Compactor.h"
#include "RebalancePolicy.h"
#include "../KvChunck.h"

#define MAX_AFTER_MERGE_PART 0.5
#define COUNT_COMPACTION 0

template <class K, class V>
Rebalance<K,V>::Rebalance(KvChunck<K,V> * startingChunk) {
	m_startingChunk = startingChunk;
	m_freezedItems = false;
	m_nextChunkToEngae = startingChunk;
}

template <class K, class V>
void Rebalance<K,V>::engageChunks() {
	RebalancePolicy<K,V> policy(m_startingChunk);

	while(true) {
		KvChunck<K,V> * next = m_nextChunkToEngae;
		if (next == NULL) break;

		//TODO - we got a problem here -  when should a rebalancer be freed?
		//	even if we finished rebalancing, other might call "engageChunks" on it.
		// Suggestion A - count references?
		Rebalance<K,V> * nextEngagedRebalance = next->engage(this);
		if (nextEngagedRebalance != this && next == m_startingChunk) {
			return nextEngagedRebalance->engageChunks();
		}

		/* policy caches last discovered  interval [first, last] of engaged range
		   to get next candidate policy traverses from first backward,
		   from last forward to find non-engaged chunks connected to the engaged interval
		   if we return null here the policy decided to terminate the engagement loop */
		KvChunck<K,V> * candidate = policy->findNextCandidate();

		// if fail to CAS here, another thread has updated next candidate
		// continue to while loop and try to engage it
		m_nextChunkToEngae.compare_exchange_strong(next, candidate);
	}

	policy->updateRangeView();
	vector<KvChunck<K,V> *> engaded = createEngagedList(policy->getFirstChunkInRange());

	m_engagedChunks.compare_exchange_strong(NULL, engaded); //By java, countCompactions is always false
}

template <class K, class V>
void Rebalance<K,V>::freeze() {
	if (isFreezed()) {
		return;
	}
	else {
		vector<KvChunck<K,V> *> engagedChunks = getEngagedChunks();
		for (int i = 0; i < engagedChunks.size(); i++) {
			engagedChunks[i]->freeze();
		}

		m_freezedItems = true;
	}
}

template <class K, class V>
void Rebalance<K,V>::compact() {
	if (isCompact()) {
		return;
	}
	else {
		vector<KvChunck<K,V> *> compacted = compacting(getEngagedChunks());

		m_compactedChunks.atomic_compare_exchange_strong(NULL, compacted); // if fail here, another thread succeeded
	}
}

template <class K, class V>
vector<KvChunck<K,V> *> Rebalance<K,V>::getCompactedChunks() {
	if (!isCompact()) {
		throw std::exception("Trying to get compacted chunks before compaction stage completed");
	}
	else {
		return m_compactedChunks;
	}
}

template <class K, class V>
vector<KvChunck<K,V> *> Rebalance<K,V>::getEngagedChunks() {
	if (!isEngaged()) {
		throw std::exception("Trying to get engaged before engagement stage completed");
	}
	else {
		return m_engagedChunks;
	}
}

template <class K, class V>
vector<KvChunck<K,V> *> Rebalance<K,V>::createEngagedList(KvChunck<K,V> * firsChunkInRange) {
	vector<KvChunck<K,V> *> engadedNewLst = new vector<KvChunck<K,V> *>();

	KvChunck<K,V> * currChunkP = firsChunkInRange;
	while (currChunkP != NULL && currChunkP.isEngaded(this)) {
		engadedNewLst.insert(currChunkP);
		currChunkP = currChunkP->m_next.getRef();
	}

	if (engadedNewLst.size() == 0) {
		throw std::exception("CreateEngagedList has returned a size 0 list");
	}

	return engadedNewLst;
}

template <class K, class V>
Rebalance<K,V>::~Rebalance() {
	//The starting chunk shouldn't be destroyed here - the rebalancer chunk is created only to return the balance to the chunk
	//(Or the force , according to the ancient prophecy)
}
