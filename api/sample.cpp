// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <map>
// #include <netinet/in.h>
// #include <unistd.h>
// #include <cstring>

// class HttpServer
// {
// public:
//     HttpServer(int port) : port_(port) {}

//     void start()
//     {
//         int server_fd, new_socket;
//         struct sockaddr_in address;
//         int addrlen = sizeof(address);

//         if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//         {
//             perror("socket failed");
//             exit(EXIT_FAILURE);
//         }

//         address.sin_family = AF_INET;
//         address.sin_addr.s_addr = INADDR_ANY;
//         address.sin_port = htons(port_);

//         if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
//         {
//             perror("bind failed");
//             exit(EXIT_FAILURE);
//         }

//         if (listen(server_fd, 10) < 0)
//         {
//             perror("listen failed");
//             exit(EXIT_FAILURE);
//         }

//         while (true)
//         {
//             if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
//             {
//                 perror("accept failed");
//                 exit(EXIT_FAILURE);
//             }

//             char buffer[1024] = {0};
//             read(new_socket, buffer, 1024);

//             std::string response = handleRequest(buffer);

//             send(new_socket, response.c_str(), response.length(), 0);
//             close(new_socket);
//         }
//     }

// private:
//     int port_;

//     std::string handleRequest(const char *request)
//     {
//         std::istringstream iss(request);
//         std::string method, path, http_version;
//         iss >> method >> path >> http_version;

//         if (method == "GET" && path == "/")
//         {
//             return "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, World!";
//         }
//         else
//         {
//             return "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
//         }
//     }
// };

// int main()
// {
//     HttpServer server(8080);
//     server.start();
//     return 0;
// }