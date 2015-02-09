#include <stdint.h>
#include <db.h>
#include "merkle.h"

void compute_parent(merkleNode* left, merkleNode* right, merkleNode* parent){
/*	sha1_in shaIn;
	dataToShaIn(&left->val, &right->val, &shaIn);
	sha1_out shaOut;
	compute_sha1(&shaIn, &shaOut);
	data dataOut;
	shaOutToData(&shaOut, &dataOut);
	parent->val = dataOut;*/
	// SHA256_CTX ctx;
	// sha256_init(&ctx);
	// sha256_update(&ctx, left->val.msg, DATA_LENGTH);
	// sha256_update(&ctx, right->val.msg, DATA_LENGTH);
	// sha256_final(&ctx, parent->val.msg); 
}


/*
*	Receives a pointer to a merkleTree whose latter half contains its leafs
*	and computes the rest of the tree
*/
void compute_merkle_tree(merkleTree* tree){
	int i;
	for(i = SIZE-1; i > 0; i--){
		compute_parent(&tree->nodes[2*i], &tree->nodes[2*i+1], &tree->nodes[i]);	
	}
}

/** Check the root of a given tree matches the expected result
	return 0 on a correct tree
*/
int check_root(data* expected, merkleTree* computed){
	return compare_data(expected, computed->nodes[1].val);
}

/*Compares two data instances
  returns 0 when the given arguments are the same
*/
int compare_data(data* d1, data* d2){
	int diff = 0;
	for (i = 0; i < DATA_LENGTH; i++){
		if (d1->msg[i] != d2->msg[i]){
			diff++;
		}
	}
	return diff;
}

/*Concatenate the data to form a valid sha1_in*/
void dataToShaIn(data* left, data* right, sha1_in* in){
	int i;
	for (i = 0; i < DATA_LENGTH; i++){
		in->msg[i] = left->msg[i];
		in->msg[DATA_LENGTH + i] = right->msg[i];
	}
}
/*Pad sha1_out with zeros to form a valid data*/
void shaOutToData(sha1_out* sha, data* d){
	int i;
	for(i = 0; i < SHA1_OUT_LENGTH;i++){
		d->msg[i] = sha->sha1[i];
	}
	for(i = SHA1_OUT_LENGTH; i < DATA_LENGTH;i++){
		d->msg[i] = 0;
	}
}

void compute_proof(merkleTree* tree, int index, merkleProof* proof){
	int i;
	proof->index = index;
	for (i = 0; i < HEIGHT; i++){
		if (index % 2 == 0){
			proof->path[i] = tree->nodes[SIZE+index+1];
		}
		else {
			proof->path[i] = tree->nodes[SIZE+index-1];	
		}
		index = index / 2;
	}
}

/*Verify the correctnes of a given merkle proof
  returns 0 on a correct proof*/
int verify_proof(merkleTree* tree, merkleProof* proof, data* expected_root){
	int index = proof->index;
	int i;
	merkleNode current;
	current.val = proof->nodes[SIZE+index].val;
	for(i = 0; i < HEIGHT; i++){
		if (index % 2){
			compute_parent(current, proof->path[i], current);
		}
		else {
			compute_parent(proof->path[i], current, current);
		}
		index = index / 2;
	}
	return compare_data(expected_root, current.val);
}

void compute(struct In *input, struct Out *output){
	output->result = 0;
	int i;
	data d;
	arrayOfData arr;
	data aux;
	hashget(&arr, &input->hash_of_db);
	merkleTree tree;
	/*First copy the data array into the leafs of an empty merkleTree*/
	for (i = 0; i < SIZE; i++){
		tree.nodes[SIZE+i].val = arr.data_arr[i];
	}
	/*Then compute the whole tree from the leafs*/
	compute_merkle_tree(&tree);
	/*Check the correctness of the computed tree*/
	output->result = 1;
}



