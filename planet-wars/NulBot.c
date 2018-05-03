#include<stdio.h>
//#include <fildes.h>
#include <fcntl.h>


void NulBot()
{
  char buffer[100];
  while(1)
  {
    fgets(buffer,100,stdin);
    if (buffer[0]=='g' && buffer[1]=='o')
    {
      printf("go\n");
    }
  }
}

int main()
{
  setvbuf(stdout, NULL, _IOLBF, 0);
  while(1)
  {
  NulBot();
  }
  return 0;
}
