#!/bin/bash

function print_usage {
    echo Usage: $0 path_to_file content
    echo Example:
    echo    $0 /tmp/aesd/assignment1/sample.txt ios
    echo Creates file:
    echo    /tmp/aesd/assignment1/sample.txt
    echo With content:
    echo    ios
}

if [ ! $# -eq 2 ]
then
    echo Wrong argument number
    print_usage
    exit 1
fi

mkdir -p "$(dirname "$1")"

if [ ! $? -eq 0 ]
then
    exit 1
fi

echo $2 > $1
