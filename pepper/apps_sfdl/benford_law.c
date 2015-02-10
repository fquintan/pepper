#include <stdint.h>
#include <db.h>

#include "benford_law.h"

int first_digit(int n){
/*	if (n < 0) n = 0 - n;
	int i;
	for(i; i < MAX_LENGTH; i++){
		if (n > 10){
			n = n / 10;
		}
	}
	return n;*/
	if(n > 1000000000) n = n / 1000000000;
	else if(n > 100000000) n = n / 100000000;
	else if(n > 10000000) n = n / 10000000;
	else if(n > 1000000) n = n / 1000000;
	else if(n > 100000) n = n / 100000;
	else if(n > 10000) n = n / 10000;
	else if(n > 1000) n = n / 1000;
	else if(n > 100) n = n / 100;
	else if(n > 10) n = n / 10;
	return n;
}

void compute_digit_distribution(struct numberArray* array, struct distribution* dist){
	int i;
	int digit;
	for (i = 0; i < MAX_SIZE; i++){
		digit = first_digit(array->arr[i]);
		dist->arr[digit]++;
	}
}


int most_frequent(struct distribution* dist){
	int i;
	int max = 0;
	int index = 0;
	for(i = 0; i < 10; i++){
		if (dist->arr[i] > max){
			max = dist->arr[i];
			index = i;
		}
	}
	return i;
}

int check_distribution(struct distribution* dist){
	int result = most_frequent(dist);
	return result;
}

void compute(struct In *input, struct Out *output){
	int i;
	struct numberArray int_arr;
	hashget(&int_arr, &input->hash);
	struct distribution dist;
	compute_digit_distribution(&int_arr, &dist);
	int result = check_distribution(&dist);
	output->result = result;
}
