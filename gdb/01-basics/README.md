# 1. Getting started

In order to launch `gdb` to debug the executable of interest we can
run a command like:

```bash
gdb ./programname
```


# 2. Setting breakpoints

Once `gdb` is started, we probably want to set some breakpoints where our
debugging will begin. You can do this using the `break` or `b` command:

```
(gdb) break 129       // To set a breakpoint at line 129
(gdb) b 129           // Same as the previous command, but using the shorthand
(gdb) b G2ME.c:129    // To set a breakpoint at line 129 of G2ME.c
(gdb) info breakpoints    // To see info on all the breakpoints you've set
(gdb) i b                 // Same as the previous command, but using the shorthand
(gdb) delete 1    // To delete breakpoint of breakpoint id 1
(gdb) d 1         // Same as the previous command, but using the shorthand
```


# 3. Setting various modes

Before we run our executable, we may want to change some debugging modes
to help us debug the program. For example:

```
(gdb) set follow-fork-mode child     // To follow the child process after a fork
(gdb) set follow-fork-mode parent    // To follow the parent process after a fork
(gdb) set detach-on-fork off    // To keep forked, non-followed processes attached
```


# 4. Run the program

Once we have some breakpoints and our debugging modes set, we can run the
program. For example:

```
(gdb) r                          // Run the program with no arguments
(gdb) r -a 127.0.0.1 -p 45678    // Run the program with some arguments
```


# 5. Debugging

## 5.1. Advancing through the code

After hitting a breakpoint, we have several options for advancing through
the code:

```
(gdb) next    // Proceed to the next instruction without stepping into subroutines
(gdb) n       // Same as the previous command, but using the shorthand
(gdb) step    // Proceed to the next instruction, stepping into subroutines
(gdb) s       // Same as the previous command, but using the shorthand
(gdb) continue    // Run the program until it hits the next breakpoint
(gdb) c           // Same as the previous command, but using the shorthand
```

## 5.2. Checking the state of variables

something

```
(gdb) print x    // Print the value of the program variable 'x'
(gdb) p x        // Same as the previous command, but using the shorthand
(gdb) p *array@5    // If 'array' is a pointer representing an array of some
                    // type, this prints the first 5 elements of 'array'
(gdb) x/1uh array    // If 'array' is a memory address, print 1 (h)alfword
                     // (2 bytes) located at 'array', interpreted as an
                     // (u)nsigned int
(gdb) x/1cb array+7  // If 'array' is a memory address, print the 7th entry as
                     // a (b)yte (1 byte), interpreted as an (c)har
```
