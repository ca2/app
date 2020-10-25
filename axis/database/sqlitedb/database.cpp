#include "framework.h"
#include "_.h"
#include <stdio.h>

#include "sqlite3.h"


extern "C" i32 axis_sqlite_callback(void * res_ptr,i32 ncol, char** reslt,char** cols);


namespace sqlite
{


   database::database()
   {

      defer_create_mutex();

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


   //__pointer(::database::dataset) database::dataset()
   //{

   //   return __new(class dataset(this));

   //}

   void * database::get_handle()
   {

      return m_psqlite;

   }

   ::database::e_connection database::connection_status()
   {

      if (m_bActive == false)
      {

         return ::database::connection_none;

      }

      return ::database::connection_ok;

   }


   ::estatus     database::set_error_code(i32 iErrorCode)
   {

      switch (iErrorCode)
      {
      case SQLITE_OK: m_strError ="Successful result";
         break;
      case SQLITE_ERROR: m_strError = "SQL m_strError or missing database";
         break;
      case SQLITE_INTERNAL: m_strError = "An internal logic m_strError in SQLite";
         break;
      case SQLITE_PERM: m_strError ="Access permission denied";
         break;
      case SQLITE_ABORT: m_strError = "Callback routine requested an abort";
         break;
      case SQLITE_BUSY: m_strError = "The database file is locked";
         break;
      case SQLITE_LOCKED: m_strError = "A table in the database is locked";
         break;
      case SQLITE_NOMEM: m_strError = "A malloc() failed";
         break;
      case SQLITE_READONLY: m_strError = "Attempt to write a readonly database";
         break;
      case SQLITE_INTERRUPT: m_strError = "Operation terminated by sqlite_interrupt()";
         break;
      case  SQLITE_IOERR: m_strError = "Some kind of disk I/O m_strError occurred";
         break;
      case  SQLITE_CORRUPT: m_strError = "The database disk image is malformed";
         break;
      case SQLITE_NOTFOUND: m_strError = "(Internal Only) Table or record not found";
         break;
      case SQLITE_FULL: m_strError = "Insertion failed because database is full";
         break;
      case SQLITE_CANTOPEN: m_strError = "Unable to open the database file";
         break;
      case SQLITE_PROTOCOL: m_strError = "database lock protocol m_strError";
         break;
      case SQLITE_EMPTY:  m_strError = "(Internal Only) database table is is_empty";
         break;
      case SQLITE_SCHEMA: m_strError = "The database schema changed";
         break;
      case SQLITE_TOOBIG: m_strError = "Too much data for one row of a table";
         break;
      case SQLITE_CONSTRAINT: m_strError = "Abort due to contraint violation";
         break;
      case SQLITE_MISMATCH:  m_strError = "Data type mismatch";
         break;
      default : m_strError = "Undefined SQLite m_strError";
      }

      return ::success;

   }


   bool database::exec(const char * pszQuery)
   {

      char * errmsg = nullptr;

      i32 iResult = sqlite3_exec((sqlite3 *)get_handle(), pszQuery, nullptr, nullptr, &errmsg);

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


   __pointer(::database::result_set) database::query_result(const char * pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      if (is_null(m_psqlite))
      {

         TRACE("sqlite::database::_sqlite_query_result: No database Connection");

         m_strLastError = "No database Connection";

         m_iLastError = -1;

         return nullptr;

      }

      m_strLastError.Empty();

      __pointer(::database::result_set) presultset = __new(::database::result_set());

      char * errmsg = nullptr;

      m_iLastError = sqlite3_exec((sqlite3 *)get_handle(), pszQuery, &axis_sqlite_callback, presultset.m_p, &errmsg);

      set_error_code(m_iLastError);

      if (errmsg != nullptr)
      {

         m_strLastError = errmsg;

         sqlite3_free(errmsg);

         errmsg = nullptr;

      }

      if(m_iLastError == SQLITE_OK)
      {

         return presultset;

      }
      else
      {

         TRACE("sqlite::database::_sqlite_query_result: Error %s", m_strLastError.c_str());

         return nullptr;

      }

   }


   string database::get_error_message()
   {

      return m_strError;

   }


   ::estatus     database::_connect()
   {

      sync_lock sl(mutex());

      disconnect();

      if(sqlite3_open(m_strName, (sqlite3 * *) &m_psqlite) == SQLITE_OK)
      {
         //cout << "Connected!\n";
         char* err = nullptr;

         i32 iResult = sqlite3_exec((sqlite3 *)get_handle(), "PRAGMA empty_result_callbacks=ON", nullptr, nullptr, &err);

         set_error_code(iResult);

         if(iResult != SQLITE_OK)
         {
            TRACE("Error: %s",err);
            __throw(::database::exception(get_error_message()));
         }
//         if (setErr(sqlite3_exec((sqlite3 *)get_handle(), "PRAGMA cache_size=-20000", nullptr, nullptr, &err)) != SQLITE_OK)
//         {
//            TRACE("Error: %s", err);
//            const char * pszErrorMessage = get_error_message();
//            if(pszErrorMessage != nullptr)
//            {
//
//               output_debug_string(pszErrorMessage);
//            }
//            //__throw(::database::exception(get_error_message()));
//         }
////         if (setErr(sqlite3_exec((sqlite3 *)get_handle(), "PRAGMA synchronous=OFF", nullptr, nullptr, &err)) != SQLITE_OK)
////         {
////            fprintf(stderr, "Error: %s", err);
////            __throw(::database::exception(get_error_message()));
////         }
         //if (setErr(sqlite3_exec((sqlite3 *)get_handle(), "PRAGMA temp_store=MEMORY", nullptr, nullptr, &err)) != SQLITE_OK)
         //{
         //   TRACE("Error: %s", err);
         //   //__throw(::database::exception(get_error_message()));
         //}

         m_bActive = true;

         return ::success;

      }

      return error_failed;

   }


   void database::disconnect()
   {

      sync_lock sl(mutex());

      if (m_psqlite != nullptr)
      {

         sqlite3_close((sqlite3 *)m_psqlite);

         m_psqlite = nullptr;

      }

      if (!m_bActive)
      {

         return;

      }

      m_bActive = false;

   }


   ::estatus     database::create()
   {

      return _connect();

   }


   ::estatus      database::drop()
   {

      sync_lock sl(mutex());

      disconnect();

      if (m_bActive)
      {

         return error_failed;

      }

      try
      {

         Context.file().del(m_strName);

      }
      catch(...)
      {

         return error_failed;

      }

      return ::success;

   }


   //long database::nextid(const char* sname)
   //{

   //   sync_lock sl(mutex());

   //   if(!m_bActive)
   //   {

   //      return DB_UNEXPECTED_RESULT;

   //   }

   //   i32 id;

   //   database::result_set res;

   //   char sqlcmd[512];

   //   sprintf(sqlcmd,"select nextid from %s where seq_name = '%s'",sequence_table.c_str(), sname);

   //   if ((last_err = sqlite3_exec((sqlite3 *) get_handle(),sqlcmd,&axis_sqlite_callback,&res,nullptr) != SQLITE_OK))
   //   {

   //      return DB_UNEXPECTED_RESULT;

   //   }

   //   if (res.m_records.get_size() == 0)
   //   {

   //      id = 1;

   //      sprintf(sqlcmd,"insert into %s (nextid,seq_name) values (%d,'%s')",sequence_table.c_str(),id,sname);

   //      if((last_err = sqlite3_exec((sqlite3 *)m_psqlite,sqlcmd,nullptr,nullptr,nullptr)) != SQLITE_OK)
   //      {

   //         return DB_UNEXPECTED_RESULT;

   //      }

   //      return id;
   //   }
   //   else
   //   {

   //      id = res.m_records[0][0].i32() + 1;

   //      sprintf(sqlcmd,"update %s dataset nextid=%d where seq_name = '%s'",sequence_table.c_str(),id,sname);

   //      if ((last_err = sqlite3_exec((sqlite3 *) m_psqlite,sqlcmd,nullptr,nullptr,nullptr)) != SQLITE_OK) return DB_UNEXPECTED_RESULT;

   //      return id;

   //   }

   //   return DB_UNEXPECTED_RESULT;

   //}




   void database::start_transaction()
   {

      sync_lock sl(mutex());

      if (m_bActive)
      {
         sqlite3_exec((sqlite3 *) m_psqlite,"begin",nullptr,nullptr,nullptr);
         m_bTransactionActive = true;
      }

   }

   void database::commit_transaction()
   {

      sync_lock sl(mutex());

      if (m_bActive)
      {
         sqlite3_exec((sqlite3 *) m_psqlite,"commit",nullptr,nullptr,nullptr);
         m_bTransactionActive = false;
      }

   }

   void database::rollback_transaction()
   {

      sync_lock sl(mutex());

      if (m_bActive)
      {
         sqlite3_exec((sqlite3 *) m_psqlite,"rollback",nullptr,nullptr,nullptr);
         m_bTransactionActive = false;
      }

   }

   string database::escape(const char * psz)
   {
      string str(psz);
      str.replace("\'", "\'\'");
      str.replace("\"", "\"\"");
      return str;
   }


   //void database::create_long_set(const string & strTable)
   //{

   //   sync_lock sl(mutex());

   //   try
   //   {

   //      dataset dataset(this);

   //      sync_lock sl(mutex());

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


   //void database::create_string_set(const string & strTable)
   //{

   //   sync_lock sl(mutex());

   //   try
   //   {

   //      dataset dataset(this);

   //      sync_lock sl(mutex());

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


} // namespace sqlite





extern "C"
i32 axis_sqlite_callback(void * res_ptr,i32 ncol, char** reslt,char** cols)
{

   database::result_set * presultset = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);

   auto & pfielda = presultset->m_pfielda;

   auto & prowa = presultset->m_prowa;

   __construct_new(pfielda);

   __construct_new(prowa);

   if (pfielda->isEmpty())
   {

      pfielda->set_size(ncol);

      for (index i = 0; i < ncol; i++)
      {

         pfielda->element_at(i).defer_create_new();

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

      index iCurrentLine = prowa->get_size();

      ::count iMaxRow = presultset->m_iMaxRowCount;

      if (iMaxRow > 0 && iCurrentLine >= iMaxRow)
      {

         int iAbort = 1;

         return iAbort;

      }

      auto prow = __new(::database::row);

      var var;

      ::count iMaxColumn = min_non_neg((::count) ncol, presultset->m_iMaxColumnCount);

      for (i32 i = 0; i < iMaxColumn; i++)
      {

         if (reslt[i] == nullptr)
         {

            var.set_type(::e_type_null);

         }
         else
         {

            var = reslt[i];

         }

         prow->set_at_grow(i, var);

      }

      prowa->set_at_grow(iCurrentLine, prow);

      int iAbort = iMaxRow > 0 && prowa->get_size() >= iMaxRow;

      return iAbort;

   }

   return 0;

}



