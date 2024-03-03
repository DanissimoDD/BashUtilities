#!/bin/bash

#ARRAY_TEST_FILES=("test1.txt" "test2.txt" "test.txt")
#ARRAY_TEMPLATE_FILES=("temp1.txt" "temp2.txt")
TEMPLATE="the"
#FLAGS=(-n -h -l -c -i -v -s) 
E_TEMPLATES=""
F_TEMPLATES=""
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" > log.txt

for var in -n -h -l -c -i -v -s
do
    for file1 in "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
    do
        for file2 in "tests/test1.txt" "tests/test2.txt" "tests/test3.txt"
        do
            TEST1="$var $TEMPLATE $file1 $file2"
            #echo "$TEST1"
            ./s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
                echo "$TEST1" "SUCCESS"
                (( COUNTER_SUCCESS++ ))
            else
                echo "$TEST1" "FAIL"
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
            rm s21_grep.txt grep.txt
        done
    done
done

for var1 in -n -h -l -c -i -v
do
    for var2 in -n -h -l -c -i -v
    do
        for var3 in -n -h -l -c -i -v
        do
            for var4 in -n -h -l -c -i -v
            do  
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    TEST1="$var1 $var2 $var3 $var4 -e ui -f tests/file_temp1.txt -f tests/file_temp2.txt tests/testtext.txt"
                    #echo "$TEST1"
                    ./s21_grep $TEST1 > s21_grep.txt
                    grep $TEST1 > grep.txt
                    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                    then
                        echo "$TEST1" "SUCCESS"
                        (( COUNTER_SUCCESS++ ))
                    else
                        echo "$TEST1" "FAIL"
                        echo "$TEST1" >> log.txt
                        (( COUNTER_FAIL++ ))
                    fi
                    rm s21_grep.txt grep.txt
                fi
            done
        done
    done
done

for var1 in -n -h -l -c -i -v
do
    for var2 in -n -h -l -c -i -v
    do
        for var3 in -n -h -l -c -i -v
        do
            for var4 in -n -h -l -c -i -v
            do  
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    TEST1="-f tests/tfile1.txt $var1 $var2 $var3 $var4 tests/testtext.txt tests/test1.txt tests/test2.txt"
                    #echo "$TEST1"
                    ./s21_grep $TEST1 &> s21_grep.txt
                    grep $TEST1 &> grep.txt
                    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                    then
                        echo "$TEST1" "SUCCESS"
                        (( COUNTER_SUCCESS++ ))
                    else
                        echo "$TEST1" "FAIL"
                        echo "$TEST1" >> log.txt
                        (( COUNTER_FAIL++ ))
                    fi
                    #rm s21_grep.txt grep.txt
                fi
            done
        done
    done
done

for var1 in -n -h -l -c -i -v
do
    for var2 in -n -h -l -c -i -v
    do
        for var3 in -n -h -l -c -i -v
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
            then
                TEST1="-s -e you -e The -f tests/file_temp1.txt $var1 $var2 $var3 tests/testtext.txt test11.txt test24.txt"
                #echo "$TEST1"
                ./s21_grep $TEST1 &> s21_grep.txt
                grep $TEST1 &> grep.txt
                DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
                if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    echo "$TEST1" "SUCCESS"
                    (( COUNTER_SUCCESS++ ))
                else
                    echo "$TEST1" "FAIL"
                    echo "$TEST1" >> log.txt
                    (( COUNTER_FAIL++ ))
                fi
                #rm s21_grep.txt grep.txt
            fi
        done
    done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
