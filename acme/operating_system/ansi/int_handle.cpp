// From file.cpp by camilo on 2022-09-06 23:27 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "int_handle.h"


#if !defined(WINDOWS)


#include <unistd.h>


int_handle::~int_handle()
{

   if (m_i >= 0)
   {

      ::close(m_i);

      m_i = -1;

   }

}


#endif

