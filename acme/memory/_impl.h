// Created by Camilo on 2021-01-12 ~10:00 <3TBS
#pragma once


namespace str
{


   template < typename POINTER >
   inline void from(string & str, const ::acme::memory_alloc < POINTER > & memoryallocpointer)
   {

      from(str, memoryallocpointer.m_p);

   }


} // namespace str



