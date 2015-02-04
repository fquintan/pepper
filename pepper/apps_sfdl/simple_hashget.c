#include <stdint.h>
#include <db.h>

#define SIZE 16

struct In {
	commitmentCK_t commitmentCK;
	commitment_t commitment;};
struct Out {int value;};

/*
  Convert a simple liked list node to its hash, and then reconstruct the
  node using that hash, using hashputdb and hashgetdb and library functions
  in db.h .
*/

void compute(struct In *input, struct Out *output){
	int val;
	setcommitmentCK(&input->commitmentCK);
	hash_t hash_of_val;
	commitmentget(&hash_of_val, &input->commitment);
	hashget(&val, &hash_of_val);
	output->value = val;
}
