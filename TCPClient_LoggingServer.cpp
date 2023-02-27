/*
Description:
'TCP Sockets: Debug Logging Server' - TCP_Client
*/

#include <SFML/Network.hpp>
#include <iostream>


int main(int argc, char* argv[])
{
    //IP Address and port number of the server as command line argument: ./a.out localhost 61717
    int port = 0;
    bool invalidPort = false;

    if (argc != 3 || atoi(argv[2]) > 65535 || atoi(argv[2]) < 61000) // incorrect number of cmd args / out of range / negative => invalid
    {
        invalidPort = true;
    }
    else
    {
        for (int i = 0; i < std::strlen(argv[2]); i++) // non-integer => invalid
        {
            if (!isdigit(argv[2][i]))
            {
                invalidPort = true;
                break;
            }
        }
    }
    if (invalidPort)
    {
        std::cout << "Invalid command line argument detected :" << argv[2] << std::endl;
        std::cout << "Please check your values and press any key to end the program!" << std::endl;
        std::cin.get();
        return 1;
    }
    else
    {
        port = atoi(argv[2]);
    }

    sf::IpAddress server = argv[1]; // 1. Create a server with the entered IP address

    sf::TcpSocket socket;  // 2. Create a socket for communicating with the server

    // 3. Connect socket to the server's specified port
    if (socket.connect(server, port) != sf::Socket::Done) //sf::Socket::Done returns 
    {
        std::cout << "Failed to connect to the server at: " << argv[1] << " on " << argv[2] << std::endl;
        std::cout << "Please check your values and press any key to end the program!" << std::endl;
        std::cin.get();
        return 1;
    }

    while (1)  // 4. continuously prompt the user for messages to send to the server
    {
        std::string out;
        std::cout << "Please enter a message: ";
        getline(std::cin, out); 
        if (out == "quit")  //client disconnects and terminates when the user enters the message : quit
        {
            socket.disconnect();
            return 1;
        }
        if (socket.send(out.c_str(), out.size()) != sf::Socket::Done) // 5. Send contents of "out" over the socket connection
            return 1;

    }
}
