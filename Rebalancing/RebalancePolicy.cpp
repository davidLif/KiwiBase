/*
 * RebalancePolicy.cpp
 *
 *  Created on: Mar 13, 2018
 *      Author: david
 */

#include "RebalancePolicy.h"
#include "../KvChunck.h"

template <class K, class V>
RebalancePolicy<K,V>::RebalancePolicy(KvChunck<K,V> * startChunk) {
	m_firstChunk = startChunk;
	m_lastChunk = startChunk;
	m_chunksInRange = 1;
	m_itemsInRange = startChunk->getCompactedCount();
}

template <class K, class V>
KvChunck<K,V> * RebalancePolicy<K,V>::findNextCandidate() {
	updateRangeView();

	if (m_chunksInRange >= REBALANCE_POLICY_REBALANCE_SIZE) {
		return NULL;
	}

	KvChunck<K,V> * next = m_lastChunk->m_next;

	if (next != NULL && next->isRebalanceCandidate()) {
		KvChunck<K,V> * candidate = next;

		int newItems = next->getCompactedCount();
		int totalItems = m_itemsInRange + newItems;
		int chunksAfterMerge = (int)ceil(((double)totalItems)/(m_maxAfterMergeItems));

		// if the the chosen chunk may reduce the number of chunks -- return it as candidate
		if( chunksAfterMerge < m_chunksInRange + 1) {
			return candidate;
		} else {
			return NULL;
		}
	}
	else {
		return NULL;
	}

	return NULL;
}

template <class K, class V>
void RebalancePolicy<K,V>::updateRangeView() {
	updateRangeFwd();
	//No prev and backwards functions, because in the java implementation we get null and always ignore
}

template <class K, class V>
KvChunck<K,V> * RebalancePolicy<K,V>::getFirstChunkInRange() {
	return m_firstChunk;
}

template <class K, class V>
void RebalancePolicy<K,V>::updateRangeFwd() {
	while (true) {
		KvChunck<K,V> * next = m_lastChunk->m_next;
		if (next == NULL || !next->isEngagedToGivenRebalancer(this)) {
			break;
		}
		else {
			m_lastChunk = next;
			m_itemsInRange += m_lastChunk->getCompactedCount();
			m_chunksInRange++;
		}
	}
}

template <class K, class V>
RebalancePolicy<K,V>::~RebalancePolicy() {
	//The policy contains only primitive-type fields
}
