#include <sys/socket.h>
#include <string>

class SocketAddress
{
private:
  sa_family_t sa_family;
  std::string sa_data;

public:
  SocketAddress(struct sockaddr *address)
  {
    sa_family = address->sa_family;
    sa_data = address->sa_data;
  }

  sa_family_t GetAddressFamily()
  {
    return sa_family;
  }

  std::string GetAddress()
  {
    return sa_data;
  }
};