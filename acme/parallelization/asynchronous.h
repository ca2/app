// Created by camilo on 2022-10-14 20:32 <3ThomasBorregaardSorensen
#pragma once


#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/primitive/function.h"
//#include "acme/primitive/primitive/matter.h"


template < typename POSTING_OBJECT, typename POSTING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD >
bool __matter_get_posted_payload_synchronously(matter * phandler, POSTING_OBJECT pposting, POSTING_METHOD posting_method, OBJECT_POINTER preturning, OBJECT_METHOD returning_method, ::payload & payload, const class time & timeWait)
{

   if(pposting->is_branch_current())
   {

      payload = (preturning->*returning_method)();

      return true;

   }

   auto posting = [pposting, posting_method](const ::procedure & procedure)
   {

      (pposting->*posting_method)(procedure);

   };

   ::function < void(const ::procedure &) > functionPost(posting);

   ::function < ::payload() > functionReturn([preturning, returning_method]()
   {

      return (preturning->*returning_method)();

   });

   functionReturn.m_timeTimeout = timeWait;

   return phandler->__get_posted_payload_synchronously(functionPost, functionReturn, payload);

}


template < typename POSTING_OBJECT, typename POSTING_METHOD >
void __matter_send_procedure(matter * phandler, POSTING_OBJECT pposting, POSTING_METHOD posting_method, const ::procedure & procedure)
{

   if(pposting->is_branch_current())
   {

      return procedure();

   }

   auto posting = [pposting, posting_method](const ::procedure & procedure)
   {

      (pposting->*posting_method)(procedure);

   };

   phandler->__send_procedure(posting, procedure);

}



