/*
 * KvChunck.h
 *
 *  Created on: Feb 22, 2018
 *      Author: david
 */

#ifndef KVCHUNCK_H_
#define KVCHUNCK_H_

#include <atomic>
#include <cstddef>
#include "Struct_KeychunckMeta.h"
#include "PendingPuts/PutPendingItem.h"
#include "Utils/MarkableReference.h"

//forward decleration
template <class K, class V> class Rebalance;

using namespace std;

#define CHUNK_EMPTY_VERSION 0
#define CHUNK_FREEZE_VERSION 1
#define CHUNK_CANCEL_REMOVE_NEXT_VERSION -1

#define VALUES_ARR_BYTES_SIZE 40 //This values tells us how many bytes m_valuesArr will take

#define CHUNK_ORDER_SIZE 4

#define CHUNK_MAX_ITEMS 4500
#define CHUNK_ALLOW_DUPS 1 //true



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

	MarkableReference<KvChunck<K,V>> m_next;
	bool m_isNextMutable; //called "mark" in the article

	//rebalance vars
	atomic<Rebalance<K,V> *> m_rebalancer;
	atomic<int *> m_test;
	KvChunck<K,V> * m_parent;

	PutPendingItem * m_ppa;

	//Stats fields
	atomic<int> m_orderIndex;
	atomic<int> m_dupsCount;

public:
	KvChunck(K minKey, int maxNumOfOperatingThreads);

	int pairSpaceAlloc(K key, V value);
	int setPairVersion(int orderArrIndex, int version);
	void setPairInChunkSpace(int orderArrIndex, K key);

	bool findValue(K key, V * outValP);
	bool popMin(V * outValP);
	K getMinKey() { return m_minKey; };
	KvChunck<K,V> * getNextChunk() { return m_next.getRef(); };
	bool infantChunkRebalancing();

	void clearThreadPpaDecleration();

	//Rebalance methods
	KvChunck<K,V> * rebalance();
	static bool shouldRebalance(KvChunck<K,V> * chunk) {
		//TODO : move this to rebalance class
		return false;
	}
	void freeze();
	Rebalance<K,V> * engage(Rebalance<K,V> * rebalancer) {
		Rebalance<K,V> * nullRebalancer = NULL;
		m_rebalancer.compare_exchange_strong(nullRebalancer, rebalancer);
		return m_rebalancer;
	}

	int * testTest(int * input){
		int * null = NULL;
		m_test.compare_exchange_strong(null, input);
		return m_test;
	}

	//Stats function
	int getFilledCount() { return m_orderIndex/CHUNK_ORDER_SIZE; } //Number of items inserted into the chunk
	int getCompactedCount() { return getFilledCount() - m_dupsCount; } //Approximate number of items chunk may contain after compaction.
	void incDupscount() { m_dupsCount++; }


	virtual ~KvChunck();
};

#endif /* KVCHUNCK_H_ */
