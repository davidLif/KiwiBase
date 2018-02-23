/*
 * KvChunck.h
 *
 *  Created on: Feb 22, 2018
 *      Author: david
 */

#ifndef KVCHUNCK_H_
#define KVCHUNCK_H_

#include "Struct_KeychunckMeta.h"
#include "PendingPuts/PutPendingItem.h"
#include <forward_list>

template <class K, class V>
class KvChunck {
private:
	K m_minKey;

	KeyChunckMeta m_keysmetaArr[];
	int kCounter;

	V m_valuesArr[];
	int vCounter;

	PutPendingItem m_ppa[];

	KvChunck * next;
	bool isNextMutable; //called "mark" in the article

public:
	KvChunck(K minKey);
	K getMinKey() { return m_minKey; };
	virtual ~KvChunck();
};

#endif /* KVCHUNCK_H_ */
