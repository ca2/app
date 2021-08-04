#include "framework.h"
#include "acme/platform/profiler.h"


namespace mysql
{


   database::database()
   {

      m_uConnectionFlags = 0;

   }


   database::~database()
   {

      close_mysql_database();

   }


   ::e_status database::initialize(::object * pobject)
   {

      auto estatus = ::database::database::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status database::destroy()
   {

      close_mysql_database();

      ::database::database::destroy();

   }


   void * database::get_handle()
   {

      return nullptr;

   }


   bool database::initialize()
   {

      return true;

   }


   ::e_status database::_connect()
   {

      return ::error_interface_only;

   }


   bool database::close_mysql_database()
   {

      return false;

   }


   string database::error1(const ::string & pszPrefix)
   {

      return "";

   }


   bool database::exec(const ::string & pszSql)
   {

      m_strLastError = "";

      m_iLastError = -1;

      return false;

   }


   __pointer(::database::result_set) database::query_result(const ::string & pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      return nullptr;

   }


   ::payload database::query_item(const ::string & pszSql, ::payload varDefault)
   {

      return error_interface_only;

   }


   bool database::query_blob(memory_base & memory, const ::string & pszSql)
   {

      return false;

   }


   __pointer(payload_array) database::query_items(const ::string & pszSql)
   {

      return nullptr;

   }


   __pointer(::database::row) database::query_row(const ::string & pszSql)
   {

      return nullptr;

   }


   __pointer(::database::row_array) database::query_rows(const ::string & pszQuery)
   {

      return nullptr;

   }


   ::payload database::query_table_item(const ::string & table, const ::string & item, const ::string &where, ::payload notfound)
   {

      return error_interface_only;

   }


   ::payload database::get_agent(const ::string & pszTable, const ::string & psz, const ::string & pszUser)
   {

      return error_interface_only;

   }


   ::count database::get_affected_rows_count()
   {

      return -1;

   }


   string database::escape(void * p, strsize iLen)
   {

      return "";

   }


   string database::escape(const ::string & psz)
   {

      return "";

   }


   ::payload database::get_insert_id()
   {
      
      return error_interface_only;

   }


} //   namespace mysql



