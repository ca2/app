// From _.h by camilo on 2022-09-06 23:27 <3ThomasBorregaardSorensen!!
#pragma once




#ifdef __cplusplus


class CLASS_DECL_ACME int_handle
{
public:


   int m_i;

   int_handle(int i = -1)
   {

      m_i = i;

   }

   ~int_handle();


   operator int() const {return m_i;}
   operator int &() {return m_i;}


};


#endif


//#if !defined(WINDOWS)
//
//
//#include "pmutex_lock.h"
//
//
//#endif


#include "datetime_c.h"


#include "ansios_file.h"


#include "file_raw.h"




