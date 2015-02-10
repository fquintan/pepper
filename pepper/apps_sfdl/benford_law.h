#include <stdint.h>
#include <db.h>


const int MAX_SIZE = 10;
const int MAX_LENGTH = 11;
const int zero_as_int = 48;

struct In {
 	hash_t hash;
};

struct Out {
	int result;
};

struct numberArray{
 	int arr[MAX_SIZE];
};

struct distribution{
	int arr[10];	
};