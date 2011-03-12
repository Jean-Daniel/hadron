#!/bin/sh
if [ "x$1" == "x" ]; then
	echo "Missing argument."
	exit;
fi

echo "Cleaning `pwd`/$1"
find "$1" -type f \( -iname "*.[h|c|m|]" -o -name "*.cpp" -o -name "*.mm" -o -iname "*.[f|v]s" -o -name "*.xcconfig" \) -exec sed -i '' 's/[[:space:]]*$//' '{}' ';'

