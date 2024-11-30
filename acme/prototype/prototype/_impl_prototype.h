//
// Created by camilo on 23/12/2022 01:26 <3ThomasBorregaardSorensen!!
//
#pragma once




#if !defined(_DEBUG)


inline huge_integer subparticle::increment_reference_count()
{

   auto c = ++m_countReference;

//#if REFERENCING_DEBUGGING
//
//   add_ref_history(pReferer, pszObjRefDbg);
//
//#endif

   return c;

}


inline huge_integer subparticle::decrement_reference_count()
{

   auto c = --m_countReference;

//#if REFERENCING_DEBUGGING
//
//   if (c > 0)
//   {
//
//      dec_ref_history(pReferer, pszObjRefDbg);
//
//   }
//
//#endif

   return c;

}


inline huge_integer subparticle::release()
{

   huge_integer i = decrement_reference_count();

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


inline huge_integer subparticle::replace_reference()
{

   return m_countReference;

}


#endif



