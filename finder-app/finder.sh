#!/bin/sh

function print_usage {
    echo Usage: $0 filesdir searchstr
    echo Example: $0 /tmp/aesd/assignment1 linux
}

if [ ! $# -eq 2 ]
then
    echo Wrong argument number
    print_usage
    exit 1
fi

if [ ! -d $1 ]
then
    echo First argument should be the path to existing directory
    print_usage
    exit 1
fi

files_cnt=$(grep -Hrn $2 $1/* | cut -d : -f 1 | uniq | wc -l)
lines_cnt=$(grep -Hrn $2 $1/* | cut -d : -f-2 | uniq | wc -l)

echo "The number of files are $files_cnt and the number of matching lines are $lines_cnt"
