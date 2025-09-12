#!/bin/bash


#robin bin output
O_FLAG=false
O_FILE="robin.out"
#TODO
K_FLAG=false
K_FILE=""
#TODO
A_FLAG=false
#TODO
T_FLAG=false
#compile the compiler
C_FLAG=false
#run the final binary
R_FLAG=false

#go through opts
while getopts "o:k:atcr" opt; do
  case ${opt} in
    o)
      O_FILE="$OPTARG"
      O_FLAG=true
      ;;
    k)
      K_FILE="$OPTARG"
      K_FLAG=true
      ;;
    a)
      A_FLAG=true
      ;;
    t)
      T_FLAG=true
      ;;
    c)
      C_FLAG=true
      ;;
    r)
      R_FLAG=true
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument" >&2
      exit 1
      ;;
  esac
done

#remove opts from args
shift $((OPTIND - 1))

#check for file
INPUT_FILE="$1"


#compile the compile if -c
if [ "$C_FLAG" = true ]; then
  make -s
  if [ $? -ne 0 ]; then
    echo 'robin.cpp build failed'
    exit 1
  fi
fi

#run ./bin/robin on input file
./bin/robin $INPUT_FILE
if [ $? -ne 0 ]; then
  echo 'robin.cpp failed'
  exit 1
fi

#build robin bin
MAKE_CMD="make robin -s"

if [ "$O_FLAG" = true ]; then
  MAKE_CMD="$MAKE_CMD ROBIN=$O_FILE"
fi

$MAKE_CMD

if [ $? -ne 0 ]; then
  echo 'out.cpp build failed'
  exit 1
fi

#run the robin bin if -r
if [ "$R_FLAG" = true ]; then
  ./gen/$O_FILE
fi
