# Logging-TCP-Server-using-SFML-cpp

In real world applications debug/status messages from applications are often sent to a central logging server so that any issues that may occur can be investigated as to the cause.

This is a C++ program that creates a TCP server that listens to incoming connections and logs the messages sent by the connected clients to a log file. A C++ client program that connects to a server via TCP sockets and allows the user to send messages to the server is also included.

# Requirements
This program uses the SFML network library to create and manage the sockets. Therefore, you need to have SFML installed on your machine to be able to compile and run this program.

You can download SFML from the official website.

# Usage

The server program requires the port number as a command line argument. The valid range of port numbers is from 61000 to 65535. Example usage:
 ./tcp_server <port_number>

The client program requires two command line arguments: the IP address of the server and the port number to connect to. Example usage:
./a.out localhost 61717

# Functionality

SERVER PROGRAM:

1. A TcpListener object listener is created and bound to the entered port to listen to new connections.

2. The listener is added to a SocketSelector object selector that waits for events on the sockets in an infinite loop.

3. If an event is detected, the code checks whether it is a new connection request or a message from an existing client.

4. If the event is a new connection request, the code accepts the connection and adds the client's socket to the list of active clients. It also logs the connection event to a file.

5. If the event is a message from an existing client, the code receives the message and logs it to the file. If the client has disconnected, the code removes the corresponding client from the list of active clients and logs the disconnection event.

Logging example: Sun Nov 6 20:07:41 2022 :: 192.168.1.1 :: Connected 

6. The program continuously loops, waiting for new connections and incoming data from any number of clients, until it is terminated by the user.

If the entered command line arguments is not a valid integer or is not within the valid range of port numbers, the program will output an error message and terminate.

CLIENT PROGRAM:

1. The program creates a server with the entered IP address.

2. A socket is created for communicating with the server.

3. The socket is connected to the server's specified port.

4. The program continuously prompts the user for messages to send to the server.

5. The contents of the message are sent over the socket connection to the server.

6. The client program can be terminated by entering "quit" as the message.

If the entered command line arguments are invalid, the program will output an error message and terminate.

# License

This project is licensed under the MIT License. Please see the LICENSE file for more information.
