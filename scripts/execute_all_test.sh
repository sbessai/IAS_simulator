# SCRIPT TO GENERATE OUTPUT FILE OF INSTRUCTION TESTS

mkdir -p ./output                                       \
         ./output/instruction_test                      \
         ./output/instruction_test/data_transfert       \
         ./output/instruction_test/unconditional_branch \
         ./output/instruction_test/conditional_branch   \
         ./output/instruction_test/arithmetic           \
         ./output/instruction_test/address_modify

# BUILD MAKEFILE
cmake .

# BUILD PROJECT
make 

# DATA_TRANSFERT
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/data_transfert/1_load_mq.ias > ./output/instruction_test/data_transfert/1_load_mq.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/data_transfert/2_load_mq_mx.ias > ./output/instruction_test/data_transfert/2_load_mq_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/data_transfert/3_stor_mx.ias > ./output/instruction_test/data_transfert/3_stor_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/data_transfert/4_load_mx.ias > ./output/instruction_test/data_transfert/4_load_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/data_transfert/5_load_min_mx.ias > ./output/instruction_test/data_transfert/5_load_min_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/data_transfert/6_load_abs_mx.ias > ./output/instruction_test/data_transfert/6_load_abs_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/data_transfert/7_load_min_abs_mx.ias > ./output/instruction_test/data_transfert/7_load_min_abs_mx.output

# UNCONDITIONAL_BRANCH
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/unconditional_branch/8_jump_left_mx.ias > ./output/instruction_test/unconditional_branch/8_jump_left_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/unconditional_branch/9_jump_right_mx.ias > ./output/instruction_test/unconditional_branch/9_jump_right_mx.output

# CONDITIONAL_BRANCH
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/conditional_branch/10_jump+_left_mx.ias > ./output/instruction_test/conditional_branch/10_jump+_left_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/conditional_branch/11_jump+_right_mx.ias > ./output/instruction_test/conditional_branch/11_jump+_right_mx.output

# ARITHMETIC
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/arithmetic/12_add_mx.ias > ./output/instruction_test/arithmetic/12_add_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/arithmetic/13_add_abs_mx.ias > ./output/instruction_test/arithmetic/13_add_abs_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/arithmetic/14_sub_mx.ias > ./output/instruction_test/arithmetic/14_sub_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/arithmetic/15_sub_abs_mx.ias > ./output/instruction_test/arithmetic/15_sub_abs_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/arithmetic/16_mul_mx.ias > ./output/instruction_test/arithmetic/16_mul_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/arithmetic/17_div_mx.ias > ./output/instruction_test/arithmetic/17_div_mx.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/arithmetic/18_lsh.ias > ./output/instruction_test/arithmetic/18_lsh.output
./bes_ias  --max-cycle 10 --output-to-file ./scripts/instruction_test/arithmetic/19_rsh.ias > ./output/instruction_test/arithmetic/19_rsh.output

# ADDRESS_MODIFY
./bes_ias --max-cycle 10 --output-to-file ./scripts/instruction_test/address_modify/20_stor_left_mx.ias > ./output/instruction_test/address_modify/20_stor_left_mx.output
./bes_ias --max-cycle 10 --output-to-file ./scripts/instruction_test/address_modify/21_stor_right_mx.ias > ./output/instruction_test/address_modify/21_stor_right_mx.output