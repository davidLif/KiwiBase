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

	//Use the list index to get closer to the target chunk
	Chunck_P indexEstimatedChunck = getFloorChunckByIndex(key);

	while(true) {
		//This is an effort to get to the best target chunk even if the index is not "best updated"
		indexEstimatedChunck = getFloorChunckByIteration(key, indexEstimatedChunck);
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
