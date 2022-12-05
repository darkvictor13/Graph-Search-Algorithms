#!/bin/sh

SUMMARY_FILE=summary.txt
EXEC=Graph_Search_Algorithms_1.0.0.out
INPUT=input_files/exemplo_prof.txt
OUTPUT_BASE=tests_output/test

rm -f $SUMMARY_FILE
echo "Testes executados em: $(date)" >> $SUMMARY_FILE
echo "BFS:" >> $SUMMARY_FILE
for number in {1..100}; do
    FILE_NAME=$OUTPUT_BASE$number.BFS.txt
    ./$EXEC $INPUT $FILE_NAME B
    awk 'NR == 4 {print $5}' $FILE_NAME >> $SUMMARY_FILE
    sleep 1
done

echo "DFS:" >> $SUMMARY_FILE
for number in {1..100}; do
    FILE_NAME=$OUTPUT_BASE$number.DFS.txt
    ./$EXEC $INPUT $FILE_NAME D
    awk 'NR == 4 {print $5}' $FILE_NAME >> $SUMMARY_FILE
    sleep 1
done

echo "A*:" >> $SUMMARY_FILE
for number in {1..100}; do
    FILE_NAME=$OUTPUT_BASE$number.A*.txt
    ./$EXEC $INPUT $FILE_NAME A
    awk 'NR == 4 {print $5}' $FILE_NAME >> $SUMMARY_FILE
    sleep 1
done

exit 0
