#include <stdio.h>

int main()
{
   char buf[BUFSIZ];

   setbuf(stdout, buf);
   puts("This is runoob");

   fflush(stdout);
   return(0);
}
