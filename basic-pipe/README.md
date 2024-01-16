# basic-pipe/

These are several basic examples using piping for my own reference.

## Compilation and Running

### Compilation

```bash
cd basic-pipe/
make
```
This will compile both the `pipe1` and `pipe2` binaries in the current directory

### Running

In one terminal, start the server:

```bash
./pipe1
./pipe2
```

## Explanation

### pipe1

`pipe1` is a simple program which forks into two processes, the parent and
child. The child runs a hardcoded shell command. Prior to this, however, the
child redirects its `stdout` to a pipe which is connected to the parent who
receives this data and then writes it to its `stdout`.

Functionally this program is a waste. It functions as if we only ever ran the
shell command, but forks and sends data through a pipe unnecessarily. The
reason I have this example is to show how to perform this function since
sometimes forking and exec()ing a program and sending its output through a pipe
to another process is useful. This example also demonstrates a basic method for
reading from a pipe.

### pipe2

`pipe2` is functionally identical to `pipe1`, but it collects all the output
from the shell command produced by the child process in memory for our
convenience, should we so desire to have that.
