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
#include "../KvChunck.h"

using namespace std;

template <class K, class V> static vector<KvChunck<K,V> *> compacting(vector<KvChunck<K,V> *> frozenChunks);

template <class K, class V> static vector<KvChunck<K,V> *> compacting(vector<KvChunck<K,V> *> frozenChunks) {
	return NULL; //dummy
}

#endif /* COMPACTOR_H_ */
