# IPC_USINNG_SOCKET

# Inter Process Communication (IPC) Using Sockets

## Introduction

Inter Process Communication (IPC) using sockets is a communication mechanism provided by the operating system that enables two or more independent processes to exchange data through network-based communication endpoints.

A socket acts as a bidirectional communication channel between processes. Unlike shared memory, processes communicating through sockets do not share memory directly. Instead, data is transferred through kernel-managed buffers and network protocols such as TCP.

Sockets are widely used in client-server applications, distributed systems, and network programming because they support communication both within the same machine and across different systems.

The study focused on understanding:

* Socket creation
* Connection establishment
* Data transfer
* Communication flow between client and server processes

---

# IPC Using Sockets

## Socket Fundamentals

A socket is a kernel-managed communication endpoint backed by a file descriptor.

When the `socket()` system call is executed:

* The kernel allocates an internal socket structure
* Send and receive buffers are created
* An integer file descriptor (`fd`) is returned

All communication operations such as:

* `read()`
* `write()`
* `send()`
* `recv()`
* `select()`
* `poll()`

operate using this socket descriptor.

---

## Key Insight

Processes communicating through sockets never access each other’s memory directly.

Instead:

1. One process writes data to the socket
2. Data enters the kernel send buffer
3. The TCP/IP stack transfers the data
4. The receiving process obtains the data from the receive buffer

This mechanism ensures:

* Process isolation
* Secure communication
* Reliable data transfer

---

# Socket Functions Studied

## 1. `socket()`

```c
socket(domain, type, protocol);
```

### Purpose

* Creates a socket endpoint
* Allocates kernel resources
* Returns a socket file descriptor

### Observation

No actual network communication happens during socket creation.

---

## 2. `bind()`

```c
bind(fd, addr, len);
```

### Purpose

* Assigns an IP address and port number to the socket
* Mostly used on the server side

### Observation

Without `bind()`, the operating system automatically assigns an ephemeral port.

---

## 3. `listen()`

```c
listen(fd, backlog);
```

### Purpose

* Converts the socket into listening mode
* Allows the server to wait for incoming client connections

### Observation

The `backlog` parameter determines the size of the pending connection queue.

---

## 4. `accept()`

```c
accept(fd, addr, len);
```

### Purpose

* Accepts incoming client connections
* Returns a new socket descriptor for communication

### Observation

The function blocks until a client attempts connection.

---

## 5. `connect()`

```c
connect(fd, addr, len);
```

### Purpose

Used by the client process to establish a connection with the server.

### Observation

Initiates the TCP three-way handshake between client and server.

---

## 6. `read()` / `write()` / `send()` / `recv()`

### Purpose

Used for exchanging data between client and server.

### Observation

Data transfer occurs through kernel-managed buffers.

---

## 7. `close()`

```c
close(fd);
```

### Purpose

* Terminates socket communication
* Releases kernel resources

### Observation

TCP FIN packets are exchanged during connection termination.

---

# Socket Communication Workflow

## Server Side Workflow

1. Create socket using `socket()`
2. Bind socket using `bind()`
3. Enable listening using `listen()`
4. Accept client connection using `accept()`
5. Exchange data using `read()` and `write()`
6. Close socket using `close()`

---

## Client Side Workflow

1. Create socket using `socket()`
2. Connect to server using `connect()`
3. Send and receive messages
4. Close socket connection

---

# Terminal-Based Socket IPC Demonstration

## Server Terminal

```bash
cd demo
./server
```

### Output

```bash
[Server] Listening on port 8080
```

---

## Client Terminal

```bash
cd demo
./client
```

### Output

```bash
[Client] Connected to 127.0.0.1:8080
```

---

# Example Communication

## Client Sends Message

```text
Hello Shubh
```

## Server Receives

```text
read() -> "Hello Shubh"
```

## Server Sends Echo Response

```text
[echo] Hello Shubh
```

## Client Receives Response

```text
recv() -> "[echo] Hello Shubh"
```

---

# Advantages of Socket IPC

* Enables communication between different systems
* Supports full duplex communication
* Suitable for distributed applications
* Scalable using advanced I/O multiplexing techniques
* Provides secure and isolated communication

---

# Limitations

* Slower than shared memory communication
* Involves kernel-level data copying
* Network latency may affect performance
* More complex than pipes

---

# Observations

* Socket IPC enables reliable communication between isolated processes
* TCP sockets provide connection-oriented communication
* Kernel buffers manage secure data transfer
* Client-server architecture forms the basis of network applications
* Timing behavior can reveal process communication patterns

---

# Challenges Faced

* Understanding TCP connection establishment
* Managing blocking socket calls
* Handling synchronization between client and server
* Understanding kernel-level buffering and communication flow
* Interpreting socket communication timing behavior

---

# Conclusion

The study of IPC using sockets provided practical understanding of process communication using network protocols.

The implementation demonstrated:

* Socket lifecycle management
* Client-server communication
* TCP connection establishment
* Data exchange using kernel buffers
* Reliable communication between independent processes

This study enhanced understanding of:

* Networking concepts
* Operating system communication mechanisms
* Real-world distributed system design
