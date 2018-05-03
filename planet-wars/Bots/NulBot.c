#include<stdio.h>
//#include <fildes.h>
#include <fcntl.h>

void NulBot()
{
  char buff[]="go";
  write(stdout,&buff,2);
}

int main()
{
  NulBot();
  return 0;
}
