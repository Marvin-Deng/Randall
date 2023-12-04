#!/bin/bash

# Output size checks

if [ `./randall 0 | wc -c` -eq 0 ]; \
then echo "P: Basic test on nbytes = 0 ./randall 0"; \
else echo "F: Basic test on nbytes = 0 ./randall 0"; \
fi

if [ `./randall 10 | wc -c` -eq 10 ]; \
then echo "P: Basic test on ./randall 10"; \
else echo "F: Basic test on ./randall 10"; \
fi

if [ `./randall -i rdrand 10 | wc -c` -eq 10 ]; \
then echo "P: rdrand test on ./randall -i rdrand 10"; \
else echo "F: rdrand test on ./randall -i rdrand 10"; \
fi

if [ `./randall -i ldrand48_r 10 | wc -c` -eq 10 ]; \
then echo "P: ldrand48_r test on ./randall -i ldrand48_r 10"; \
else echo "F: ldrand48_r test on ./randall -i ldrand48_r 10"; \
fi

if [ `./randall -i /dev/random 30 | wc -c` -eq 30 ]; \
then echo "P: /F test on /dev/random 30"; \
else echo "F: /F test on /dev/random 30"; \
fi

if [ `./randall -o stdio 30 | wc -c` -eq 30 ]; \
then echo "P: Test -o stdio on ./randall -o stdio 30"; \
else echo "F: Test -o stdio on ./randall -o stdio 30"; \
fi

if [ `./randall -o 10 100 | wc -c` -eq 100 ]; \
then echo "P: Test -o N on ./randall -o 10 100"; \
else echo "F: Test -o N on ./randall -o 10 100"; \
fi

if [ `./randall -i /dev/random 30 -o 10 100 | wc -c` -eq 30  ]; \
then echo "P: Test -i and -o N on -i /dev/random 30 -o 10 100"; \
else echo "F: Test -i and -o N on -i /dev/random 30 -o 10 100"; \
fi

if [ `./randall -i /dev/random 30 -o stdio | wc -c` -eq 30  ]; \
then echo "P: Test -i and -o stdio on ./randall -o 10 100"; \
else echo "F: Test -i and -o stdio on ./randall -o 10 100"; \
fi

# Input error checks

if [ "$(./randall 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for missing nbytes in ./randall"; \
else echo "F: Return code is not 1 for missing nbytes in ./randall"; \
fi

if [ "$(./randall dsfds 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for non integer nbytes in ./randall dsfds"; \
else echo "F: Return code is not 1 for non integer nbytes in ./randall dsfds"; \
fi

if [ "$(./randall -dsfs 3 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for invalid option in ./randall -dsfs"; \
else echo "F: Return code is not 1 for invalid option in ./randall -dsfs"; \
fi

if [ "$(./randall -i 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for missing operand in ./randall -i"; \
else echo "F: Return code is not 1 for missign operand in ./randall -i"; \
fi

if [ "$(./randall -i invalid_input_option 4 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for ./randall -i invalid_input_option 4"; \
else echo "F: Return code is not 1 for ./randall -i invalid_input_option 4"; \
fi

if [ "$(./randall -i ldrand48_r 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for missing nbytes in ./randall -i ldrand48_r"; \
else echo "F: Return code is not 1 for missing nbytes in ./randall -i ldrand48_r"; \
fi

if [ "$(./randall -i /dev/random 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for missing nbytes in ./randall -i /dev/random"; \
else echo "F: Return code is not 1 for missing nbytes in ./randall -i /dev/random/"; \
fi

if [ "$(./randall -i /FFFF 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for invalid path in ./randall -i /FFFF"; \
else echo "F: Return code is not 1 for invalid path in ./randall -i /FFFF"; \
fi

# Output error checks

if [ "$(./randall -o 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for missing -o argument in ./randall -o"; \
else echo "F: Return code is not 1 ffor missing -o argument in ./randall -o"; \
fi

if [ "$(./randall -o invalid_option 4 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for invalid output option in ./randall -o invalid_option 4"; \
else echo "F: Return code is not 1 for invalid output option in ./randall -o invalid_option 4"; \
fi

if [ "$(./randall -o 5 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for missing 'nbytes' in ./randall -o 5"; \
else echo "F: Return code is not 1 for missing 'nbytes' in ./randall -o 5"; \
fi

if [ "$(./randall -o stdio 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for missing 'nbytes' with stdio in ./randall -o stdio"; \
else echo "F: Return code is not 1 for missing 'nbytes' with stdio ./randall -o  stdio"; \
fi

if [ "$(./randall -o 0 100 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for block size of 0 in ./randall -o 0 100"; \
else echo "F: Return code is not 1 for block size of 0 in ./randall -o 0 100"; \
fi

if [ "$(./randall -o -5 100 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for negative block size in ./randall -o -5 100"; \
else echo "F: Return code is not 1 for negative block size in ./randall -o -5 100"; \
fi
