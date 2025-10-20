// Created by camilo on 2025-10-20 00:36 <3ThomasBorregaardSorensen!!
#pragma once


class static_index;


class CLASS_DECL_ACME static_index_source
{
public:

   
   ::interlocked_count m_count;


   static_index create_static_index();


};


class CLASS_DECL_ACME static_index
{
protected:

   
   friend class static_index_source;


   ::collection::index m_iStaticIndex;

   static_index(static_index_source* pstaticindexsource);


public:


   ::collection::index index() const
   {

      return m_iStaticIndex;

   }

};


