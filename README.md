# Rshell

    A simple command shell designed by Trevor Smith and Chianh Wu.

## What it does (currently)

    This shell currently will take one command with no delimiters, and execute
    that command. Similarly, it has a self contained exit command that is pretty
    rudimentary if you look at the source. The shell itself will also handle comments
    starting with the '#' symbol.

## Bugs

    This program currently does not take delimiters (e.g. "&&"; "||"; ';').

    If you type say "echo "hello world"" it will print ""hello world"" instead of just
    "hello world".

    If you type an invalid command say "ech "hello world"" and then try to exit after
    you will have to type exit again to actually exit rshell. 
