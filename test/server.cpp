#include "../lib/Socket.h"

int main()
{
  Socket s = Socket(AF_INET, SOCK_STREAM);
  s.Bind("127.0.0.1", 4141);
  s.Listen(1);
  s.Accept();
  s.Close();
  return 0;
}