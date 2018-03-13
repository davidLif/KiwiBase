/*
 * RebalancePolicy.h
 *
 *  Created on: Mar 13, 2018
 *      Author: david
 */

#ifndef REBALANCEPOLICY_H_
#define REBALANCEPOLICY_H_

#include "../KvChunck.h"

#define MAX_AFTER_MERGE_PART 0.5

template <class K, class V>
class RebalancePolicy {
private:
	KvChunck<K,V> * m_firstChunk;
	KvChunck<K,V> * m_lastChunk;
	int m_chunksInRange;
	int m_itemsInRange;
	const int m_maxAfterMergeItems = (int)(CHUNK_MAX_ITEMS * MAX_AFTER_MERGE_PART);
public:
	RebalancePolicy(KvChunck<K,V> * startChunk);
	KvChunck<K,V> * findNextCandidate();
	void updateRangeView();
	KvChunck<K,V> * getFirstChunkInRange();
	virtual ~RebalancePolicy();
};

#endif /* REBALANCEPOLICY_H_ */
