/*
 * Struct_KeyChunckMeta.h
 *
 *  Created on: Feb 23, 2018
 *      Author: david
 */

#ifndef STRUCT_KEYCHUNCKMETA_H_
#define STRUCT_KEYCHUNCKMETA_H_

struct KeyChunckMeta {
	unsigned int key; //4 bytes
	unsigned int version; //4 bytes
	void * valuePtr; //4 bytes
	KeyChunckMeta * next; //4 bytes
};

#endif /* STRUCT_KEYCHUNCKMETA_H_ */
