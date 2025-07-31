#include "framework.h"


namespace simpledb
{


   database::database(::particle * pparticle):
      ::object(pparticle)
   {

      defer_create_synchronization();

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
   const ::scoped_string & scopedstrHost,
   const ::scoped_string & scopedstrUser,
   const ::scoped_string & scopedstrPassword,
   const ::scoped_string & scopedstrDatabase,
   int iPort,
   const ::scoped_string & scopedstrSocketName,
   unsigned int uFlags)
   {
      return false;
   }

   bool database::close()
   {
      return false;

   }

   string database::error1(const ::scoped_string & scopedstrPrefix)
   {
      return "";
   }

   void database::trace_error1(const ::scoped_string & scopedstrPrefix)
   {

      m_strLastError += error1(scopedstrPrefix);

      informationf("%s", m_strLastError);

   }


   ::pointer<result>database::query(const ::scoped_string & scopedstrSql)
   {

      return nullptr;

   }


   ::payload database::query_item(const ::scoped_string & scopedstrSql,::payload varDefault)
   {

      return ::payload(::e_type_null);

   }


   bool database::query_blob(memory_base & memory, const ::scoped_string & scopedstrSql)
   {

      return false;

   }


   ::payload database::query_items(const ::scoped_string & scopedstrSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_row(const ::scoped_string & scopedstrSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_rows(const ::scoped_string & scopedstrSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_table_item(const ::string & table, const ::string & item, const ::string &where,::payload notfound)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrUser)
   {

      return ::payload(::e_type_null);

   }


   string database::escape(void * p,character_count iLen)
   {

      return "";

   }


   string database::escape(const ::scoped_string & scopedstr)
   {

      return "";

   }


   ::payload database::get_insert_id()
   {

      return -1;

   }


} //   namespace simpledb



