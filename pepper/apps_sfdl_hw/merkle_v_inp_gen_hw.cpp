#include <apps_sfdl_gen/merkle_v_inp_gen.h>
#include <apps_sfdl_hw/merkle_v_inp_gen_hw.h>
#include <apps_sfdl_gen/merkle_cons.h>

#include <storage/configurable_block_store.h>
#include <apps_sfdl/merkle.h>

//This file will NOT be overwritten by the code generator, if it already
//exists. make clean will also not remove this file.

merkleVerifierInpGenHw::merkleVerifierInpGenHw(Venezia* v_)
{
  v = v_;
  compiler_implementation.v = v_;
}

//Refer to apps_sfdl_gen/merkle_cons.h for constants to use when generating input.
void merkleVerifierInpGenHw::create_input(mpq_t* input_q, int num_inputs)
{
  #if IS_REDUCER == 0
  //Default implementation is provided by compiler
  compiler_implementation.create_input(input_q, num_inputs);
  #endif
	char db_file_path[BUFLEN];
	snprintf(db_file_path, BUFLEN - 1, "%s/block_stores/prover_1_%s", FOLDER_STATE,
	shared_bstore_file_name.c_str());
	ConfigurableBlockStore bs(db_file_path);
	int i, j;
	hash_t hash;

	arrayOfData data;
	for(i = 0; i < merkle_cons::SIZE; i++){
		for(j = 0; j < merkle_cons::DATA_LENGTH; j++){
			data.data_arr[i].msg[j] = (uint32_t) i*j;
		}
	}
	hashput2(&bs, &hash, &data);
	int inp = 0;

	for(i = 0; i < NUM_HASH_CHUNKS; i++){
		mpq_set_ui(input_q[inp++], hash.bit[i], 1);
	}
	for(i = 0; i < merkle_cons::DATA_LENGTH; i++){
		mpq_set_ui(input_q[inp++], data.data_arr[1].msg[i], 1);
	}
	mpq_set_si(input_q[inp++], 1, 1);

  // states that should be persisted and may not be generated everytime should be created here.
  if (generate_states) {
  }
}
