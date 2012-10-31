#!/bin/bash

function usage()
{
    echo "Usage: ./compile.sh <file> [file1 file2 ...]"
}

function compile()
{
    local filename=$1
    echo "Compiling ${filename}"
    outfile=`echo ${filename} | cut -d . -f 1`
    g++ -ggdb `pkg-config --cflags` -o ${outfile}.o ${filename} `pkg-config --libs opencv`
    echo "Output file ${outfile}"
}

if [ $# -eq 0 ]; then
    usage
fi

for file in $*; do
    compile ${file}
done
