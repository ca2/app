#pragma once


class CLASS_DECL_CA2_DATA db_str_set :
   virtual public ::object
{
public:

   ::mutex                         m_mutex;
   class db_str_set_core *       m_pcore;

   db_str_set(db_server * pserver);
   virtual ~db_str_set();


   bool load(const ::string & lpKey, string &strValue);
   bool save(const ::string & lpKey, const ::string & lpcsz);

   bool erase(const ::string & lpKey);


};




