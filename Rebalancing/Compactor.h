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
#include "../Utils/MarkableReference.h"

#define COMPACTOR_LOW_THRESHOLD 		CHUNK_MAX_ITEMS/2
#define COMPACTOR_HIGH_THRESHOLD 		CHUNK_MAX_ITEMS - KIWI_MAX_WORKING_THREADS
#define COMPACTOR_MAX_RANGE_TO_APPEND 	0.2 * CHUNK_MAX_ITEMS

using namespace std;

template <class K, class V> static vector<KvChunck<K,V> *> compacting(vector<KvChunck<K,V> *> * frozenChunks);
template <class K, class V> static bool canAppendSuffix(int orderIndex, vector<KvChunck<K,V> *> * frozenSuffix, int maxCount);
template <class K, class V> static void completeCopy(KvChunck<K,V> * dest, int orderIndex, vector<KvChunck<K,V> *> * srcChunks);

template <class K, class V> static vector<KvChunck<K,V> *> compacting(vector<KvChunck<K,V> *> * frozenChunks) {

	vector<KvChunck<K,V> *> * compacted = new vector<KvChunck<K,V> *>();

	KvChunck<K,V> * firstFrozen = (*frozenChunks)[0];
	KvChunck<K,V> * currFrozen = firstFrozen;
	KvChunck<K,V> * currCompacted = new KvChunck<K,V>(currFrozen, currFrozen->getMinKey());
	int orderIndex = firstFrozen->getFirstItemOrderId();

	int frozenIndex = 1;
	while (true) {
		orderIndex = currCompacted->copyPart(currFrozen, orderIndex, COMPACTOR_LOW_THRESHOLD);

		if (orderIndex == CHUNK_EMPTY_VERSION) { // if completed reading curr freezed chunk
			if (frozenIndex >= frozenChunks->size()) break;

			currFrozen = (*frozenChunks)[frozenIndex];
			frozenIndex++;
			orderIndex = currFrozen->getFirstItemOrderId();
		}
		else { // filled compacted chunk up to LOW_THRESHOLD

			frozenIndex--; //Move the index one step backwards
			vector<KvChunck<K,V> *> frozenSuffix
				= frozenChunks.subList(frozenChunks.begin() + frozenIndex, frozenChunks.begin() + frozenChunks.size());

			// try to look ahead and add frozen suffix
			if (canAppendSuffix(orderIndex, frozenSuffix, COMPACTOR_MAX_RANGE_TO_APPEND)) {
				completeCopy(currCompacted, orderIndex, frozenSuffix);
			}
			else {
				KvChunck<K,V> * newChunkOutOfFrozen = new KvChunck<K,V>(firstFrozen, currFrozen->readKey(orderIndex));
				//TODO - we loose a reference to a chunk here.
				// If we can make the main index loose its reference to the chunk too
				// , then we can "smart free" the chunk here.
				delete currCompacted->m_next; //
				currCompacted->m_next = new MarkableReference<KvChunck<K,V>>(newChunkOutOfFrozen, false);

				compacted->insert(currCompacted);
				currCompacted = newChunkOutOfFrozen;
			}
		}
	}

	compacted->insert(currCompacted);

	return compacted;
}

template <class K, class V> static bool canAppendSuffix(int orderIndex, vector<KvChunck<K,V> *> * frozenSuffix, int maxCount) {
	//TODO : dummy. MultiChunkIterator is quit hard
	return false;
}

template <class K, class V> static void completeCopy(KvChunck<K,V> * dest, int orderIndex, vector<KvChunck<K,V> *> * srcChunks) {

	KvChunck<K,V> * src = (*srcChunks)[0];
	dest->copyPart(src, orderIndex, CHUNK_MAX_ITEMS);

	for (int iterationIndex = 1; iterationIndex < srcChunks.size(); iterationIndex++) {
		src = (*srcChunks)[iterationIndex];
		orderIndex = src->getFirstItemOrderId();
		dest->copyPart(src, orderIndex, CHUNK_MAX_ITEMS);
	}
}

#endif /* COMPACTOR_H_ */
