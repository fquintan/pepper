#include <stdint.h>
#include <db.h>
#include "merkle.h"


void copy_data(data* from, data* to){
	int i;
	for (i = 0; i < DATA_LENGTH; i++){
		to->msg[i] = from->msg[i];
	}
}
void copy_node(merkleNode* from, merkleNode* to){
	 copy_data(&from->val, &to->val);
}

void compute_parent(merkleNode* left, merkleNode* right, merkleNode* parent){
	sha1_in shaIn;
	dataToShaIn(&left->val, &right->val, &shaIn);
	sha1_out shaOut;
	compute_sha1(&shaIn, &shaOut);
	data dataOut;
	shaOutToData(&shaOut, &dataOut);
	copy_data(&dataOut, &parent->val);
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
	index = SIZE + index;
	int aux;
	for (i = 0; i < HEIGHT; i++){
		if (index % 2 == 0){
			copy_node(&tree->nodes[index+1], &proof->path[i]);
		}
		else {
			copy_node(&tree->nodes[index-1], &proof->path[i]);
		}
		index = index / 2;
	}
}



/*Verify the correctnes of a given merkle proof
  returns 0 on a correct proof*/
int verify_proof(merkleTree* tree, merkleProof* proof, data* expected_root){
	int i;
	int index = proof->index + SIZE;
	merkleNode current;
	copy_node(&tree->nodes[index], &current);
	for (i = 0; i < HEIGHT; i++){
		if (index % 2 == 0){
			compute_parent(&current, &proof->path[i], &current);
		}
		else {
			compute_parent(&proof->path[i], &current, &current);
		}
		index = index / 2;
	}
	return compare_data(expected_root, &current.val);
}


void compute(struct In *input, struct Out *output){
	int i;
	arrayOfData arr;
	hashget(&arr, &input->hash_of_db);
	merkleTree tree;
	for (i = 0; i < SIZE; i++){
		copy_data(&(arr.data_arr[i]), &(tree.nodes[SIZE+i].val));
	}
	compute_merkle_tree(&tree);
	merkleProof proof;
	compute_proof(&tree, 1, &proof);
	data d;
	copy_data(&tree.nodes[1].val, &d);
	output->result = verify_proof(&tree, &proof, &d);
}



