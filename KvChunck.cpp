/*
 * KvChunck.cpp
 *
 *  Created on: Feb 22, 2018
 *      Author: david
 */

#include "KvChunck.h"

template <class K, class V>
KvChunck<K,V>::KvChunck(K minKey, int maxNumOfOperatingThreads) {

	m_minKey = minKey;
	kCounter = 0;
	vCounter = 0;

	m_ppa = new PutPendingItem[maxNumOfOperatingThreads];
}

template <class K, class V>
int KvChunck<K,V>::pairSpaceAlloc(K key, V value){
	return 1;
}

template <class K, class V>
bool KvChunck<K,V>::findValue(K key, V * outValP){
	outValP = NULL;
	return false;
}

template <class K, class V>
bool KvChunck<K,V>::infantChunkRebalancing(){
	if (m_parent != NULL) {
		m_parent.rebalance();
		return true;
	}
	else {
		return false;
	}
}

template <class K, class V>
KvChunck<K,V>::~KvChunck() {

	delete[] m_ppa;
}
