#!/bin/bash

lcov -t "tst_viswtimer" -o tst_viswtime.info -c -d .
genhtml -o report tst_viswtime.info