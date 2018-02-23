/*
 * KvChunck.h
 *
 *  Created on: Feb 22, 2018
 *      Author: david
 */

#ifndef KVCHUNCK_H_
#define KVCHUNCK_H_

#include "Struct_KeychunckMeta.h"
#include "PendingPuts/PutPendingItem.h"

#ifndef CHUNCK_VALUEARRSIZE
#define CHUNCK_VALUEARRSIZE
#define VALUES_ARR_BYTES_SIZE 40 //This values tells us how many bytes m_valuesArr will take
#endif

template <class K, class V>
class KvChunck {
private:
	K m_minKey;

	//Both the keys and values arrays are allocated to max size according to the chunks params,
	// and the counters tells us how many indexes in the arrays are item-filled.
	KeyChunckMeta m_keysMetaArr[VALUES_ARR_BYTES_SIZE/sizeof(V)];
	int kCounter;

	V m_valuesArr[VALUES_ARR_BYTES_SIZE/sizeof(V)];
	int vCounter;

	KvChunck<K,V> * m_next;
	bool m_isNextMutable; //called "mark" in the article

	PutPendingItem m_ppa[];

public:
	KvChunck(K minKey, int maxNumOfOperatingThreads);
	K getMinKey() { return m_minKey; };
	KvChunck<K,V> * getNextChunk() { return m_next; };
	virtual ~KvChunck();
};

#endif /* KVCHUNCK_H_ */
