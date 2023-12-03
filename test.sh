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

# Error checks

if [ "$(./randall 2> /dev/null; echo $?)" -eq 1 ]; \
then echo "P: Return code is 1 for missing nbytes in ./randall"; \
else echo "F: Return code is not 1 for missing nbytes in ./randall"; \
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
then echo "P: Return code is 1 for invalid path ./randall -i /FFFF"; \
else echo "F: Return code is not 1 for invalid path ./randall -i /FFFF"; \
fi