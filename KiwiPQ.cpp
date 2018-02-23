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

Chunck_P KiwiPQ::getFloorChunck(unsigned int key)
{
	Chunck_P floorChunck = NULL;
	for(forward_list<KvChunck<unsigned int,int> *>::iterator it = m_chunckLst.begin(); it != m_chunckLst.end(); ++it ) {
		if ((*it)->getMinKey() < key) {
			floorChunck = (*it);
		}
	}
	return floorChunck;
}

KiwiPQ::~KiwiPQ() {
	// TODO Auto-generated destructor stub
}
