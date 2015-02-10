#include <apps_sfdl_gen/benford_law_v_inp_gen.h>
#include <apps_sfdl_hw/benford_law_v_inp_gen_hw.h>
#include <apps_sfdl_gen/benford_law_cons.h>
#include <storage/configurable_block_store.h>

#include <apps_sfdl/benford_law.h>
//This file will NOT be overwritten by the code generator, if it already
//exists. make clean will also not remove this file.

benford_lawVerifierInpGenHw::benford_lawVerifierInpGenHw(Venezia* v_)
{
  v = v_;
  compiler_implementation.v = v_;
}

//Refer to apps_sfdl_gen/benford_law_cons.h for constants to use when generating input.
void benford_lawVerifierInpGenHw::create_input(mpq_t* input_q, int num_inputs)
{
  #if IS_REDUCER == 0
  //Default implementation is provided by compiler
  compiler_implementation.create_input(input_q, num_inputs);
  #endif
	char db_file_path[BUFLEN];
	snprintf(db_file_path, BUFLEN - 1, "%s/block_stores/prover_1_%s", FOLDER_STATE,
	shared_bstore_file_name.c_str());
	ConfigurableBlockStore bs(db_file_path);
	int i;
	hash_t hash;

	struct numberArray array;
	for (i = 0; i < benford_law_cons::MAX_SIZE; i++){
		array.arr[i] = rand() % 100 + 100;
	}
	hashput2(&bs, &hash, &array);
	int inp = 0;

	for(i = 0; i < NUM_HASH_CHUNKS; i++){
		mpq_set_ui(input_q[inp++], hash.bit[i], 1);
	}

  // states that should be persisted and may not be generated everytime should be created here.
  if (generate_states) {
  }
}
