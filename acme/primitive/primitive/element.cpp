// Created by camilo on 2021-08-01 23:42 Thomas Month!! <3ThomasBS__!!
#include "framework.h"


#ifdef _DEBUG


i64 element::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 element::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = --m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


i64 element::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif


::e_status element::call_member(::i64 iId)
{

   return ::success_none;

}


//::e_status matter::handle(enum_message emessage, i64 iData, ::matter * pmatter)
//{
//
//   return ::success;
//
//}
//


void element::handle(::subject * psubject, ::context * pcontext)
{


}


void element::handle(::message::message * pmessage)
{


}



