/*
 * Compactor.h
 *
 *  Created on: Mar 12, 2018
 *      Author: david
 */

#ifndef COMPACTOR_H_
#define COMPACTOR_H_

#include <vector>
#include <cstddef>
#include "../KiwiConfigDefinitions.h"
#include "../KvChunck.h"

#define COMPACTOR_LOW_THRESHOLD 		CHUNK_MAX_ITEMS/2
#define COMPACTOR_HIGH_THRESHOLD 		CHUNK_MAX_ITEMS - KIWI_MAX_WORKING_THREADS
#define COMPACTOR_MAX_RANGE_TO_APPEND 	0.2 * CHUNK_MAX_ITEMS

using namespace std;

template <class K, class V> static vector<KvChunck<K,V> *> compacting(vector<KvChunck<K,V> *> * frozenChunks);

template <class K, class V> static vector<KvChunck<K,V> *> compacting(vector<KvChunck<K,V> *> * frozenChunks) {

	vector<KvChunck<K,V> *> * compacted = new vector<KvChunck<K,V> *>();

	KvChunck<K,V> * firstFrozen = (*frozenChunks)[0];
	KvChunck<K,V> * currFrozen = firstFrozen;
	KvChunck<K,V> * currCompact = new KvChunck<K,V>(currFrozen);
	int orderIndex = firstFrozen->getFirstItemOrderId();

	int frozenIndex = 1;
	while (true) {
		orderIndex = currCompact->copyPart(currFrozen, orderIndex, COMPACTOR_LOW_THRESHOLD);

		if (orderIndex == CHUNK_EMPTY_VERSION) { // if completed reading curr freezed chunk
			if (frozenIndex >= frozenChunks->size()) break;

			currFrozen = (*frozenChunks)[frozenIndex];
			frozenIndex++;
			orderIndex = currFrozen->getFirstItemOrderId();
		}
		else { // filled compacted chunk up to LOW_THRESHOLD

		}
	}

	return NULL; //dummy
}

#endif /* COMPACTOR_H_ */
