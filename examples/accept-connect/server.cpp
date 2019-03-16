#include "Socket.h"
#include <arpa/inet.h>

int main()
{
  Socket s = Socket(4141);
  s.Listen(1);
  s.Accept();
  s.Close();
  return 0;
}