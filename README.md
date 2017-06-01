# Rshell
A simple command shell designed by Trevor Smith and Chianh Wu.

## What it does (currently)
This shell will handle standard command line programs and their arguments. Similarly, these commands can be linked with `&&`,`||`, or `;`.
We are orking on adding precidence via parentheses. The shell itself will also handle comments starting with the `#` symbol. There is also a built
in function that will test if a file or directory exits, and can be executed via `test` with flags `-e` to check existance, `-f` to check for 
a regular file, and `-d` to check if it is a directory. Also, `test` can be represented as `[]` (e.g. `test -e /home/user/` = `[ -e /home/user/ ]`);
note also that this is white space sensetive `[-e /home/user/]` will not work.

## How to Run
- `$ git clone https://github.com/tsmit019/rshell.git`
- `$ cd rshell`
- `$ git checkout hw2`
- `$ make`
- `$ bin/rshell`

## If you want to run test
- `$ git clone https://github.com/tsmit019/rshell.git`
- `$ cd rshell`
- `$ git checkout hw3`
- `$ make`
- `$ cd tests`

From here you can chose any of the `.sh` and run them. Make sure they are executable by checking using `ls -l`. If they are not executable, then type `chmod 711 *.sh` to make all the `.sh` files executable. 


## Bugs
If you give a command that is parenthese, connector, then command (e.g. `(echo a && echo b) || echo c`) you get a out of range error that I was 
not able to resolve. Similarly, any connector directly after a closing parenthese will cause this behavior and I am unsure why. I will try and fix 
this by the next release. 

Similarly, commands with connectors right after each other will through a similar out of range error. E.g `echo a && ||` will give you out of range.

