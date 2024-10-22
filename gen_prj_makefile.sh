#!/bin/bash

if [ -d "./builds" ]; then
	echo "builds already exists."
else
	echo "create builds folder"
	mkdir builds
fi

pushd ./builds
cmake -G "Unix Makefiles" ..
popd