#include <stdint.h>
#include <db.h>
#include "Sha1.h"

const int SIZE = 4;
const int DATA_LENGTH = 8;
const int SHA1_IN_LENGTH = 16;
const int SHA1_OUT_LENGTH = 5;


int log2(int n){
	int log = 0;
	while (n > 0){
		n = n / 2;
		log++;
	}
	return log;
}

const int HEIGHT = 2;//log2(SIZE);


typedef struct data{
	uint32_t msg[DATA_LENGTH];	
}data;

typedef struct arrayOfData{
	data data_arr[SIZE];	
}arrayOfData;

struct In {
 	hash_t hash_of_db;
 	//data expected_root;
 	data element;
 	int index;
};

struct Out {
	int result;
};


typedef struct merkleNode{
	data val;
}merkleNode;

typedef struct merkleTree{
	merkleNode nodes[2*SIZE];
}merkleTree;

typedef struct merkleProof{
	merkleNode path[HEIGHT];
	int index;
}merkleProof;

