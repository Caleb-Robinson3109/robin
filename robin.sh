#!/bin/bash

make -s
if [ $? -ne 0 ]; then
  echo 'robin.cpp build failed'
  exit 1
fi

./bin/robin $1
if [ $? -ne 0 ]; then
  echo 'robin.cpp failed'
  exit 1
fi

make robin -s
if [ $? -ne 0 ]; then
  echo 'out.cpp build failed'
  exit 1
fi

./gen/a.out
