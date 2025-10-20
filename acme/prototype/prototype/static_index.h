// Created by camilo on 2025-10-20 00:36 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME static_index
{
protected:

   
   static ::interlocked_count s_count;

   ::collection::index m_iStaticIndex;

public:


   static_index();


   ::collection::index index() const
   {

      return m_iStaticIndex;

   }

};


