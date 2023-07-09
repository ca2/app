// Created by camilo on 2023-07-09 02:06 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/primitive/datetime/file_time.h"
#include "acme/primitive/datetime/system_time.h"


posix_time::posix_time(const ::file_time & filetime, i32 nDST) :
   posix_time(system_time(filetime), nDST)
{

}


posix_time::posix_time(const system_time & systemtime, i32 nDST)
{



}



