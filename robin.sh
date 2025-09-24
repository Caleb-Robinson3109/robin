#!/bin/bash

# -o <filename> robin bin output
O_FLAG=false
O_FILE="robin.out"
# -i <filename> the intermeident files name
I_FLAG=false
I_FILE=""
#-r remove the intermident cpp file
R_FLAG=false
#-a print ast
A_FLAG=false
#-t print tokens
T_FLAG=false
#TODO debug mode
D_FLAG=false
#-c compile the compiler
C_FLAG=false
#-e exacute the final binary
E_FLAG=false
#-q scilent flag
Q_FLAG=false

#go through opts
while getopts "o:i:atcredq" opt; do
  case ${opt} in
    o)
      O_FILE="$OPTARG"
      O_FLAG=true
      ;;
    i)
      I_FILE="$I_FILE$OPTARG"
      I_FLAG=true
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
    e)
      E_FLAG=true
      ;;
    d)
      D_FLAG=true
      ;;
    q)
      Q_FLAG=true
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


INPUT_FILE="$1"

if [ -z "$INPUT_FILE" ]; then
  echo "robin.sh: \"no input file using default hello.rob\""
  INPUT_FILE="hello.rob"
fi

#get and check for file and names the intermident .cpp file based on -i
if [ "$I_FLAG" = false ]; then
  I_FILE="$INPUT_FILE.cpp"
fi

if [[ $I_FILE != *.cpp ]]; then
  I_FILE="$I_FILE.cpp"
fi

MAKE_CMD="make"

if [ "$Q_FLAG" = true ]; then
  MAKE_CMD="$MAKE_CMD -s "
fi

#compile the compile if -c
if [ "$C_FLAG" = true ]; then
  
  if [ "$Q_FLAG" = false ]; then
    echo "$MAKE_CMD"
  fi
  
  $MAKE_CMD
  if [ $? -ne 0 ]; then
    echo 'robin.cpp build failed'
    exit 1
  fi
fi

#run ./bin/robin on input file
if [ "$Q_FLAG" = false ]; then
    echo "./bin/robin $INPUT_FILE $I_FILE $T_FLAG $A_FLAG"
fi

./bin/robin $INPUT_FILE $I_FILE $T_FLAG $A_FLAG
if [ $? -ne 0 ]; then
  echo 'robin.cpp failed'
  exit 1
fi

#build robin bin
MAKE_ROBIN_CMD="make robin "

if [ "$Q_FLAG" = true ]; then
  MAKE_ROBIN_CMD="$MAKE_ROBIN_CMD -s"
fi

if [ "$O_FLAG" = true ]; then
  MAKE_ROBIN_CMD="$MAKE_ROBIN_CMD ROBIN=$O_FILE"
fi

MAKE_ROBIN_CMD="$MAKE_ROBIN_CMD OUTPUT=$I_FILE"

if [ "$Q_FLAG" = false ]; then
  echo "$MAKE_ROBIN_CMD"
fi

$MAKE_ROBIN_CMD

if [ $? -ne 0 ]; then
  echo "$I_FILE build failed"
  exit 1
fi

#if -r then remove the intermidient .cpp file
if [ "$R_FLAG" = true ]; then
  if [ "$Q_FLAG" = false ]; then
    echo "rm gen/$I_FILE"
  fi
  
  rm gen/$I_FILE
fi

#run the robin bin if -e
if [ "$E_FLAG" = true ]; then
  if [ "$Q_FLAG" = false ]; then
    echo "./gen/$O_FILE"
  fi
  
  ./gen/$O_FILE 
fi
