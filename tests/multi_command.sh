#!/bin/sh

echo "-----This is the start of the #comment_tests-----"

RSHELL=../bin/rshell

$RSHELL << EOF
ls -al && echo hello world
ech hello world || ls -l
mkdir hello_test; rm -r hello_test
echo test && ls -l
echo hello; ls -la && echo world
echo ples; echo give; echo me; echo points; echo ples
exit
