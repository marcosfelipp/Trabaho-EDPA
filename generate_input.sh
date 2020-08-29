#!/bin/bash

test_case=$1;
file_to_save="./tests/${test_case}.txt";

if [ $test_case = "stress" ]
then
    elements="";
    for i in $(seq 1 512000); 
    do
        elements="${elements}1";
    done

    echo "512000" >> "${file_to_save}";
    printf "${elements}\n" >> "${file_to_save}";
fi

if [ $test_case = "ascii" ]
then
    elements="";
    for j in $(seq 32 127); 
    do
        var="\\$(printf '%03o' "$j")";
        elements="${elements}${var}";
        echo "$((j-31))" >> "${file_to_save}";
        printf "${elements}\n" >> "${file_to_save}";
    done
fi

echo "0" >> "${file_to_save}"