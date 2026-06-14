# IPC_USINNG_SOCKET

Introduction
Inter Process Communication (IPC) using sockets is a communication mechanism provided by the operating system that enables two or more independent processes to exchange data through network-based communication endpoints.
A socket acts as a bidirectional communication channel between processes. Unlike shared memory, processes communicating through sockets do not share memory directly. Instead, data is transferred through kernel-managed buffers and network protocols such as TCP.
Sockets are widely used in client-server applications, distributed systems, and network programming because they support communication both within the same machine and across different systems.
The study focused on understanding socket creation, connection establishment, data transfer, and communication flow between client and server processes.


IPC Using Sockets
Socket Fundamentals
A socket is a kernel-managed communication endpoint backed by a file descriptor.
When the socket() system call is executed:
The kernel allocates an internal socket structure.
Send and receive buffers are created.
An integer file descriptor (fd) is returned.
All communication operations such as:
read()
write()
send()
recv()
select()
poll()
operate using this socket descriptor.

Key Insight
Processes communicating through sockets never access each other’s memory directly.
Instead:
One process writes data to the socket.
Data enters the kernel send buffer.
The TCP/IP stack transfers the data.
The receiving process obtains the data from the receive buffer.
This mechanism ensures process isolation and secure communication.


Socket Functions Studied
1. socket()
socket(domain, type, protocol);
Purpose
Creates a socket endpoint.
Allocates kernel resources.
Returns a socket file descriptor.
Observation
No actual network communication happens during socket creation.

2. bind()
bind(fd, addr, len);
Purpose
Assigns an IP address and port number to the socket.
Mostly used on the server side.
Observation
Without bind(), the operating system automatically assigns an ephemeral port.

3. listen()
listen(fd, backlog);
Purpose
Converts the socket into listening mode.
Allows the server to wait for incoming client connections.
Observation
The backlog parameter determines the size of the pending connection queue.

4. accept()
accept(fd, addr, len);
Purpose
Accepts incoming client connections.
Returns a new socket descriptor for communication.
Observation
The function blocks until a client attempts connection.

5. connect()
connect(fd, addr, len);
Purpose
Used by the client process to establish connection with the server.
Observation
Initiates TCP three-way handshake between client and server.

6. read() / write() / send() / recv()
Purpose
Used for exchanging data between client and server.
Observation
Data transfer occurs through kernel-managed buffers.

7. close()
close(fd);
Purpose
Terminates socket communication.
Releases kernel resources.
Observation
TCP FIN packets are exchanged during connection termination.

Socket Communication Workflow
Server Side Workflow
Create socket using socket()
Bind socket using bind()
Enable listening using listen()
Accept client connection using accept()
Exchange data using read() and write()
Close socket using close()

Client Side Workflow
Create socket using socket()
Connect to server using connect()
Send and receive messages
Close socket connection

Terminal-Based Socket IPC Demonstration
Server Terminal
cd demo
./server
Output
[Server] Listening on port 8080

Client Terminal
cd demo
./client
Output
[Client] Connected to 127.0.0.1:8080

Example Communication
Client Sends Message
Hello Shubh
Server Receives
read() -> "Hello Shubh"
Server Sends Echo Response
[echo] Hello Shubh
Client Receives Response
recv() -> "[echo] Hello Shubh"

Advantages of Socket IPC
Enables communication between different systems.
Supports full duplex communication.
Suitable for distributed applications.
Scalable using advanced I/O multiplexing techniques.
Provides secure and isolated communication.

Limitations
Slower than shared memory communication.
Involves kernel-level data copying.
Network latency may affect performance.
More complex than pipes.

Observations
Socket IPC enables reliable communication between isolated processes.
TCP sockets provide connection-oriented communication.
Kernel buffers manage secure data transfer.
Client-server architecture forms the basis of network applications.
Timing behavior can reveal process communication patterns.

Challenges Faced
Understanding TCP connection establishment.
Managing blocking socket calls.
Handling synchronization between client and server.
Understanding kernel-level buffering and communication flow.
Interpreting socket communication timing behavior.

Conclusion
The study of IPC using sockets provided practical understanding of process communication using network protocols.
The implementation demonstrated:
Socket lifecycle management
Client-server communication
TCP connection establishment
Data exchange using kernel buffers
Reliable communication between independent processes
This study enhanced understanding of networking concepts, operating system communication mechanisms, and real-world distributed system design.
