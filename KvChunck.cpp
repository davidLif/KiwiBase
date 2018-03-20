/*
 * KvChunck.cpp
 *
 *  Created on: Feb 22, 2018
 *      Author: david
 */

#include "KvChunck.h"
#include "Rebalancing/Rebalance.h"
#include "PendingPuts/PutPendingItem.h"

template class  KvChunck<unsigned int, int>;

template <class K, class V>
KvChunck<K,V>::KvChunck(K minKey, int maxNumOfOperatingThreads) {

	m_parent = NULL;
	m_minKey = minKey;
	kCounter = 0;
	vCounter = 0;

	m_maxNumOfOperatingThreads = maxNumOfOperatingThreads;
	m_ppa = new PutPendingItem[maxNumOfOperatingThreads];
}

template <class K, class V>
KvChunck<K,V>::KvChunck(KvChunck<K,V> * parent) {

	m_parent = parent;
	m_minKey = parent->m_minKey;
	kCounter = 0;
	vCounter = 0;

	m_maxNumOfOperatingThreads = parent->m_maxNumOfOperatingThreads;
	m_ppa = new PutPendingItem[m_maxNumOfOperatingThreads];
}

template <class K, class V>
int KvChunck<K,V>::pairSpaceAlloc(K key, V value){
	return 1;
}

template <class K, class V>
int KvChunck<K,V>::setPairVersion(int orderArrIndex, int version) {
	return 1;
}

template <class K, class V>
void KvChunck<K,V>::setPairInChunkSpace(int orderArrIndex, K key) {

}

template <class K, class V>
bool KvChunck<K,V>::findValue(K key, V * outValP){
	outValP = NULL;
	return false;
}

template <class K, class V>
bool KvChunck<K,V>::popMin(V * outValP){
	outValP = NULL;
	return false;
}

template <class K, class V>
void KvChunck<K,V>::freeze() {
	//TODO
}

template <class K, class V>
KvChunck<K,V> * KvChunck<K,V>::rebalance() {
	return NULL;
}

template <class K, class V>
int KvChunck<K,V>::getFirstItemOrderId() {
	return -1;
}

template <class K, class V>
int KvChunck<K,V>::copyPart(KvChunck<K,V> * sourceChunk, int orderIndex, int maxCapacity) {
	return -1;
}

template <class K, class V>
bool KvChunck<K,V>::infantChunkRebalancing(){
	if (m_parent != NULL) {
		m_parent->rebalance();
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
