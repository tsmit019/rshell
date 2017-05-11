#!/bin/sh

#tests commands with comments

echo "-----This is the start of the #comment_tests-----"

RSHELL=../bin/rshell

$RSHELL << EOF
ls -a #hello
mkdir test1 #hello2
rm -r test1 #hello3 && testing
echo hello #world
ls -la && echo hello #world
echo hello; ls -l #this is a test
exit
EOF
