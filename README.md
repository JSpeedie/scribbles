# scribbles
A collection of code snippets or examples for my personal reference

## basic-socket-client-server/

This is a skeleton client/server pair using sockets.

#### Compilation

```bash
cd basic-socket-client-server/
make
```
This will compile both the `client` and `server` binaries in the current directory

#### Running

In one terminal, start the server:

```bash
cd basic-socket-client-server/
./server <listen-port>
```

For example:

```bash
./server 45678
```

In another terminal, start the client:

```
cd basic-socket-client-server/
./client <server-ip> <server-listen-port>
```

For example: (and make sure you run the server first)

```bash
./client 127.0.0.1 45678
```

If your client says its connection was denied, make sure you entered the same
port for both your server and client. If you did, try a different port.
