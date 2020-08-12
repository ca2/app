#pragma once

class db_server;

class CLASS_DECL_AURA db_set :
   virtual public ::database::client
{
public:
   db_server *            db();
   db_set(db_server * pserver, const char * pszTable);
   virtual ~db_set();

   sqlite::set *    m_pdataset;
   string               m_strTable;


};


class CLASS_DECL_AURA simpledb_set :
   virtual public ::database::client
{
public:

   simpledb_set(db_server * pserver, const char * pszTable);
   virtual ~simpledb_set();

   db_server *            db();

   simpledb::set *     m_pdataset;
   string            m_strTable;

};
