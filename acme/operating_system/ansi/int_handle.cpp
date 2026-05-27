// From file.cpp by camilo on 2022-09-06 23:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "i32_handle.h"


#if !defined(WINDOWS)


#include <unistd.h>


i32_handle::~i32_handle()
{

   if (m_i32 >= 0)
   {

      ::close(m_i32);

      m_i32 = -1;

   }

}


#endif

