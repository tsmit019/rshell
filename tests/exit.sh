#!/bin/sh

#tests exit and commands with exit

echo "-----This is the start of the exit_tests-----"

RSHELL=../bin/rshell

$RSHELL << EOF
ls -al
echo hello world && exit
ech hello wrolsjdsa || exit
exit && echo hello
(echo a && echo b) && exit
EOF

