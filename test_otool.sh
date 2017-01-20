#!/bin/bash

FT_OTOOL=`./ft_otool $1`
OTOOL=`otool -t $1`

echo "$FT_OTOOL" > FT_OTOOL_OUTPUT
echo "$OTOOL" > OTOOL_OUTPUT

DIFF=`diff FT_OTOOL_OUTPUT OTOOL_OUTPUT`

if [ -z "$DIFF" ]; then
	echo "$1: OK"
else
	echo "----------> $1: KO <----------"
fi
rm FT_OTOOL_OUTPUT
rm OTOOL_OUTPUT
