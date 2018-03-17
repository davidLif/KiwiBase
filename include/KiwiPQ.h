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
#include <chrono>
#include <thread>
#include "KvChunck.h"
#include "ABS_PriorityQueue.h"

using namespace std;

typedef KvChunck<unsigned int,int> * Chunck_P;

class KiwiPQ: public Abs_PriorityQueue<unsigned int, int> {
public:
	KiwiPQ();
	virtual void insert(unsigned int key, int value);
	virtual int popMin();
	virtual ~KiwiPQ();

private:
	forward_list<Chunck_P> m_chunckLst;
	int m_globalTreeVersion;

	int getValue(unsigned int key);
	unsigned int priorityKeyRecalc(unsigned int key, int numOfRetries, int * elementP) { return key;};
	Chunck_P getFloorChunckByIndex(unsigned int key);
	Chunck_P getFloorChunckByIteration(unsigned int key, Chunck_P searchStartChunk);

	enum PutRetryState_e {
		FullRetry_e = 0,
		SemiRetry_e = 1,
		SuccessfulExit_e = 2
	};
};

#endif /* KIWIPQ_H_ */
