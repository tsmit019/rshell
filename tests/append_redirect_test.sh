echo "-----This is the start of the #output_append-----"

RSHELL=../bin/rshell

$RSHELL << EOF
echo hello && echo this should work > test.txt
cat < test.txt
ls && ls -al >> test.txt
echo appending && echo now i am adding to this file without deleting anything >> test.txt
cat < test.txt
rm test.txt
exit
EOF

