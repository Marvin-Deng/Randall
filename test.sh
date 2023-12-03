#!/bin/bash

if [ `./randall 0 | wc -c` -eq 0 ]; \
then echo "P: basic test on nbytes = 0 ./randall 0"; \
else echo "F: basic test on nbytes = 0 ./randall 0"; \
fi
if [ `./randall 10 | wc -c` -eq 10 ]; \
then echo "P: basic test on ./randall 10"; \
else echo "F: basic test on ./randall 10"; \
fi