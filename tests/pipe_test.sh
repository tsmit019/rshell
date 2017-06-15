echo "-----This is the start of the #pipe_tests-----"

RSHELL=../bin/rshell

$RSHELL << EOF
echo hello && ls -l | sed -e "s/[aeio]/u/g"
echo this will test && echo this will work here > test.txt
ls -l | grep "\.txt$"
ls | echo
rm test.txt
exit
EOF
