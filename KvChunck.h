/*
 * KvChunck.h
 *
 *  Created on: Feb 22, 2018
 *      Author: david
 */

#ifndef KVCHUNCK_H_
#define KVCHUNCK_H_

#include <cstddef>
#include "Struct_KeychunckMeta.h"
#include "PendingPuts/PutPendingItem.h"

#define CHUNK_EMPTY_VERSION 0
#define CHUNK_FREEZE_VERSION 1
#define CHUNK_CANCEL_REMOVE_NEXT_VERSION -1

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

	//rebalance vars
	KvChunck<K,V> * m_parent;

	PutPendingItem m_ppa[];

public:
	KvChunck(K minKey, int maxNumOfOperatingThreads);

	int pairSpaceAlloc(K key, V value);
	int setPairVersion(int orderArrIndex, int version);
	void setPairInChunkSpace(int orderArrIndex, K key);

	bool findValue(K key, V * outValP);

	void clearThreadPpaDecleration();

	KvChunck<K,V> * rebalance();
	static bool shouldRebalance(KvChunck<K,V> * chunk);

	K getMinKey() { return m_minKey; };
	KvChunck<K,V> * getNextChunk() { return m_next; };
	bool infantChunkRebalancing();

	virtual ~KvChunck();
};

#endif /* KVCHUNCK_H_ */
