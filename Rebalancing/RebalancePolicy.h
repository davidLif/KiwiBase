/*
 * RebalancePolicy.h
 *
 *  Created on: Mar 13, 2018
 *      Author: david
 */

#ifndef REBALANCEPOLICY_H_
#define REBALANCEPOLICY_H_

#include <math.h>
#include "../KvChunck.h"

#define MAX_AFTER_MERGE_PART 0.5
#define REBALANCE_POLICY_REBALANCE_SIZE 2 //Bit strange but that what the java code says

//No prev and backwards functions, because in the java implementation we get null and always ignore

template <class K, class V>
class RebalancePolicy {
private:
	KvChunck<K,V> * m_firstChunk;
	KvChunck<K,V> * m_lastChunk;
	int m_chunksInRange;
	int m_itemsInRange;
	const double m_maxAfterMergeItems = (double)(CHUNK_MAX_ITEMS * MAX_AFTER_MERGE_PART);

	void updateRangeFwd();
public:
	RebalancePolicy(KvChunck<K,V> * startChunk);
	KvChunck<K,V> * findNextCandidate();
	void updateRangeView();

	KvChunck<K,V> * getFirstChunkInRange();
	virtual ~RebalancePolicy();
};

#endif /* REBALANCEPOLICY_H_ */
