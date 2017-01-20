#!/bin/bash
FT_NM=`./ft_nm $1`
NM=`nm $1`

echo "$FT_NM" > FT_NM_OUTPUT
echo "$NM" > NM_OUTPUT

DIFF=`diff FT_NM_OUTPUT NM_OUTPUT`

# echo 'ft_nm:'
# cat FT_NM_OUTPUT
#
# echo 'nm:'
# cat NM_OUTPUT

if [ -z "$DIFF" ]; then
	echo "$1: OK"
else
	echo "$DIFF"
	echo "$1: KO"
fi
rm FT_NM_OUTPUT
rm NM_OUTPUT
