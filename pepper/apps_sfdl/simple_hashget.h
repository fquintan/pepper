#include <stdint.h>
#include <db.h>


const int MAX_SIZE = 5;

struct In {
  hash_t hash;
};
struct Out {int value;};

struct intArray{
  int arr[MAX_SIZE];
};
