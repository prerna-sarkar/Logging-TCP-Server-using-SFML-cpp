/*
Description:
'TCP Sockets: Debug Logging Server' - TCP_Server
*/

#include<SFML/Network.hpp>
#include<iostream>
#include<list>
#include<thread>
#include<iterator>
#include<fstream>
#include<ctime>
#include <string.h>

std::list<sf::TcpSocket*> listClients; // list to store pointers to the (sockets) clients
sf::SocketSelector selector; // create a selector
int port = 0;
std::ofstream ofile("server.log", std::ios::out | std::ios::app); // create output log file

int main(int argc, char* argv[])
{
    // get the listening port number as a command line argument
    bool invalidPort = false;
    if (argc != 2 || atoi(argv[1]) > 65535 || atoi(argv[1]) < 61000) // incorrect number of cmd args / out of range / negative => invalid
    {
        invalidPort = true;
    }
    else
    {
        for (int i = 0; i < std::strlen(argv[1]); i++) // non-integer => invalid
        {
            if (!isdigit(argv[1][i]))
            {
                invalidPort = true;
                break;
            }
        }
    }
    if (invalidPort)
    {
        std::cout << "Invalid command line argument detected: " << argv[1] << std::endl;
        std::cout << "Please check your values and press any key to end the program!" << std::endl;
        std::cin.get();
        return 1;
    }
    else
    {
        port = atoi(argv[1]);
    }

    sf::TcpListener listener; // socket to listen to new connections

    if (listener.listen(port) != sf::Socket::Done) // bind the listener to the listening port
        std::cout << "Error in binding the listener to the port specified" << std::endl;
    std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

    selector.add(listener); // add the listener to the selector

    while (true) // accept connections in a while loop
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket* client = new sf::TcpSocket;

                if (listener.accept(*client) != sf::Socket::Done)
                {
                    std::cout << "Error in accepting connection" << std::endl;
                    delete client;
                }
                else
                {
                    listClients.emplace_back(client); // add pointer to the new client to the list of client pointers
                    selector.add(*client);

                    time_t nowConnect = time(0); //date and time as per current system
                    char* timeConnect = ctime(&nowConnect); //convert to string
                    timeConnect[strcspn(timeConnect, "\n")] = '\0';

                    ofile << timeConnect << " :: " << (*client).getRemoteAddress() << " :: Connected" << std::endl;
                }
            }
            else
            {
                std::list<sf::TcpSocket*>::iterator it;

                for (it = listClients.begin(); it != listClients.end();)
                {
                    sf::TcpSocket& client = **it;
                    if (selector.isReady(client))
                    {
                        sf::TcpSocket& socket = **it;
                        char message[128] = { 0 };
                        std::size_t received;

                        auto status = socket.receive(message, sizeof(message), received);
                        if (status == sf::Socket::Done)
                        {
                            std::string str = ""; //The clients will be sending text string messages
                            str = message;

                            time_t nowMsg = time(0); //date and time as per current system
                            char* timeMsg = ctime(&nowMsg); //convert to string
                            timeMsg[strcspn(timeMsg, "\n")] = '\0';

                            ofile << timeMsg << " :: " << socket.getRemoteAddress() << " :: " << str << std::endl; // append msg to log file
                            it++;
                        }
                        else if (status == sf::Socket::Disconnected)
                        {
                            time_t nowDisconnect = time(0); //date and time as per current system
                            char* timeDisconnect = ctime(&nowDisconnect); //convert to string
                            timeDisconnect[strcspn(timeDisconnect, "\n")] = '\0';

                            ofile << timeDisconnect << " :: " << socket.getRemoteAddress() << " :: Disconnected" << std::endl;

                            //socket.disconnect();
                            selector.remove(socket);
                            it = listClients.erase(it);
                        }
                        else
                            it++;
                    }
                    else
                        it++;
                }
            }
        }
        //else
          //  std::cout << "Failed\n";
    }
}
