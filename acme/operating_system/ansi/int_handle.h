// From _.h by camilo on 2022-09-06 23:27 <3ThomasBorregaardSorensen!!
#pragma once




#ifdef __cplusplus


class CLASS_DECL_ACME int_handle
{
public:


   ::i32 m_i32;

   int_handle(::i32 i = -1)
   {

      m_i32 = i;

   }

   ~int_handle();


   operator ::i32() const {return m_i32;}
   operator ::i32 &() {return m_i32;}


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




