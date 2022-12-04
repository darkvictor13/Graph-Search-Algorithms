#!/bin/sh

SUMMARY_FILE=summary.txt
EXEC=Graph_Search_Algorithms_0.1.0.out
INPUT=input_files/exemplo_prof.txt
OUTPUT_BASE=tests_output/test

rm -f $SUMMARY_FILE
for number in {1..10}; do
    FILE_NAME=$OUTPUT_BASE$number.BFS.txt
    ./$EXEC $INPUT $FILE_NAME B
    awk 'NR == 4 {print $5}' $FILE_NAME >> $SUMMARY_FILE
    sleep 1
done

exit 0
