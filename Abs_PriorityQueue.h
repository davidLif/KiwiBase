/*
 * Abs_PriorityQueue.h
 *
 *  Created on: Feb 21, 2018
 *      Author: david
 */

#ifndef ABS_PRIORITYQUEUE_H_
#define ABS_PRIORITYQUEUE_H_

class Abs_PriorityQueue<K,V> {
public:
	Abs_PriorityQueue();
	virtual void Insert(K key, V value);
	virtual V getAndRemoveMin();
	virtual ~Abs_PriorityQueue();
};


#endif /* ABS_PRIORITYQUEUE_H_ */
