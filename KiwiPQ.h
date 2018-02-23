/*
 * KiwiPQ.h
 *
 *  Created on: Feb 22, 2018
 *      Author: david
 */

#ifndef KIWIPQ_H_
#define KIWIPQ_H_

#include <forward_list>
#include <cstddef>
#include "KvChunck.h"
#include "ABS_PriorityQueue.h"

using namespace std;

typedef KvChunck<unsigned int,int> * Chunck_P;

class KiwiPQ: public Abs_PriorityQueue<unsigned int, int> {
public:
	KiwiPQ();
	virtual void Insert(unsigned int key, int value);
	virtual ~KiwiPQ();

private:
	forward_list<Chunck_P> m_chunckLst;

	Chunck_P getFloorChunckByIndex(unsigned int key);
	Chunck_P getFloorChunckByIteration(unsigned int key, Chunck_P searchStartChunk);
};

#endif /* KIWIPQ_H_ */
