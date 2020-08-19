#include "framework_c.h"


off_t tell64(int fd)
{

   return lseek(fd, 0, SEEK_CUR);

}
