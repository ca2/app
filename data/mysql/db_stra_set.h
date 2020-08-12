#pragma once


class CLASS_DECL_AURA db_stra_set :
   public ::database::client
{
public:


   i32         m_iMaximumCount;
   ::database::key     m_id;


   db_stra_set(db_server * pdatacentral, ::database::key & id);
   
   
   void get_data(string_array & stra);
   ::count set_data(string_array & stra);

};

