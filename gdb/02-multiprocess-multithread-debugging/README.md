# 1. Getting started

Launch `gdb` to debug the executable of interest. Now you likely want to set
breakpoints just before your program forks or becomes multithreaded, and at
the beginning of each thread.

# 2. Setting detach mode

If you are debugging a multiprocess program, you will want to prevent
`gdb` from detaching the inferiors that it does not follow.

```
(gdb) set detach-on-fork off    // To keep forked, non-followed processes attached
```

For multithreaded programs, you can skip this step.

# 3. Run the program

Run the program until it reaches one of the breakpoints you set. For example:

```
(gdb) r -a 127.0.0.1 -p 45678
```

# 4. Debugging

## 4.1. Setting scheduler locking

Once a breakpoint is hit (and in accordance with the multithreaded debugging
method to be demonstrated in this tutorial) we will enable scheduler locking.
What this means is that now when `gdb` stops or continues, it stops or resumes
only the current thread/process and not *all* of them. This is often useful
when debugging multiprocess/multithreaded programs as we may want to switch
between threads, controlling exactly what each one is doing in order to recreate
a specific possible execution order.

```
(gdb) set scheduler-locking on
```

## 4.2. Debugging the processes/threads

Now we can `step` or `next` past the fork or thread creation so that all our
processes/threads get created. Once they have, we can switch to the thread
we want to follow first. For example:

```
(gdb) i threads    // To see what processes/threads are running
(gdb) thread 2.1   // To switch to debugging thread of thread id 2.1
```

We can then advance through that thread as we desire. Once we have proceeded as
far as we would like to, we can switch to another thread using the same
`thread` command. For example:

```
(gdb) thread 1.1
```

If, however, we want to advance to a blocking instruction in the thread we are
following before we switch, we simply need to set a breakpoint at the instruction
that immediately follows the blocking instruction, advance the code so it hits
the blocking instruction, `Ctrl-C` to regain access to the `gdb` prompt, and
switch to our other process/thread.

After advancing through the code of the other thread, we can switch back to
the first one in the same manner. If we used `Ctrl-C` on the first thread,
we can return to debugging it by using `continue` which will stop at the
breakpoint we set immediately after the blocking instruction.
