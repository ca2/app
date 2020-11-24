#include "framework.h"
#include "acme/platform/profiler.h"
#ifndef _UWP
#include <mysql/mysql.h>


int_bool init_data_library()
{

   if (mysql_server_init(0, NULL, NULL))
   {

      return FALSE;

   }

   return TRUE;

}


namespace mysql
{


   database::database()
   {

      m_uConnectionFlags = 0;

      m_cAffectedRows = -1;
      m_pmysql = nullptr;
#ifdef WINDOWS
      m_protocol = MYSQL_PROTOCOL_MEMORY;
#else
      m_protocol = MYSQL_PROTOCOL_DEFAULT;
#endif

   }


   database::~database()
   {

      close_mysql_database();

   }


   ::estatus database::initialize(::layered * pobjectContext)
   {

      auto estatus = ::database::database::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void database::finalize()
   {

      close_mysql_database();

      ::database::database::finalize();

   }


   void * database::get_handle()
   {

      return m_pmysql;

   }


   bool database::initialize()
   {

      return true;

   }


   ::estatus database::_connect()
   {

      /* initialize connection handler */
      m_pmysql = mysql_init (nullptr);

      if(m_pmysql == nullptr)
      {
         
         trace_error1("mysql_init() failed (probably out of memory)\n");
         
         m_pmysql = nullptr;

         return error_failed;

      }

      mysql_options((MYSQL *)m_pmysql, MYSQL_SET_CHARSET_NAME, "utf8mb4");

#ifdef WINDOWS

      if(ansi_compare_ci(m_strHost, "localhost") == 0)
      {
         
         m_protocol = MYSQL_PROTOCOL_MEMORY;

         mysql_options(m_pmysql, MYSQL_OPT_PROTOCOL,  &m_protocol);

         m_strHost.Empty();

      }

#endif

      if(mysql_real_connect(
            (MYSQL *) m_pmysql,
            m_strHost.is_empty() ? nullptr : m_strHost.c_str(),
            m_strUser,
            m_strPass,
            m_strName,
            atoi(m_strPort),
            m_strSckt,
            (unsigned long) m_uConnectionFlags) == nullptr)
      {

         trace_error1( "mysql_real_connect() failed\n");

         mysql_close((MYSQL *) m_pmysql);

         m_pmysql = nullptr;

         return error_failed;

      }

      mysql_query((MYSQL *)m_pmysql, "SET NAMES 'utf8mb4' COLLATE 'utf8_unicode_ci'");

      mysql_query((MYSQL *)m_pmysql, "SET CHARACTER SET 'utf8mb4'");

      return ::success;

   }


   bool database::close_mysql_database()
   {

      if (m_pmysql == nullptr)
      {

         return false;

      }


//      m_resultptra.remove_all();

      /*

      for(i32 i = 0; i < m_resultptra.get_count(); i++)
      {
         if(m_resultptra(i)->m_bAutoDelete)
         {
            delete m_resultptra[i];
         }
      }

      */

      mysql_close((MYSQL *) m_pmysql);

      m_pmysql = nullptr;

      return true;

   }


   string database::error1(const char * pszPrefix)
   {
      string strPrefix(pszPrefix);
      string strFormat;
      if(m_pmysql == nullptr)
      {
         strFormat = "mysql error => nullptr sql connection pointer";
      }
      else
      {
         strFormat.Format(
         "mysql error => %u (%s): %s\n",
         mysql_errno((MYSQL *) m_pmysql),
         mysql_sqlstate((MYSQL *) m_pmysql),
         mysql_error((MYSQL *) m_pmysql));
      }
      if(strPrefix.has_char())
         return strPrefix + ": " + strFormat;
      else
         return strPrefix + strFormat;
   }


   bool database::exec(const char * pszSql)
   {

      m_strLastError = "";

      m_cAffectedRows = -1;

      m_iLastError = -1;

      MYSQL_RES * pres = nullptr;

      if (m_pmysql == nullptr)
      {

         millis_sleep(2000);

         if (!initialize() || m_pmysql == nullptr)
         {

            trace_error1("Could not execute statement (0)");

            return false;

         }

      }

      try
      {

         if (mysql_query((MYSQL *)m_pmysql, pszSql) != 0) /* the statement failed */
         {

            if (m_pmysql == nullptr || mysql_errno(m_pmysql) == 2006) // MySQL server has gone away
            {

               millis_sleep(2000);

               if (!initialize() || m_pmysql == nullptr)
               {

                  trace_error1("Could not execute statement");

                  return false;

               }

               if (mysql_query((MYSQL *)m_pmysql, pszSql) != 0) /* the statement failed */
               {

                  trace_error1("Could not execute statement");

                  return false;

               }

            }
            else
            {

               trace_error1("Could not execute statement");

               return false;

            }

         }

      }
      catch (...)
      {

         trace_error1("Could not execute statement (2)");

         return false;

      }

      return true;

   }


   MYSQL_RES * database::_mysql_query_result(const char * pszSql)
   {

      if (!exec(pszSql))
      {

         return nullptr;

      }

      /* the statement succeeded; determine whether it returned data */
      MYSQL_RES * pres = mysql_store_result ((MYSQL *) m_pmysql);

      if(pres) /* a result dataset was returned */
      {

         m_iLastUsedTime = ::acme::profiler::micros();

         return pres;

      }

      m_iLastError = mysql_errno((MYSQL *)m_pmysql);

      if (m_iLastError == 0)
      {

         m_iLastUsedTime = ::acme::profiler::micros();

         m_cAffectedRows  = mysql_affected_rows((MYSQL *)m_pmysql);

         TRACE("Number of rows affected: %lu\n", (u32)m_cAffectedRows);

      }

      return nullptr;
      //else /* no result dataset was returned */
      {
         /*
         * does the lack of a result dataset mean that the statement didn't
         * return one, or that it should have but an error occurred?
         */


         //if(m_iLastError == 0)
         //{

         //   /*
         //   * statement generated no result dataset (it was not a SELECT,
         //   * SHOW, DESCRIBE, etc.); just report rows-affected value.
         //   */

         //   m_iLastUsedTime = ::aura::profiler::micros();

         //   auto presult  = __new(result(this, nullptr));

         //   presult->m_uiAffectedRows = mysql_affected_rows((MYSQL *)m_pmysql);

         //   TRACE("Number of rows affected: %lu\n", (u32)presult->m_uiAffectedRows);

         //   return presult;

         //}
         //else /* an error occurred */
         //{
         //   trace_error1 ("Could not retrieve result dataset");
         //   return nullptr;
         //}
      }
   }


   bool database::_mysql_result_free(MYSQL_RES * pres)
   {

      try
      {

         if (::is_set(pres))
         {

            mysql_free_result(pres);

         }

      }
      catch(...)
      {

      }

      return true;

   }


   MYSQL_ROW database::_mysql_fetch_row(MYSQL_RES * pres)
   {

      if (pres == nullptr)
      {

         return nullptr;

      }

      MYSQL_ROW row = mysql_fetch_row((MYSQL_RES *)pres);

      if(mysql_errno (m_pmysql) != 0)
      {

         trace_error1( "mysql_fetch_row() failed");

      }

      return row;

   }


   unsigned long * database::_mysql_fetch_lengths(MYSQL_RES * pres)
   {

      if (::is_null(pres))
      {

         return nullptr;

      }

      unsigned long * lengths = mysql_fetch_lengths((MYSQL_RES *) pres);

      if (lengths == nullptr)
      {

         m_iLastError = mysql_errno(m_pmysql);

         trace_error1("mysql_fetch_lengths() failed");

      }

      return lengths;

   }


   i64 database::_mysql_num_fields(MYSQL_RES * pres)
   {

      if (::is_null(pres))
      {

         return -1;

      }

      return mysql_num_fields((MYSQL_RES *) pres);

   }


   i64 database::_mysql_num_rows(MYSQL_RES * pres)
   {

      if (::is_null(pres))
      {

         return -1;

      }

      return mysql_num_rows(pres);

   }


   __pointer(::database::result_set) database::query_result(const char * pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      MYSQL_RES * pres = _mysql_query_result(pszQuery);

      if (::is_null(pres))
      {

         return nullptr;

      }

      auto pset = __new(::database::result_set());

      MYSQL_ROW row;

      pset->m_prowa = __new(::database::row_array());

      auto & prowa = pset->m_prowa;

      i64 iNumRows = _mysql_num_rows(pres);

      i64 iNumFields = _mysql_num_fields(pres);

      if (iColumnCount > 0)
      {

         iNumFields = min(iColumnCount, iNumFields);

      }

      if (iRowCount > 0)
      {

         iNumRows = min(iRowCount, iNumRows);

      }

      prowa->set_size(iNumRows);

      i64 iRow = 0;

      while ((row = _mysql_fetch_row(pres)) != nullptr)
      {

         if (iRow >= iNumRows)
         {

            if (iRowCount > 0 && iRow >= iRowCount)
            {

               break;

            }

            iNumRows++;

            prowa->set_size(iNumRows);

         }

         auto prow = __new(::database::row);

         prow->set_size(iNumFields);

         for (i64 iField = 0; iField < iNumFields; iField++)
         {

            if (row[iField] == nullptr)
            {

               prow->set_at_grow(iField, ::e_type_null);

            }
            else
            {

               prow->set_at_grow(iField, row[iField]);

            }

         }

         prowa->set_at_grow(iRow, prow);

         iRow++;

         if (iRowCount > 0 && iRow >= iRowCount)
         {

            break;

         }

      }

      return pset;


   }



   payload database::query_item(const char * pszSql, payload varDefault)
   {

      MYSQL_RES * pres = _mysql_query_result(pszSql);

      if (::is_null(pres))
      {

         return varDefault;

      }

      MYSQL_ROW row = (MYSQL_ROW) _mysql_fetch_row(pres);

      if (row == nullptr)
      {

         return varDefault;

      }
      else if (row[0] == nullptr)
      {

         return ::payload(::e_type_null);

      }
      else
      {

         return payload(row[0]);

      }

   }


   bool database::query_blob(memory_base & memory, const char * pszSql)
   {

      MYSQL_RES * pres = _mysql_query_result(pszSql);

      if (::is_null(pres))
      {

         return false;

      }

      MYSQL_ROW row = (MYSQL_ROW)_mysql_fetch_row(pres);

      if (row == nullptr)
      {

         return false;

      }
      else if (row[0] == nullptr)
      {

         return false;

      }
      else
      {

         unsigned long * pul =  _mysql_fetch_lengths(pres);

         if (pul == nullptr)
         {

            return false;

         }

         memory.assign(row[0], pul[0]);

         return true;

      }

   }


   __pointer(var_array) database::query_items(const char * pszSql)
   {

      MYSQL_RES * pres = _mysql_query_result(pszSql);

      if (::is_null(pres))
      {

         return nullptr;

      }

      MYSQL_ROW row;

      i64 iNumRows = _mysql_num_rows(pres);

      auto pvara = __new(var_array);

      pvara->set_size(iNumRows);

      i64 iRow = 0;

      while ((row = _mysql_fetch_row(pres)) != nullptr)
      {

         if (iRow >= iNumRows)
         {

            iNumRows++;

            pvara->set_size(iNumRows);

         }

         if (row[0] == nullptr)
         {

            pvara->set_at_grow(iRow, ::e_type_null);

         }
         else
         {

            pvara->set_at_grow(iRow, row[0]);

         }

         iRow++;

      }

      return pvara;

   }


   __pointer(::database::row) database::query_row(const char * pszSql)
   {

      MYSQL_RES * pres = _mysql_query_result(pszSql);

      if (::is_null(pres))
      {

         return nullptr;

      }

      MYSQL_ROW row = _mysql_fetch_row(pres);

      if (row == nullptr)
      {

         return nullptr;

      }

      auto prow = __new(::database::row);

      i64 iNumFields = _mysql_num_fields(pres);

      prow->set_size(iNumFields);

      for(i64 iField = 0; iField < iNumFields; iField++)
      {

         if (row[iField] == nullptr)
         {

            prow->set_at_grow(iField, ::e_type_null);

         }
         else
         {

            prow->set_at_grow(iField, row[iField]);

         }

      }

      return prow;

   }


   __pointer(::database::row_array) database::query_rows(const char * pszQuery)
   {

      auto pset = query_result(pszQuery);

      if (pset.is_null())
      {

         return nullptr;

      }

      return pset->m_prowa;

   }


   payload database::query_table_item(const char * table, const char * item, const char *where, payload notfound)
   {
      string strSql;
      strSql.Format("SELECT `%s` FROM `%s` WHERE %s", item, table, where);
      return query_item(strSql, notfound);
   }


   payload database::get_agent(const char * pszTable, const char * psz, const char * pszUser)
   {
      string strSql;
      string strAgent(psz);
      string strTable(pszTable);
      strSql = "SELECT id FROM " + strTable + " WHERE value='" + strAgent + "'";
      string strId = query_item(strSql);

      if(strId.is_empty())
      {
         strId = query_item("SELECT max(id) FROM " + strTable + " ORDER BY id");
         if(strId.is_empty())
         {
            strId = string("0000000000000000") + string("0000000000000000") + string("0000000000000000") + string("0000000000000000")
                    + string("0000000000000000") + string("0000000000000000") + string("0000000000000000") + string("0000000000000000")
                    + string("0000000000000000") + string("0000000000000000") + string("0000000000000000") + string("0000000000000000")
                    + string("0000000000000000") + string("0000000000000000") + string("0000000000000000") + string("000000000000000");
         }
         else
         {
            ::str::increment_digit_letter(strId);
         }
         strSql = "INSERT INTO " + strTable + "(`id`, `value`) VALUES('" + strId + "', '" + strAgent + "')";
         if(!query(strSql))
            return false;
      }
      if(pszUser != nullptr)
      {
         if(!query("UPDATE " + strTable + " SET `user` = '" + string(pszUser) + "' WHERE `id` = '" + strId + "'"))
            return false;
      }
      return strId;
   }


   ::count database::get_affected_rows_count()
   {

      return m_cAffectedRows;

   }


   string database::escape(void * p, strsize iLen)
   {

      string str;

      char * psz = str.get_string_buffer(iLen * 2 + 1);

      if (psz == nullptr)
      {

         __throw(memory_exception());

      }

      mysql_real_escape_string((MYSQL *) m_pmysql, psz, (const char *) p, (unsigned long) iLen);

      str.release_string_buffer();

      return str;

   }


   string database::escape(const char * psz)
   {

      return escape((void *) psz, strlen(psz));

   }


   payload database::get_insert_id()
   {
      return (u64) mysql_insert_id((MYSQL *) m_pmysql);
   }

} //   namespace mysql


#endif
