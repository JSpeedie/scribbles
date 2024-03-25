# Extras

# 1. Turning on the TUI

After starting `gdb`, if my config doesn't make `gdb` start in TUI mode,
I like to fix that by bringing up the source code for reference:

```
(gdb) layout src
```

Note: that this will change the function of the arrow keys such that they move
the code window rather than cycling through previous commands. To go through
past commands, use Ctrl-p and Ctrl-n (for up and down) and Alt-b and Alt-f (for
left and right).


## 2. Changing the TUI

You can change the height of the source code window using the command

```
(gdb) wh src 20
(gdb) wh src +6
(gdb) wh src -6
```

20 is a good value for most situations I think, but more important is knowing
how to change this as needed.
