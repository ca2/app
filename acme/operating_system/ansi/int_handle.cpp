// From file.cpp by camilo on 2022-09-06 23:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "int_handle.h"


#if !defined(WINDOWS)


#include <unistd.h>


int_handle::~int_handle()
{

   if (m_i32 >= 0)
   {

      ::close(m_i32);

      m_i32 = -1;

   }

}


#endif

