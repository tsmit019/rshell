echo "-----This is the start of the #input_redirection-----"

RSHELL=../bin/rshell

$RSHELL << EOF
echo hello && echo hello > test.txt
cat < test.txt
echo hello && ls -la && ls -la > test.txt
cat < test.txt
cat < fake_file.txt
exit
EOF
