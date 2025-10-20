// Created by camilo on 2025-10-20 00:36 <3ThomasBorregaardSorensen!!
#pragma once



class CLASS_DECL_ACME static_index_seed
{
public:

   
   ::interlocked_count m_count;


};


class CLASS_DECL_ACME static_index
{
public:


   ::collection::index m_iStaticIndex;

   static_index(static_index_seed& staticindexseed)
   {

      m_iStaticIndex = staticindexseed.m_count++;

   }


};



