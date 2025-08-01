#include "framework.h"
#include "database.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/string/base64.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "axis/database/database/result_set.h"
#include "axis/database/database/exception.h"
#include "axis/database/database/field.h"
#include <stdio.h>


extern "C" int database_sqlite3_sqlite_callback(void * res_ptr,int ncol, char** reslt,char** cols);


namespace sqlite
{


   database::database()
   {


      m_pstmtSelect = nullptr;
      m_pstmtReplace = nullptr;

      m_bActive = false;
      m_bTransactionActive = false;      // for transaction

      m_strError = "Unknown database m_strError";//S_NO_CONNECTION;
      m_strHost = "localhost";
      m_strPort = "";
      m_strName = "sqlite.m_strName";
      m_strUser = "root";
      m_strPass = "";
      m_psqlite = nullptr;

   }


   database::~database()
   {

      disconnect();

   }


   //::pointer<::database::dataset>database::dataset()
   //{

   //   return __allocate class dataset (this);

   //}

   void * database::get_handle()
   {

      return m_psqlite;

   }


   ::database::enum_connection database::connection_status()
   {

      if (isActive() == false)
      {

         return ::database::e_connection_none;

      }

      return ::database::e_connection_ok;

   }


   void database::set_error_code(int iErrorCode)
   {

      switch (iErrorCode)
      {
         case SQLITE_OK:
            m_strError = "Successful result";
            break;
         case SQLITE_ERROR:
            m_strError = "SQL m_strError or missing database";
            break;
         case SQLITE_INTERNAL:
            m_strError = "An internal logic m_strError in SQLite";
            break;
         case SQLITE_PERM:
            m_strError = "Access permission denied";
            break;
         case SQLITE_ABORT:
            m_strError = "Callback routine requested an abort";
            break;
         case SQLITE_BUSY:
            m_strError = "The database file is locked";
            break;
         case SQLITE_LOCKED:
            m_strError = "A table in the database is locked";
            break;
         case SQLITE_NOMEM:
            m_strError = "A malloc() failed";
            break;
         case SQLITE_READONLY:
            m_strError = "Attempt to write a readonly database";
            break;
         case SQLITE_INTERRUPT:
            m_strError = "Operation terminated by sqlite_interrupt()";
            break;
         case SQLITE_IOERR:
            m_strError = "Some kind of disk I/O m_strError occurred";
            break;
         case SQLITE_CORRUPT:
            m_strError = "The database disk image is malformed";
            break;
         case SQLITE_NOTFOUND:
            m_strError = "(Internal Only) Table or record not found";
            break;
         case SQLITE_FULL:
            m_strError = "Insertion failed because database is full";
            break;
         case SQLITE_CANTOPEN:
            m_strError = "Unable to open the database file";
            break;
         case SQLITE_PROTOCOL:
            m_strError = "database lock protocol m_strError";
            break;
         case SQLITE_EMPTY:
            m_strError = "(Internal Only) database table is is_empty";
            break;
         case SQLITE_SCHEMA:
            m_strError = "The database schema changed";
            break;
         case SQLITE_TOOBIG:
            m_strError = "Too much data for one row of a table";
            break;
         case SQLITE_CONSTRAINT:
            m_strError = "Abort due to contraint violation";
            break;
         case SQLITE_MISMATCH:
            m_strError = "Data type mismatch";
            break;
         default :
            m_strError = "Undefined SQLite m_strError";
      }

      //return ::success;

   }


   bool database::exec(const ::scoped_string & scopedstrQuery)
   {

      char * errmsg = nullptr;

      int iResult = sqlite3_exec((sqlite3 *) get_handle(), scopedstrQuery, nullptr, nullptr, &errmsg);

      set_error_code(iResult);

      if (iResult != SQLITE_OK)
      {


         if (errmsg != nullptr)
//         {
//
//            sqlite3_free(errmsg);
//
//            errmsg = nullptr;
//
//         }
//

            return false;

      }

      return true;

   }


   ::pointer<::database::result_set>database::query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount,
                                                            ::collection::count iColumnCount)
   {

      if (::is_null(m_psqlite))
      {

         informationf("sqlite::database::_sqlite_query_result: No database Connection");

         m_strLastError = "No database Connection";

         m_iLastError = -1;

         return nullptr;

      }

      m_strLastError.empty();

      ::pointer<::database::result_set>presultset = __allocate ::database::result_set();

      char * errmsg = nullptr;

      m_iLastError = sqlite3_exec((sqlite3 *) get_handle(), scopedstrQuery, &database_sqlite3_sqlite_callback, presultset.m_p, &errmsg);

      set_error_code(m_iLastError);

      if (errmsg != nullptr)
      {

         m_strLastError = errmsg;

         sqlite3_free(errmsg);

         errmsg = nullptr;

      }

      if (m_iLastError == SQLITE_OK)
      {

         return presultset;

      } else
      {

         informationf("sqlite::database::_sqlite_query_result: Error %s", m_strLastError.c_str());

         return nullptr;

      }

   }


   ::pointer<::database::result_set>database::query(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount, ::collection::count iColumnCount)
   {

      return query_result(scopedstrQuery, iRowCount, iColumnCount);

   }


   bool database::isActive()
   {

      return m_psqlite != nullptr;

   }


   string database::get_error_message()
   {

      return m_strError;

   }


   void database::init()
   {

      //return ::success;

   }


   ::pointer<class payload_array> database::query_row(const ::scoped_string & scopedstr)
   {

      return ::database::database_impl::query_row(scopedstr);

   }


   ::payload database::query_item(const ::scoped_string & scopedstr)
   {

      return ::database::database_impl::query_item(scopedstr);

   }


   ::pointer<payload_array>database::query_items(const ::scoped_string & scopedstr)
   {

      return ::database::database_impl::query_items(scopedstr);

   }

   void database::connect(
      const ::scoped_string & scopedstrName,
      const ::scoped_string & scopedstrHost,
      const ::scoped_string & scopedstrPort,
      const ::scoped_string & scopedstrUser,
      const ::scoped_string & scopedstrPass,
      const ::scoped_string & scopedstrSckt,
      unsigned long long uConnectionFlags)
   {

      m_strHost = scopedstrHost;
      m_strPort = scopedstrPort;
      m_strName = scopedstrName;
      m_strUser = scopedstrUser;
      m_strPass = scopedstrPass;
      m_strSckt = scopedstrSckt;
      m_uConnectionFlags = uConnectionFlags;

      //auto estatus = 
      
      _connect();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   pointer< pointer_array < payload_array > > database::query_rows(const ::scoped_string & scopedstr)
   {

      return ::database::database_impl::query_rows(scopedstr);

   }


   bool database::memory_query_item(get_memory getmemory, const ::scoped_string & scopedstr)
   {

      return false;

   }


   void database::reset()
   {

   }


   ::collection::count database::get_affected_rows_count()
   {

      return -1;

   }


   bool database::in_transaction()
   {

      return false;

   }


   void database::_connect()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      disconnect();

      if (sqlite3_open(m_strName, (sqlite3 * *) & m_psqlite) == SQLITE_OK)
      {
         //cout << "Connected!\n";
         char * err = nullptr;

         int iResult = sqlite3_exec((sqlite3 *) get_handle(), "PRAGMA empty_result_callbacks=ON", nullptr, nullptr,
                                    &err);

         set_error_code(iResult);

         if (iResult != SQLITE_OK)
         {
            information() << "Error: " <<  err;
            throw ::database::exception(get_error_message());
         }
//         if (setErr(sqlite3_exec((sqlite3 *)get_handle(), "PRAGMA cache_size=-20000", nullptr, nullptr, &err)) != SQLITE_OK)
//         {
//            informationf("Error: %s", err);
//            const ::scoped_string & scopedstrErrorMessage = get_error_message();
//            if(scopedstrErrorMessage != nullptr)
//            {
//
//               information(scopedstrErrorMessage);
//            }
//            //throw ::exception(::database::exception(get_error_message()));
//         }
////         if (setErr(sqlite3_exec((sqlite3 *)get_handle(), "PRAGMA synchronous=OFF", nullptr, nullptr, &err)) != SQLITE_OK)
////         {
////            fprintf(stderr, "Error: %s", err);
////            throw ::exception(::database::exception(get_error_message()));
////         }
         //if (setErr(sqlite3_exec((sqlite3 *)get_handle(), "PRAGMA temp_store=MEMORY", nullptr, nullptr, &err)) != SQLITE_OK)
         //{
         //   informationf("Error: %s", err);
         //   //throw ::exception(::database::exception(get_error_message()));
         //}

         m_bActive = true;

         return;

      }

      throw ::exception(error_failed);

   }


   void database::disconnect()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pstmtSelect != nullptr)
      {

         sqlite3_finalize(m_pstmtSelect);

         m_pstmtSelect = nullptr;

      }

      if (m_pstmtReplace != nullptr)
      {

         sqlite3_finalize(m_pstmtReplace);

         m_pstmtReplace = nullptr;

      }

      if (m_psqlite != nullptr)
      {

         sqlite3_close((sqlite3 *) m_psqlite);

         m_psqlite = nullptr;

      }

      if (!isActive())
      {

         return;

      }

      m_bActive = false;

   }


   void database::create()
   {

      return _connect();

   }

   string database::add_error_message(const ::scoped_string & scopedstr)
   {

      m_strError += scopedstr;

      return m_strError;

   }


   void database::drop()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      disconnect();

      if (isActive())
      {

         throw ::exception(error_failed);

      }

      try
      {

         file()->erase(m_strName);

      }
      catch (...)
      {

         throw ::exception(error_failed);

      }

      //return ::success;

   }


   //long database::nextid(const ::string & sname)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   if(!isActive())
   //   {

   //      return DB_UNEXPECTED_RESULT;

   //   }

   //   int atom;

   //   database::result_set res;

   //   char sqlcmd[512];

   //   sprintf(sqlcmd,"select nextid from %s where seq_name = '%s'",sequence_table.c_str(), sname);

   //   if ((last_err = sqlite3_exec((sqlite3 *) get_handle(),sqlcmd,&axis_sqlite_callback,&res,nullptr) != SQLITE_OK))
   //   {

   //      return DB_UNEXPECTED_RESULT;

   //   }

   //   if (res.m_records.get_size() == 0)
   //   {

   //      atom = 1;

   //      sprintf(sqlcmd,"insert into %s (nextid,seq_name) values (%d,'%s')",sequence_table.c_str(),atom,sname);

   //      if((last_err = sqlite3_exec((sqlite3 *)m_psqlite,sqlcmd,nullptr,nullptr,nullptr)) != SQLITE_OK)
   //      {

   //         return DB_UNEXPECTED_RESULT;

   //      }

   //      return atom;
   //   }
   //   else
   //   {

   //      atom = res.m_records[0][0].as_int() + 1;

   //      sprintf(sqlcmd,"update %s dataset nextid=%d where seq_name = '%s'",sequence_table.c_str(),atom,sname);

   //      if ((last_err = sqlite3_exec((sqlite3 *) m_psqlite,sqlcmd,nullptr,nullptr,nullptr)) != SQLITE_OK) return DB_UNEXPECTED_RESULT;

   //      return atom;

   //   }

   //   return DB_UNEXPECTED_RESULT;

   //}




   void database::start_transaction()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (isActive())
      {
         sqlite3_exec((sqlite3 *) m_psqlite, "begin", nullptr, nullptr, nullptr);
         m_bTransactionActive = true;
      }

   }

   void database::commit_transaction()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (isActive())
      {
         sqlite3_exec((sqlite3 *) m_psqlite, "commit", nullptr, nullptr, nullptr);
         m_bTransactionActive = false;
      }

   }

   void database::rollback_transaction()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (isActive())
      {
         sqlite3_exec((sqlite3 *) m_psqlite, "rollback", nullptr, nullptr, nullptr);
         m_bTransactionActive = false;
      }

   }

   string database::escape(const ::scoped_string & scopedstr)
   {
      
      string str(scopedstr);
      
      str.replace_with("\'\'", "\'");

      str.replace_with("\"\"", "\"");

      return str;

   }


   //void database::create_long_set(const ::scoped_string & scopedstrTable)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   try
   //   {

   //      dataset dataset(this);

   //      _synchronous_lock synchronouslock(this->synchronization());

   //      dataset.query("select * from sqlite_master where type like 'table' and name like '" + strTable + "'");

   //      if (dataset.num_rows() == 0)
   //      {

   //         dataset.exec("create table '" + strTable + "' (id text primary key, value integer)");
   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //}


   //void database::create_string_set(const ::scoped_string & scopedstrTable)
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   try
   //   {

   //      dataset dataset(this);

   //      _synchronous_lock synchronouslock(this->synchronization());

   //      dataset.query("select * from sqlite_master where type like 'table' and name like '" + strTable + "'");

   //      if(dataset.num_rows() == 0)
   //      {

   //         dataset.exec("create table '" + strTable + "' (id text primary key, value text)");

   //      }

   //   }
   //   catch(...)
   //   {

   //   }

   //}

   //string database::error1(const ::scoped_string & scopedstrPrefix)
   //{

   //   return "";

   //}


   void database::trace_error1(const ::scoped_string & scopedstrPrefix)
   {


   }


   string database::query_error(const ::scoped_string & scopedstrPrefix)
   {

      return "";

   }


   void database::set_id_blob(const ::scoped_string & scopedstrKey, ::block block)
   {

      try
      {

         base64 base64;

         string strBase64(base64.encode(block));

         ::property_set set;

         string strSql;

         string str;

         _synchronous_lock slDatabase(synchronization());

         {

            if (m_pstmtReplace == nullptr)
            {

               int iResult = sqlite3_prepare_v2(
                  (sqlite3 *) get_handle(),
                  "REPLACE INTO blobtable (id, value) values (:id, :value);",
                  -1,
                  &m_pstmtReplace, nullptr);

               string strError = sqlite3_errmsg((sqlite3 *) get_handle());

               set_error_code(iResult);

               if (iResult != SQLITE_OK)
               {

                  m_pstmtReplace = nullptr;

                  throw ::exception(error_failed);

               }

               m_iReplaceId = sqlite3_bind_parameter_index(m_pstmtReplace, ":id");

               m_iReplaceValue = sqlite3_bind_parameter_index(m_pstmtReplace, ":value");

            }
            else
            {

               sqlite3_reset(m_pstmtReplace);

            }

            character_count iLength = scopedstrKey.length();

            int res = sqlite3_bind_text(m_pstmtReplace, m_iReplaceId, scopedstrKey, (int) iLength,
                                        SQLITE_TRANSIENT);

            if (res != SQLITE_OK)
            {

               informationf("failure to bind text");

               throw ::exception(error_failed);

            }

            res = sqlite3_bind_blob(m_pstmtReplace, m_iReplaceValue, block.data(), (int) block.size(), SQLITE_TRANSIENT);

            if (res != SQLITE_OK)
            {

               informationf("failure to bind blob");

               throw ::exception(error_failed);

            }

            res = sqlite3_step(m_pstmtReplace);

         }

      }
      catch (...)
      {

         throw ::exception(error_failed);

      }

      //return ::success;

   }


   bool database::get_id_blob(const ::scoped_string & scopedstrKey, get_memory getmemory)
   {
      
      if (m_pstmtSelect == nullptr)
      {

         int iResult = sqlite3_prepare_v2(
            (sqlite3 *) get_handle(),
            "select `value` FROM `blobtable` WHERE `id` = :id;",
            -1,
            &m_pstmtSelect, nullptr);

         string strError = sqlite3_errmsg((sqlite3 *) get_handle());

         set_error_code(iResult);

         if (iResult != SQLITE_OK)
         {

            m_pstmtSelect = nullptr;

            throw ::exception(error_failed);

         }

         m_iSelectId = sqlite3_bind_parameter_index(m_pstmtSelect, ":id");

      }
      else
      {

         try
         {

            sqlite3_reset(m_pstmtSelect);

         }
         catch (...)
         {

            m_pstmtSelect = nullptr;

            throw ::exception(error_failed);

         }

      }

      int iLength = (int) scopedstrKey.length();

      int res = sqlite3_bind_text(m_pstmtSelect, m_iSelectId, scopedstrKey, (int) iLength, SQLITE_TRANSIENT);

      if (res != SQLITE_OK)
      {

         throw ::exception(error_failed);

      }

      res = sqlite3_step(m_pstmtSelect);

      if (res != SQLITE_ROW)
      {

         //string strSql = "select `value` FROM stringtable WHERE `id` = '" + escape(strKey) + "'";

         //::payload payload = query_item(strSql);

         //if (!(bool)payload)
         //{

         //   return false;

         //}

         //return payload.get_string();

         //throw ::exception(error_failed);

         return false;

      }

      const_char_pointer psz = (const_char_pointer )sqlite3_column_blob(m_pstmtSelect, 0);

      character_count iLen = sqlite3_column_bytes(m_pstmtSelect, 0);

      if (!getmemory.get(scopedstrKey, iLen))
      {

         throw ::exception(error_failed);

      }

      //return success;

      return true;

   }


} // namespace sqlite



extern "C"
int database_sqlite3_sqlite_callback(void * res_ptr,int ncol, char** reslt,char** cols)
{

   database::result_set * presultset = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);

   auto & pfielda = presultset->m_pfielda;

   auto & prowa = presultset->m_prowa;

   presultset->__defer_construct_new(pfielda);

   presultset->__defer_construct_new(prowa);

   if (pfielda->is_empty())
   {

      pfielda->set_size(ncol);

      for (::collection::index i = 0; i < ncol; i++)
      {

         presultset->__defer_construct_new(pfielda->element_at(i));

         pfielda->element_at(i)->m_strName = cols[i];

//         if(cols[i + ncol] != nullptr)
//         {
//            string str(cols[i + ncol]);
//            str.make_lower();
//            if(str == "integer")
//            {
//               r->m_record_header[i].type = database::DataTypeLong;
//            }
//            else if(str == "string")
//            {
//               r->m_record_header[i].type = database::DataTypeString;
//            }
//            else if(str == "numeric")
//            {
//               r->m_record_header[i].type = database::DataTypeDouble;
//            }
//         }
      }

   }

   if (reslt != nullptr)
   {

      ::collection::index iCurrentLine = prowa->get_size();

      ::collection::count iMaxRow = presultset->m_iMaxRowCount;

      if (iMaxRow > 0 && iCurrentLine >= iMaxRow)
      {

         int iAbort = 1;

         return iAbort;

      }

      auto prow = __allocate ::database::row();

      ::payload payload;

      ::collection::count iMaxColumn = minimum_non_negative((::collection::count) ncol, presultset->m_iMaxColumnCount);

      for (int i = 0; i < iMaxColumn; i++)
      {

         if (reslt[i] == nullptr)
         {

            payload.set_type(::e_type_null);

         }
         else
         {

            payload = reslt[i];

         }

         prow->set_at_grow(i, payload);

      }

      prowa->set_at_grow(iCurrentLine, prow);

      int iAbort = iMaxRow > 0 && prowa->get_size() >= iMaxRow;

      return iAbort;

   }

   return 0;

}



