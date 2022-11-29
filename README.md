# Logging-TCP-Server-using-SFML-cpp

In real world applications debug/status messages from applications are often sent to a central logging server so that any issues that may occur can be investigated as to the cause.

Client:
The client console program takes as a command line argument the IP Address and port number of the server.
It continuously prompts the user for messages to send to the server. The client disconnects and terminates when the user enters the message: quit 

Server:
The program takes as a single command line argument the port number on which the TCP Server will listen for connection requests. The server is able to maintain connections from any number of clients.
The clients will send text string messages which the server saves in a file called server.log in the same directory as the server application.

The messages are logged as follows: date & time :: ip_address of client :: message string

The server logs when clients connect and disconnect using the following format:   Sun Nov 6 20:07:41 2022 :: 192.168.1.1 :: Connected 

(The programs also check for invalid entries like Negative port numbers, Non numeric values, Port number outside the range 61000-65535)
