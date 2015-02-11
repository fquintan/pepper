#include <apps_sfdl_hw/simple_hashget_p_exo.h>
#include <apps_sfdl_gen/simple_hashget_cons.h>
#include <common/sha1.h>
#include <storage/configurable_block_store.h>
#include <db.h>

#pragma pack(push)
#pragma pack(1)

#include  <apps_sfdl/simple_hashget.c>
//This file will NOT be overwritten by the code generator, if it already
//exists. make clean will also not remove this file.

simple_hashgetProverExo::simple_hashgetProverExo() {

  //Uncomment and fix to specify the sizes of the input and output types
  //to baseline_minimal:
  //baseline_minimal_input_size = sizeof(something);
  //baseline_minimal_output_size = sizeof(something);

}

//using namespace simple_hashget_cons;

void simple_hashgetProverExo::init_exo_inputs(
  const mpq_t* input_q, int num_inputs,
  char *folder_path, HashBlockStore *bs) {
  
}

void simple_hashgetProverExo::export_exo_inputs(
  const mpq_t* output_q, int num_outputs,
  char* folder_path, HashBlockStore *bs) {

}

void simple_hashgetProverExo::run_shuffle_phase(char *folder_path) {

}

void simple_hashgetProverExo::baseline_minimal(void* input, void* output){
}

void simple_hashgetProverExo::baseline(const mpq_t* input_q, int num_inputs, 
      mpq_t* output_recomputed, int num_outputs) {
  struct In input;
  struct Out output;
  // Fill code here to prepare input from input_q.
  int i;
  for(i = 0; i < NUM_HASH_CHUNKS; i++){
    input.hash.bit[i] = mpz_get_ui(mpq_numref(input_q[i]));
  }
  // Call baseline_minimal to run the computation
  struct intArray val;
  int sum = 0;
  hashget(&val, &input.hash);
  for(i = 0; i < MAX_SIZE; i++){
    sum += val.arr[i];
  }
  output.value = sum;
  // Fill code here to dump output to output_recomputed.
  mpq_set_si(output_recomputed[0], 0, 1);
  mpq_set_si(output_recomputed[1], output.value, 1);
}

//Refer to apps_sfdl_gen/simple_hashget_cons.h for constants to use in this exogenous
//check.
bool simple_hashgetProverExo::exogenous_check(const mpz_t* input, const mpq_t* input_q,
      int num_inputs, const mpz_t* output, const mpq_t* output_q, int num_outputs, mpz_t prime) {

  bool passed_test = true;
#ifdef ENABLE_EXOGENOUS_CHECKING
  mpq_t *output_recomputed;
  alloc_init_vec(&output_recomputed, num_outputs);
  baseline(input_q, num_inputs, output_recomputed, num_outputs);

  for(int i = 0; i < num_outputs; i++){

    if (mpq_equal(output_recomputed[i], output_q[i]) == 0){
      passed_test = false;
      break;
    }

  }
  clear_vec(num_outputs, output_recomputed);
#else
  gmp_printf("<Exogenous check disabled>\n");
#endif
  return passed_test;
};

#pragma pack(pop)
