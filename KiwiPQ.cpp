/*
 * KiwiPQ.cpp
 *
 *  Created on: Feb 22, 2018
 *      Author: david
 */

#include "KiwiPQ.h"

using namespace std;

KiwiPQ::KiwiPQ() : Abs_PriorityQueue<unsigned int, int>::Abs_PriorityQueue() {
	// TODO Auto-generated constructor stub
}

void KiwiPQ::Insert(unsigned int key, int value) {

	PutRetryState_e retryState = KiwiPQ::FullRetry_e;

	while (retryState == KiwiPQ::FullRetry_e) {
		//Use the list index to get closer to the target chunk
		Chunck_P putWorkingChunk = getFloorChunckByIndex(key);

		retryState = KiwiPQ::SemiRetry_e;
		while(retryState == KiwiPQ::SemiRetry_e) {
			//This is an effort to get to the best target chunk even if the index is not "best updated"
			putWorkingChunk = getFloorChunckByIteration(key, putWorkingChunk);

			//Check if the chunk in the middle of specific rebalance stage (according to the java code, chunk.creator != null (IsInfant)).
			//	If the chunk is in the middle of a rebalance operation, then we need to wait until the rebalance is finished
			//  Originally, we will fail in this state. The fix here suggests to sleep and then restart on the function.
			if (putWorkingChunk->infantChunkRebalancing()) {
				//If we entered here, then a rebalance has been called on the non-null parent
				std::this_thread::sleep_for(std::chrono::milliseconds(100)); //0.1 seconds. Just a number
				retryState = KiwiPQ::FullRetry_e;
				continue;
			}

			//try to reserve in-chunk-space for the new key-val pair. If failed then ret val < 0
			int allocatedOrderArrIndex = putWorkingChunk->pairSpaceAlloc(key, value);

			if (allocatedOrderArrIndex < 0) {
				//Call rebalance. if null is returned, make full restart
				putWorkingChunk = putWorkingChunk->rebalance();
				if (putWorkingChunk == NULL) {
					retryState = KiwiPQ::FullRetry_e;
				}
				else {
					retryState = KiwiPQ::SemiRetry_e;
				}
				continue;
			}

			//Technically, no "real" scan ops so no scan preprocess is made

			// Try to update the version to current version, but use whatever version is successfully set
			// reading & setting version AFTER publishing ensures that anyone who sees this put op has
			// a version which is at least the version we're setting, or is otherwise setting the version itself
			int putVersion = putWorkingChunk->setPairVersion(allocatedOrderArrIndex, globalTreeVersion);

			if (putVersion == CHUNK_FREEZE_VERSION) {
				//Clear put operation from chunk ppa (if scan), consider rebalance and semi-retry
				if (KvChunck<unsigned int, int>::shouldRebalance(putWorkingChunk)) {
					putWorkingChunk->rebalance();
				}
				retryState = KiwiPQ::SemiRetry_e;
				continue;
			}

			// Allocation is done (and published) and has a version, all that is left is to insert it into the chunk's linked list
			putWorkingChunk->setPairInChunkSpace(allocatedOrderArrIndex, key);

			//finished the insert, clear declaration if scans

			//consider rebalance
			if (KvChunck<unsigned int, int>::shouldRebalance(putWorkingChunk)) {
				putWorkingChunk->rebalance();
			}

			//Exit put
			retryState = KiwiPQ::SuccessfulExit_e;
		}
	}
}

Chunck_P KiwiPQ::getFloorChunckByIndex(unsigned int key)
{
	Chunck_P floorChunck = NULL;

	//this forward list is only a dummy for the real skip list
	for(forward_list<KvChunck<unsigned int,int> *>::iterator it = m_chunckLst.begin(); it != m_chunckLst.end(); ++it ) {
		if ((*it)->getMinKey() < key) {
			floorChunck = (*it);
		}
	}

	return floorChunck;
}

Chunck_P KiwiPQ::getFloorChunckByIteration(unsigned int key, Chunck_P searchStartChunk) {
	Chunck_P floorChunck = searchStartChunk;
	Chunck_P nextchunk = floorChunck->getNextChunk();

	while((nextchunk != NULL) && (nextchunk->getMinKey() < key)) {
		floorChunck = nextchunk;
		nextchunk = floorChunck->getNextChunk();
	}

	return floorChunck;
}

KiwiPQ::~KiwiPQ() {
	// TODO Auto-generated destructor stub
}
