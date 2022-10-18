// Created by camilo on 2022-10-14 20:32 <3ThomasBorregaardSorensen
#pragma once


template < typename POSTING_OBJECT, typename POSTING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD >
bool __material_get_posted_payload_synchronously(material_object * phandler, POSTING_OBJECT pposting, POSTING_METHOD posting_method, OBJECT_POINTER preturning, OBJECT_METHOD returning_method, ::payload & payload, const class ::wait & wait)
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

   functionReturn.m_waitTimeout = wait;

   return phandler->__get_posted_payload_synchronously(functionPost, functionReturn, payload);

}


template < typename POSTING_OBJECT, typename POSTING_METHOD >
void __material_send_procedure(material_object * phandler, POSTING_OBJECT pposting, POSTING_METHOD posting_method, const ::procedure & procedure)
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



