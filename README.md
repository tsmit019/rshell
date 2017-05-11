# Rshell
A simple command shell designed by Trevor Smith and Chianh Wu.

## What it does (currently)
This shell currently will take one command, or a series of commands seperated by `&&`, `\\`, `;`. It will execute these commands from left to right.Similarly, 
it has a self contained exit command that is pretty rudimentary if you look at the source. The shell itself will also handle comments
starting with the `#` symbol.

## How to Run
- `$ git clone https://github.com/tsmit019/rshell.git`
- `$ cd rshell`
- `$ git checkout hw2`
- `$ make`
- `$ bin/rshell`

## If you want to run test
- `$ git clone https://github.com/tsmit019/rshell.git`
- `$ cd rshell`
- `$ git checkout hw2`
- `$ make`
- `$ cd tests`

From here you can chose any of the `.sh` and run them. Make sure they are executable by checking using `ls -l`. If they are not executable, then type `chmod 711 *.sh` to make all the `.sh` files executable. 


## Bugs
If you have something like `ls -la || echo hello && ls -a` then it will run `ls -la` then not run `echo hello`, but in bash it will run the `ls -a` but in our shell it will not run.

Executing a command like `echo hello || ls -a; mkdir test` would sometimes just output the first command twice (possibly fixed).

If you type say `echo "hello world"` it will print `"hello world"` instead of just
`hello world`.

If you type an invalid command say `ech "hello world"` and then try to `exit` after
you will have to type `exit` again to actually exit rshell. 
