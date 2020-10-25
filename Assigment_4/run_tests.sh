#!/bin/bash
set -e

if [ "x$1" == "x" ] || [ ! -x "$1" ]; then
	echo "uso: $0 <program> [test dir]"
        exit 1
fi

TEST_DIR="./tests"
if [ "x$2" != "x" ] ; then
   TEST_DIR="${2}"
fi

prog="$1" 

PASS=0
TOTAL=0

for t in ${TEST_DIR}/?? ; do
    TOTAL=$(( $TOTAL + 1 ))
    set +e
    YOUR_OUTPUT="$( $prog $t 2>&1 )"
    set -e
    EXPECTED_OUTPUT="$( cat ${t}.a )"
    echo -n "test $t : "
    if [ "${YOUR_OUTPUT}" = "${EXPECTED_OUTPUT}" ]; then
        PASS=$(( $PASS + 1 ))
        echo " Success!"
    else
        echo " Fail!"
        echo -e "\t Expected:\n[${EXPECTED_OUTPUT}]"
        echo -e "\t Your output:\n[${YOUR_OUTPUT}]"
    fi
done

echo "You pass $PASS of $TOTAL tests."
if [ "$PASS" -eq "$TOTAL" ]; then
    exit 0
else
    exit 1
fi


		
