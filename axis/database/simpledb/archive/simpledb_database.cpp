#include "framework.h"


namespace simpledb
{


   database::database(::object * pobject):
      ::object(pobject)
   {

      defer_create_mutex();

      m_protocol = 0;

   }


   database::~database()
   {

      close();

   }


   bool database::initialize()
   {

      return true;

   }

   bool database::connect(
   const char * pszHost,
   const char * pszUser,
   const char * pszPassword,
   const char * pszDatabase,
   i32 iPort,
   const char * pszSocketName,
   u32 uFlags)
   {
      return false;
   }

   bool database::close()
   {
      return false;

   }

   string database::error1(const ::string & pszPrefix)
   {
      return "";
   }

   void database::trace_error1(const ::string & pszPrefix)
   {

      m_strLastError += error1(pszPrefix);

      FORMATTED_TRACE("%s", m_strLastError);

   }


   __pointer(result) database::query(const ::string & pszSql)
   {

      return nullptr;

   }


   ::payload database::query_item(const ::string & pszSql,::payload varDefault)
   {

      return ::payload(::e_type_null);

   }


   bool database::query_blob(memory_base & memory, const ::string & pszSql)
   {

      return false;

   }


   ::payload database::query_items(const ::string & pszSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_row(const ::string & pszSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_rows(const ::string & pszSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_table_item(const ::string & table, const ::string & item, const ::string &where,::payload notfound)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::get_agent(const ::string & pszTable, const ::string & psz, const ::string & pszUser)
   {

      return ::payload(::e_type_null);

   }


   string database::escape(void * p,strsize iLen)
   {

      return "";

   }


   string database::escape(const ::string & psz)
   {

      return "";

   }


   ::payload database::get_insert_id()
   {

      return -1;

   }


} //   namespace simpledb



