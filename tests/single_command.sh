#!/bin/sh

#tests single commands

echo "-----This is the start of the single_tests-----"

RSHELL=../bin/rshell

$RSHELL << EOF
echo testing this is a testing
echo "hello world"
ls -a
ls -a -l
ls -al
$$ || ;
touch testing.cpp
ls -l
rm testing.cpp
ls -l
invalidtest
echo testing123 haha
exit
EOF

