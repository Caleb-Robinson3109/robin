#!/bin/bash

./bin/robin $1
if [ $? -ne 0 ]; then
  exit 1
fi

make robin -s
if [ $? -ne 0 ]; then
  exit 1
fi

./gen/a.out
