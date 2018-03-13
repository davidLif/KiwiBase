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
	return NULL;
}

template <class K, class V>
void RebalancePolicy<K,V>::updateRangeView() {
}

template <class K, class V>
KvChunck<K,V> * RebalancePolicy<K,V>::getFirstChunkInRange() {
	return NULL;
}

template <class K, class V>
RebalancePolicy<K,V>::~RebalancePolicy() {
}
