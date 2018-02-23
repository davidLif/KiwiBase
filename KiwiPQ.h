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
	virtual ~KiwiPQ();

private:
	forward_list<Chunck_P> m_chunckLst;

	Chunck_P getFloorChunck(unsigned int key);

};

#endif /* KIWIPQ_H_ */
