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
KvChunck<K,V>::~KvChunck() {

	delete[] m_ppa;
}
