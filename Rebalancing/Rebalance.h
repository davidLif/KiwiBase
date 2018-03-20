/*
 * Rebalance.h
 *
 *  Created on: Mar 12, 2018
 *      Author: david
 */

#ifndef REBALANCE_H_
#define REBALANCE_H_

#include <atomic>
#include <vector>
#include <cstddef>
#include <stdexcept>

//forward decleration
template <class K, class V> class KvChunck;

using namespace std;

template <class K, class V>
class Rebalance {
private:
	KvChunck<K,V> * m_startingChunk;
	atomic<KvChunck<K,V> *> m_nextChunkToEngae;
	atomic<bool> m_freezedItems;
	atomic<vector<KvChunck<K,V> *> *> m_engagedChunks;
	atomic<vector<KvChunck<K,V> *> *> m_compactedChunks;

	vector<KvChunck<K,V> *> * createEngagedList(KvChunck<K,V> * firsChunkInRange);

public:
	Rebalance(KvChunck<K,V> * startingChunk);

	void engageChunks();
	void freeze();
	void compact(); //no scans, so no scan index

	bool isCompact() { return m_compactedChunks != NULL; }
	bool isEngaged() { return m_engagedChunks != NULL; }
	bool isFreezed() { return m_freezedItems; }

	vector<KvChunck<K,V> *> * getCompactedChunks();
	vector<KvChunck<K,V> *> * getEngagedChunks();

	virtual ~Rebalance();
};

#endif /* REBALANCE_H_ */
