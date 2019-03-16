#include "Socket.h"
#include <arpa/inet.h>

int main()
{
  Socket s = Socket(AF_INET, SOCK_STREAM, 0);

  if (s.Bind(INADDR_ANY, 8888) < 0)
  {
    perror("BIND");
  }
  if (s.Connect(inet_addr((char *)"127.0.0.1"), 4141))
  {
    perror("CONNECT");
  }

  s.Close();
  return 0;
}