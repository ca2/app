#include "framework.h"


db_set::db_set(db_server * pserver, const ::string & pszTable)
{

   m_pdataserver = pserver;

   __pointer(::sqlite::database) pdb   = db()->get_database();

   if(pdb != nullptr)
   {

      m_pdataset = (__pointer(::sqlite::dataset)) pdb->create_dataset();

   }

   m_strTable = pszTable;

}


db_set::~db_set()
{


}


db_server * db_set::db()
{

   return dynamic_cast < db_server * > (m_pdataserver);

}



simpledb_set::simpledb_set(db_server * pserver, const ::string & pszTable)
{
   m_pdataserver = pserver;
   ::simpledb::database * pdb   = db()->m_pbase;
   m_pdataset = (::simpledb::dataset *) pdb->create_dataset();
   m_strTable = pszTable;
   
   //create Integer Table if necessary
   /*try
   {
      pdb->start_transaction();
      m_pdataset->query("select * from sqlite_master where type like 'table' and name like '" + m_strTable + "'");
      if (m_pdataset->num_rows()==0)
      {
         m_pdataset->exec("create table integertable (id text primary key, value integer)");
      }
      pdb->commit_transaction();
   }
   catch (...)
   {
      pdb->rollback_transaction();
      return;
   }*/
}

simpledb_set::~simpledb_set()
{

}

db_server * simpledb_set::db()
{
   return dynamic_cast < db_server * > (m_pdataserver);
}
