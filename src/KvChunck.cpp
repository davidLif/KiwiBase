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

	m_minKey = minKey;
	kCounter = 0;
	vCounter = 0;

	m_ppa = new PutPendingItem[maxNumOfOperatingThreads];
}

template <class K, class V>
int KvChunck<K,V>::pairSpaceAlloc(K key, V value){
    // TODO
	return 1;
}

template <class K, class V>
int KvChunck<K,V>::setPairVersion(int orderArrIndex, int version) {
<<<<<<< HEAD:KvChunck.cpp
	return 1;
=======
    // TODO
    return 1;
>>>>>>> ba62069bc0b730abd9eefb785905a4437635c47e:src/KvChunck.cpp
}

template <class K, class V>
void KvChunck<K,V>::setPairInChunkSpace(int orderArrIndex, K key) {
<<<<<<< HEAD:KvChunck.cpp

=======
    // TODO
>>>>>>> ba62069bc0b730abd9eefb785905a4437635c47e:src/KvChunck.cpp
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
<<<<<<< HEAD:KvChunck.cpp
void KvChunck<K,V>::freeze() {
	//TODO
=======
void KvChunck<K,V>::clearThreadPpaDecleration() {
    // TODO
>>>>>>> ba62069bc0b730abd9eefb785905a4437635c47e:src/KvChunck.cpp
}

template <class K, class V>
KvChunck<K,V> * KvChunck<K,V>::rebalance() {
<<<<<<< HEAD:KvChunck.cpp
	return NULL;
=======
    // TODO
    return NULL;
}

template <class K, class V>
bool KvChunck<K,V>::shouldRebalance(KvChunck<K,V> * chunk) {
    // TODO
    return false;
>>>>>>> ba62069bc0b730abd9eefb785905a4437635c47e:src/KvChunck.cpp
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
