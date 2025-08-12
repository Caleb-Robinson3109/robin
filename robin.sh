#!/bin/bash

make -s
./bin/robin $1
make -s robin
./gen/a.out