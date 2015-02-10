#include <stdint.h>
#include <db.h>

#include "simple_hashget.h"
/*
  Convert a simple liked list node to its hash, and then reconstruct the
  node using that hash, using hashputdb and hashgetdb and library functions
  in db.h .
*/

void compute(struct In *input, struct Out *output){
	struct intArray val;
	int i;
	int sum = 0;
	hashget(&val, &input->hash);
//	int size = val.size;
	for(i = 0; i < MAX_SIZE; i++){
		sum += val.arr[i];
	}
	output->value = sum;
}
