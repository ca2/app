// Created by camilo:hi5! on 2024-05-07 10:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "interlocked_count.h"


namespace ace
{

class context;

}// namespace ace

void information_log(const char * psz);
void informationf_log(const char * psz,...);
void error_log(const char * psz);
void errorf_log(const char * psz,...);


class CLASS_DECL_ACME quantum
{
public:


   mutable ::ace::context *         m_pcontext;
   ::interlocked_count              m_countReference;

   quantum():m_pcontext{nullptr},
   m_countReference{1
      }
   {}
   virtual ~quantum();



   void information_log(const char * psz);
   void informationf_log(const char * psz,...);
   void error_log(const char * psz);
   void errorf_log(const char * psz,...);



};