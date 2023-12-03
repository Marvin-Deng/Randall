#!/bin/bash

if [ `./randall 0 | wc -c` -eq 0 ]; \
then echo "P: basic test on nbytes = 0 ./randall 0"; \
else echo "F: basic test on nbytes = 0 ./randall 0"; \
fi
if [ `./randall 10 | wc -c` -eq 10 ]; \
then echo "P: basic test on ./randall 10"; \
else echo "F: basic test on ./randall 10"; \
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
