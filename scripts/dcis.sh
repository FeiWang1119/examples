#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage: $0 target source" >&2
	exit 1
fi

for dciname in $2/*; do
	dci $1 $dciname
	name=$(basename "$dciname" .dci)
	cp $1/${name}.dci $dciname
done
