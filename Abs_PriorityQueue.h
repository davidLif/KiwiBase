/*
 * Abs_PriorityQueue.h
 *
 *  Created on: Feb 21, 2018
 *      Author: david
 */

#ifndef ABS_PRIORITYQUEUE_H_
#define ABS_PRIORITYQUEUE_H_

template <class K, class V>
class Abs_PriorityQueue {
public:
	Abs_PriorityQueue() {};
	virtual void Insert(K key, V value) = 0;
	//virtual V getAndRemoveMin() = 0;
	virtual ~Abs_PriorityQueue() {};
};


#endif /* ABS_PRIORITYQUEUE_H_ */
