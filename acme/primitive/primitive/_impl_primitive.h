//
// Created by camilo on 23/12/2022 01:26 <3ThomasBorregaardSørensen!!
//
#pragma once


template < typename T >
inline i64 release(T*& p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
{

   if (::is_null(p))
   {

      return -1;

   }

   ::particle* pparticle = p;

   try
   {

      p = nullptr;

   }
   catch (...)
   {

      ::output_debug_string("exception release p = nullptr; \n");

   }

   try
   {

      return pparticle->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }
   catch (...)
   {

      ::output_debug_string("exception release pparticle->release() \n");

   }

   return -1;

}


template < typename T >
inline i64 global_release(T*& p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
{

   if (::is_null(p))
   {

      return -1;

   }

   try
   {

      auto i = p->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      if (i <= 0)
      {

         p = nullptr;

      }

      return i;

   }
   catch (...)
   {

      ::output_debug_string("exception release pparticle->release() \n");

   }

   return -1;

}






#if !defined(_DEBUG)


inline i64 particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


inline i64 particle::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
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


inline i64 particle::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif



