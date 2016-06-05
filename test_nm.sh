#!/bin/bash
VAR=`./ft_nm ft_nm > FT_NM_OUTPUT && nm ft_nm > NM_OUTPUT && diff NM_OUTPUT FT_NM_OUTPUT`
if [ -z "$VAR" ]; then
	echo "OK"
else
	echo "KO"
fi
rm FT_NM_OUTPUT
rm NM_OUTPUT
