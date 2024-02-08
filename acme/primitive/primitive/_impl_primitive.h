//
// Created by camilo on 23/12/2022 01:26 <3ThomasBorregaardSorensen!!
//
#pragma once




#if !defined(_DEBUG)


inline i64 subparticle::increment_reference_count()
{

   auto c = ++m_countReference;

#if REFERENCING_DEBUGGING

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


inline i64 subparticle::decrement_reference_count()
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


inline i64 subparticle::release()
{

   i64 i = decrement_reference_count();

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


inline i64 subparticle::replace_reference()
{

   return m_countReference;

}


#endif



