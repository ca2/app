#pragma once


class CLASS_DECL_AURA db_stra_set :
   public ::database::client
{
public:


   int         m_iMaximumCount;
   ::database::key     id();


   db_stra_set(db_server * pdatacentral, ::database::key & atom);
   
   
   void get_data(string_array_base & stra);
   ::collection::count set_data(string_array_base & stra);

};

