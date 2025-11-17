// Created by camilo on 2025-10-20 00:36 <3ThomasBorregaardSorensen!!
#pragma once


class unique_index;


class CLASS_DECL_ACME unique_index_domain
{
protected:

   friend class unique_index;

   ::interlocked_count m_count;

public:

   unique_index create_unique_index();

};



class CLASS_DECL_ACME unique_index
{
protected:

   
   ::collection::index m_iUniqueIndex;


   friend class unique_index_domain;


   unique_index(unique_index_domain* puniqueindexdomain);
   

public:


   ::collection::index index() const
   {

      return m_iUniqueIndex;

   }

};


