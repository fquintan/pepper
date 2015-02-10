#include <apps_sfdl_gen/simple_hashget_v_inp_gen.h>
#include <apps_sfdl_hw/simple_hashget_v_inp_gen_hw.h>
#include <apps_sfdl_gen/simple_hashget_cons.h>
#include <storage/configurable_block_store.h>

#include <apps_sfdl/simple_hashget.h>
//This file will NOT be overwritten by the code generator, if it already
//exists. make clean will also not remove this file.

simple_hashgetVerifierInpGenHw::simple_hashgetVerifierInpGenHw(Venezia* v_)
{
  v = v_;
  compiler_implementation.v = v_;
}

//Refer to apps_sfdl_gen/simple_hashget_cons.h for constants to use when generating input.
void simple_hashgetVerifierInpGenHw::create_input(mpq_t* input_q, int num_inputs)
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

	struct intArray val;
	for (i = 0; i < simple_hashget_cons::MAX_SIZE; i++){
		val.arr[i] = i+1;
	}
	hashput2(&bs, &hash, &val);
	int inp = 0;

	for(i = 0; i < NUM_HASH_CHUNKS; i++){
		mpq_set_ui(input_q[inp++], hash.bit[i], 1);
	}

  // states that should be persisted and may not be generated everytime should be created here.
  if (generate_states) {
  }
}
