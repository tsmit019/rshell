#!/bin/sh
echo "-----This is the start of the #test_test-----"

RSHELL=../bin/rshell

$RSHELL << EOF
test -e /home
[ -d /etc/ ]
test -f /home/
test -d /home/
[ -e /etc/ ]
[ -f /etc/home/ ]
test /home/trevor
[ /home/trevor/is_the_best.txt ]
exit
EOF
