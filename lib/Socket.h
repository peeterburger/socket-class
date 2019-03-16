// Basic socket functions
#include <sys/socket.h>
// To create sockaddr
#include <netinet/in.h>
// Basic i/o
#include <stdio.h>
// To close a socket
#include <unistd.h>

class Socket
{
private:
  int address_family;
  __socket_type type;
  int protocol;
  int sockfd;

public:
  int GetDomain() const { return address_family; }
  __socket_type GetType() const { return type; }
  int GetProtocol() const { return protocol; }
  int GetSockfd() const { return sockfd; }

private:
  Socket()
  {
  }

public:
  Socket(int port) : Socket::Socket(AF_INET, SOCK_STREAM, 0)
  {
    Socket::Bind(INADDR_ANY, port);
  }

  Socket(int address_family, __socket_type type, int protocol = 0) : address_family(address_family), type(type), protocol(protocol)
  {
    sockfd = socket(address_family, type, protocol);
  }

public:
#pragma region conventional wrapping

  int Accept(struct sockaddr *address, socklen_t *address_len)
  {
    return accept(sockfd, address, address_len);
  }

  int Bind(const struct sockaddr *address, socklen_t address_len)
  {
    return bind(sockfd, address, address_len);
  }

  int Connect(const struct sockaddr *address, socklen_t address_len)
  {
    return connect(sockfd, address, address_len);
  }

  int GetPeerName(struct sockaddr *address, socklen_t *address_len)
  {
    return getpeername(sockfd, address, address_len);
  }

  int GetSockOpt(int level, int option_name, void *option_value, socklen_t *option_len)
  {
    return getsockopt(sockfd, level, option_name, option_value, option_len);
  }

  int Listen(int backlog)
  {
    return listen(sockfd, backlog);
  }

  ssize_t Receive(void *buffer, size_t length, int flags)
  {
    return recv(sockfd, buffer, length, flags);
  }

  ssize_t ReceiveFrom(void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len)
  {
    return recvfrom(sockfd, buffer, length, flags, address, address_len);
  }

  ssize_t ReceiveMessage(struct msghdr *message, int flags)
  {
    return recvmsg(sockfd, message, flags);
  }

  ssize_t Send(const void *buffer, size_t length, int flags)
  {
    return send(sockfd, buffer, length, flags);
  }

  ssize_t SendMessage(const struct msghdr *message, int flags)
  {
    return sendmsg(sockfd, message, flags);
  }

  ssize_t SendTo(const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len)
  {
    return sendto(sockfd, message, length, flags, dest_addr, dest_len);
  }

  int SetOpt(int level, int option_name, const void *option_value, socklen_t option_len)
  {
    return setsockopt(sockfd, level, option_name, option_value, option_len);
  }

  int Shutdown(int how)
  {
    return shutdown(sockfd, how);
  }

#pragma endregion

#pragma region simplified conventional wrapping

#pragma endregion

#pragma region OO wrapping

  Socket Accept()
  {
    struct sockaddr *new_address;
    socklen_t *address_len;
    int newsockfd = Socket::Accept(new_address, address_len);

    // Error on accept
    if (newsockfd == -1)
    {
      return Socket();
    }

    Socket s = Socket();
    s.address_family = address_family;
    s.type = type;
    s.protocol = protocol;
    s.sockfd = newsockfd;

    return s;
  }

  int Bind(in_addr_t addr, in_port_t port)
  {
    struct sockaddr_in in_addr;
    in_addr.sin_family = address_family;
    in_addr.sin_addr.s_addr = addr;
    in_addr.sin_port = htons(port);
    return Socket::Bind((struct sockaddr *)&in_addr, sizeof(in_addr));
  }

  int Connect(in_addr_t addr, in_port_t port)
  {
    struct sockaddr_in in_addr;
    in_addr.sin_family = address_family;
    in_addr.sin_addr.s_addr = addr;
    in_addr.sin_port = htons(port);
    return Socket::Connect((struct sockaddr *)&in_addr, sizeof(in_addr));
  }

  int Shutdown()
  {
    return Socket::Shutdown(SHUT_RDWR);
  }

#pragma endregion

#pragma region additional functions

  int Close()
  {
    return close(sockfd);
  }

#pragma endregion
};