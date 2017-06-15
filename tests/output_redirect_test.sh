echo "-----This is the start of the #output_overwriting-----"

RSHELL=../bin/rshell

$RSHELL << EOF
ls -la > test.txt
cat < test.txt
echo erasing everything and trying again > test.txt
cat < test.txt
cat < test.txt > test_clone.txt #this will not work in my code
rm test.txt
exit
EOF
