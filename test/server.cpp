#include "../lib/Socket.h"

int main()
{
  Socket s = Socket(AF_INET, SOCK_STREAM);
  s.Bind("127.0.0.1", 25);
  s.Listen(10);

  struct sockaddr *address;
  socklen_t *address_len;

  getpeername(s.GetSockfd(), address, address_len);

  address->sa_family;
  // nprintf("sa_family:\t  %p\n", address->sa_family);

  s.Close();
  return 0;
}