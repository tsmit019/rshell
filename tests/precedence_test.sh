#!/bin/sh
echo "-----This is the start of the #precedence_test-----"

RSHELL=../bin/rshell

$RSHELL << EOF
echo a && echo b || echo c && echo d
(echo a && echo b) || (echo c && echo d)
(echo a) && (echo b)
((echo a) && (echo b))
((echo a)
exit
EOF

