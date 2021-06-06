# scbfi
a fast lightweight bf interpreter

**Command:** bf (filename)

-Note- if there's no filename provided, it executes the example file (ej.bf).

**Characteristics:**

* The stack is 30000 bytes
* The máximum number of nested loops that can be used in a program is 3000 **However this doesn't mean that a program can't use more of 3000 loop, it's only when they're nested**
* The only limit on file size is the available ram in your computer, this is because all the instructions are stored in ram before startitng the program

**Roadmap:**

* Add debuging mode
* Add interactive mode
