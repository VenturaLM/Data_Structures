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
	TMPFILE=/tmp/ed_test_$$_${RANDOM}
	TOTAL=$(( $TOTAL + 1 ))
	set +e
	$prog $t >& ${TMPFILE}
	RETV=$?
	YOUR_OUTPUT="$( cat ${TMPFILE} )"
	EXPECTED_OUTPUT="$( cat ${t}.a )"
	DIFF=$( diff $TMPFILE ${t}.a )
	set -e
        
	echo -n "test $t : "
	if [ $RETV != 0 ] || [ "${YOUR_OUTPUT}" != "${EXPECTED_OUTPUT}" ]; then
		echo " Fail!"
		if [ $RETV != 0 ]; then
			echo -e "\t The program exits with error code $RETV"
                fi
                echo -e "\t Expected:\n[${EXPECTED_OUTPUT}]"
                echo -e "\t Your output:\n[${YOUR_OUTPUT}]"
                echo -e "\t Differences:\n[${DIFF}]"
	else
		PASS=$(( $PASS + 1 ))
		echo " Success!"
	fi
done

echo "You pass $PASS of $TOTAL tests."

exit 0

