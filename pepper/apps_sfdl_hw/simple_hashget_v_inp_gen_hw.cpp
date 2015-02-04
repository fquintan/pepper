#include <apps_sfdl_gen/simple_hashget_v_inp_gen.h>
#include <apps_sfdl_hw/simple_hashget_v_inp_gen_hw.h>
#include <apps_sfdl_gen/simple_hashget_cons.h>
#include <storage/configurable_block_store.h>

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
	commitment_t commitment;
  
	commitmentCK_t CK = {{
		//Randomly generated.
		0x8a, 0xf7, 0x24, 0xa1, 0x58, 
		0xc9, 0x8b, 0x89, 0x29, 0x85, 
		0xce, 0xa1, 0xae, 0xc3, 0x42, 
		0x6e, 0xbb, 0x86, 0x56, 0x37
	}};
	int val = (int) 20;

	setcommitmentCK(&CK);
	hashput2(&bs, &hash, &val);
	commitmentput2(&bs, &commitment, &hash);

	int inp = 0;
	for(i = 0; i < NUM_CK_BITS/8; i++){
		mpq_set_ui(input_q[inp++], CK.bit[i], 1);
	}
	for(i = 0; i < NUM_COMMITMENT_CHUNKS; i++){
		mpq_set_ui(input_q[inp++], commitment.bit[i], 1);
	}
  // states that should be persisted and may not be generated everytime should be created here.
  if (generate_states) {
  }
}
