# SCRIPT TO GENERATE OUTPUT FILE OF VALIDATION TESTS

mkdir -p ./output            		\
         ./output/validation

# BUILD MAKEFILE
cmake .

# BUILD PROJECT
make

# VALIDATION PROGRAM
./bes_ias  --max-cycle 100 --output-to-file ./scripts/validation/2_pow_n.ias > ./output/validation/2_pow_n.output
./bes_ias  --max-cycle 100 --output-to-file ./scripts/validation/sum_n.ias > ./output/validation/sum_n.output
./bes_ias  --max-cycle 100 --output-to-file ./scripts/validation/fact.ias > ./output/validation/fact.output