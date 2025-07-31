#include "framework.h"
#include "mysql_database.h"
////#include "acme/exception/exception.h"
#include "acme/platform/profiler.h"
#include "acme/prototype/string/str.h"
#include "axis/database/database/result_set.h"
#include "acme/filesystem/filesystem/file_context.h"


#ifndef UNIVERSAL_WINDOWS


#include "acme/_operating_system.h"
#include <mysql/mysql.h>



int_bool init_data_library()
{

   if (mysql_server_init(0, NULL, NULL))
   {

      return false;

   }

   return true;

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


   void database::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::database::database::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void database::destroy()
   {

      close_mysql_database();

      //auto estatus = 
      
      ::database::database::destroy();

      //return estatus;

   }


   void* database::get_handle()
   {

      return m_pmysql;

   }


   bool database::initialize()
   {

      return true;

   }


   void database::_connect()
   {

      /* initialize connection handler */
      m_pmysql = mysql_init(nullptr);

      if (m_pmysql == nullptr)
      {

         trace_error1("mysql_init() failed (probably out of memory)\n");

         m_pmysql = nullptr;

         throw ::exception(error_failed);

      }

      //mysql_options((MYSQL*)m_pmysql, MYSQL_SET_CHARSET_NAME, "utf8mb4");
      //mysql_options((MYSQL*)m_pmysql, MYSQL_OPT_BIND, "192.168.8.89");

      //m_strSckt = "192.168.0.205";

//#ifdef WINDOWS
//
//      if (case_insensitive_ansi_compare(m_strHost, "localhost") == 0)
//      {
//
//         m_protocol = MYSQL_PROTOCOL_MEMORY;
//
//         mysql_options(m_pmysql, MYSQL_OPT_PROTOCOL, &m_protocol);
//
//         m_strHost.empty();
//
//      }
//
//#endif

      unsigned int uPort = atoi(m_strPort);

      if (mysql_real_connect(
         (MYSQL*)m_pmysql,
         m_strHost.is_empty() ? nullptr : m_strHost.c_str(),
         m_strUser,
         m_strPass,
         m_strName,
         uPort,
         m_strSckt.is_empty() ? nullptr : m_strSckt,
         (unsigned long)m_uConnectionFlags) == nullptr)
      {

         trace_error1("mysql_real_connect() failed\n");

         mysql_close((MYSQL*)m_pmysql);

         m_pmysql = nullptr;

         throw ::exception(error_failed);

      }

      mysql_query((MYSQL*)m_pmysql, "SET NAMES 'utf8' COLLATE 'case_insensitive_utf8_unicode'");

      mysql_query((MYSQL*)m_pmysql, "SET CHARACTER SET 'utf8'");

      //return ::success;

   }


   bool database::close_mysql_database()
   {

      if (m_pmysql == nullptr)
      {

         return false;

      }


      //      m_resultptra.erase_all();

            /*

            for(int i = 0; i < m_resultptra.get_count(); i++)
            {
               if(m_resultptra(i)->m_bAutoDelete)
               {
                  delete m_resultptra[i];
               }
            }

            */

      mysql_close((MYSQL*)m_pmysql);

      m_pmysql = nullptr;

      return true;

   }


   string database::query_error(const ::scoped_string & scopedstrPrefixParam)
   {
      
      string strPrefix(strPrefixParam);

      string strFormat;

      if (m_pmysql == nullptr)
      {

         strFormat = "mysql error => nullptr sql connection pointer";

      }
      else
      {
         strFormat.formatf(
            "mysql error => %u (%s): %s\n",
            mysql_errno((MYSQL*)m_pmysql),
            mysql_sqlstate((MYSQL*)m_pmysql),
            mysql_error((MYSQL*)m_pmysql));
      }
      if (strPrefix.has_character())
         return strPrefix + ": " + strFormat;
      else
         return strPrefix + strFormat;
   }


   bool database::exec(const ::scoped_string & scopedstrSql)
   {

      m_strLastError = "";

      m_cAffectedRows = -1;

      m_iLastError = -1;

      MYSQL_RES* pres = nullptr;

      if (m_pmysql == nullptr)
      {

         sleep(2000_ms);

         if (!initialize() || m_pmysql == nullptr)
         {

            trace_error1("Could not execute statement (0)");

            return false;

         }

      }

      try
      {

         if (mysql_query((MYSQL*)m_pmysql, pszSql) != 0) /* the statement failed */
         {

            if (m_pmysql == nullptr || mysql_errno(m_pmysql) == 2006) // MySQL server has gone away
            {

               sleep(2000_ms);

               if (!initialize() || m_pmysql == nullptr)
               {

                  trace_error1("Could not execute statement");

                  return false;

               }

               if (mysql_query((MYSQL*)m_pmysql, pszSql) != 0) /* the statement failed */
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


   MYSQL_RES* database::_mysql_query_result(const ::scoped_string & scopedstrSql)
   {

      if (!exec(scopedstrSql))
      {

         return nullptr;

      }

      /* the statement succeeded; determine whether it returned data */
      MYSQL_RES* pres = mysql_store_result((MYSQL*)m_pmysql);

      if (pres) /* a result dataset was returned */
      {

         m_timeLastUse.Now();

         return pres;

      }

      m_iLastError = mysql_errno((MYSQL*)m_pmysql);

      if (m_iLastError == 0)
      {

         m_timeLastUse.Now();

         m_cAffectedRows = mysql_affected_rows((MYSQL*)m_pmysql);

         informationf("Number of rows affected: %lu\n", (unsigned int)m_cAffectedRows);

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

         //   m_iLastUsedTime = ::aura::profiler::microsecond();

         //   auto presult  = __allocate result(this, nullptr);

         //   presult->m_uiAffectedRows = mysql_affected_rows((MYSQL *)m_pmysql);

         //   informationf("Number of rows affected: %lu\n", (unsigned int)presult->m_uiAffectedRows);

         //   return presult;

         //}
         //else /* an error occurred */
         //{
         //   trace_error1 ("Could not retrieve result dataset");
         //   return nullptr;
         //}
      }
   }


   bool database::_mysql_result_free(MYSQL_RES* pres)
   {

      try
      {

         if (::is_set(pres))
         {

            mysql_free_result(pres);

         }

      }
      catch (...)
      {

      }

      return true;

   }


   MYSQL_ROW database::_mysql_fetch_row(MYSQL_RES* pres)
   {

      if (pres == nullptr)
      {

         return nullptr;

      }

      MYSQL_ROW row = mysql_fetch_row((MYSQL_RES*)pres);

      if (mysql_errno(m_pmysql) != 0)
      {

         trace_error1("mysql_fetch_row() failed");

      }

      return row;

   }


   unsigned long* database::_mysql_fetch_lengths(MYSQL_RES* pres)
   {

      if (::is_null(pres))
      {

         return nullptr;

      }

      unsigned long* lengths = mysql_fetch_lengths((MYSQL_RES*)pres);

      if (lengths == nullptr)
      {

         m_iLastError = mysql_errno(m_pmysql);

         trace_error1("mysql_fetch_lengths() failed");

      }

      return lengths;

   }


   long long database::_mysql_num_fields(MYSQL_RES* pres)
   {

      if (::is_null(pres))
      {

         return -1;

      }

      return mysql_num_fields((MYSQL_RES*)pres);

   }


   long long database::_mysql_num_rows(MYSQL_RES* pres)
   {

      if (::is_null(pres))
      {

         return -1;

      }

      return mysql_num_rows(pres);

   }


   ::pointer<::database::result_set>database::query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount, ::collection::count iColumnCount)
   {

      MYSQL_RES* pres = _mysql_query_result(scopedstrQuery);

      if (::is_null(pres))
      {

         return nullptr;

      }

      auto pset = __allocate ::database::result_set();

      MYSQL_ROW row;

      pset->m_prowa = __allocate ::database::row_array();

      auto& prowa = pset->m_prowa;

      long long iNumRows = _mysql_num_rows(pres);

      long long iNumFields = _mysql_num_fields(pres);

      if (iColumnCount > 0)
      {

         iNumFields = minimum(iColumnCount, iNumFields);

      }

      if (iRowCount > 0)
      {

         iNumRows = minimum(iRowCount, iNumRows);

      }

      prowa->set_size(iNumRows);

      long long iRow = 0;

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

         auto prow = __allocate ::database::row();

         prow->set_size(iNumFields);

         for (long long iField = 0; iField < iNumFields; iField++)
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


   

   bool database::query_item(::payload & payload, const ::scoped_string & scopedstrSql)
   {

      MYSQL_RES* pres = _mysql_query_result(scopedstrSql);

      if (::is_null(pres))
      {

         return false;

      }

      MYSQL_ROW row = (MYSQL_ROW)_mysql_fetch_row(pres);

      if (row == nullptr)
      {

         return false;

      }

      if (row[0] == nullptr)
      {

         payload = ::e_type_null;

      }
      else
      {

         payload = row[0];

      }

      return true;

   }


   bool database::query_blob(memory_base& memory, const ::scoped_string & scopedstrSql)
   {

      MYSQL_RES* pres = _mysql_query_result(scopedstrSql);

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

         unsigned long* pul = _mysql_fetch_lengths(pres);

         if (pul == nullptr)
         {

            return false;

         }

         memory.assign(row[0], pul[0]);

         return true;

      }

   }


   bool database::query_items(::pointer<payload_array>& pvara, const ::scoped_string & scopedstrSql)
   {

      MYSQL_RES* pres = _mysql_query_result(scopedstrSql);

      if (::is_null(pres))
      {

         return false;

      }

      MYSQL_ROW row;

      long long iNumRows = _mysql_num_rows(pres);

      __defer_construct_new(pvara);

      pvara->set_size(iNumRows);

      long long iRow = 0;

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


   bool database::query_row(::pointer<::database::row>& prow, const ::scoped_string & scopedstrSql)
   {

      MYSQL_RES* pres = _mysql_query_result(scopedstrSql);

      if (::is_null(pres))
      {

         return false;

      }

      MYSQL_ROW row = _mysql_fetch_row(pres);

      if (row == nullptr)
      {

         return false;

      }

      long long iNumFields = _mysql_num_fields(pres);

      __defer_construct_new(prow);

      prow->set_size(iNumFields);

      for (long long iField = 0; iField < iNumFields; iField++)
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


   bool database::query_rows(::pointer<::database::row_array>& prowarray, const ::scoped_string & scopedstrQuery)
   {

      auto pset = query_result(scopedstrQuery);

      if (pset.is_null())
      {

         return false;

      }

      prowarray = pset->m_prowa;

      return prowarray;

   }


   //::payload database::query_table_item(const ::string & table, const ::string & item, const ::string & where, ::payload notfound)
   //{
   //   string strSql;
   //   strSql.Format("SELECT `%s` FROM `%s` WHERE %s", item, table, where);
   //   return database_impl::query_item(strSql, notfound);
   //}


   ::payload database::get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrUser)
   {
      string strSql;
      string strAgent(scopedstr);
      string strTable(scopedstrTable);
      strSql = "SELECT atom FROM " + strTable + " WHERE value='" + strAgent + "'";
      string strId = query_item(strSql);

      if (strId.is_empty())
      {
         strId = query_item("SELECT maximum(atom) FROM " + strTable + " ORDER BY atom");
         if (strId.is_empty())
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
         strSql = "INSERT INTO " + strTable + "(`atom`, `value`) VALUES('" + strId + "', '" + strAgent + "')";
         if (!query(strSql))
            return false;
      }
      if (!pszUser)
      {
         if (!query("UPDATE " + strTable + " SET `user` = '" +::string(scopedstrUser) + "' WHERE `atom` = '" + strId + "'"))
            return false;
      }
      return strId;
   }


   ::collection::count database::get_affected_rows_count()
   {

      return m_cAffectedRows;

   }


   string database::escape(const char * psz, character_count iLen)
   {

      string strEscaped;

      char* pszEscaped = strEscaped.get_buffer(iLen * 2 + 1);

      if (scopedstr == nullptr)
      {

         throw ::exception(error_no_memory);

      }

      mysql_real_escape_string((MYSQL*)m_pmysql, pszEscaped, psz, (unsigned long)iLen);

      strEscaped.release_buffer();

      return strEscaped;

   }


   string database::escape(const ::scoped_string & scopedstr)
   {

      return escape(str.c_str(), str.length());

   }


   ::payload database::get_insert_id()
   {
      return (unsigned long long)mysql_insert_id((MYSQL*)m_pmysql);
   }

} //   namespace mysql


#endif
