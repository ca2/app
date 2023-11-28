//
// Created by camilo on 23/12/2022 01:26 <3ThomasBorregaardSorensen!!
//
#pragma once




#if !defined(_DEBUG)


inline i64 particle::increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   auto c = ++m_countReference;

#if REFERENCING_DEBUGGING

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


inline i64 particle::decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   auto c = --m_countReference;

#if REFERENCING_DEBUGGING

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


inline i64 particle::release(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   i64 i = decrement_reference_count(REFERENCING_DEBUGGING_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


inline i64 particle::replace_reference(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   return m_countReference;

}


#endif



