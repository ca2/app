#include "framework.h"
//#ifndef _UWP
//#include <mysql/mysql.h>


//namespace mysql
//{
//
//
//   dataset::dataset(database * pdatabase, MYSQL_RES * pres) :
//      ::object(pdatabase),
//      ::database::dataset(pdatabase)
//   {
//
////      m_pdatabase->m_resultptra.add(this);
//      m_pres = pres;
//
//   }
//
//
//   dataset::~dataset()
//   {
//
//      free_result();
//
//   }
//
//
//   bool dataset::free_result()
//   {
//
//      try
//      {
//         if(m_pres != nullptr)
//         {
//            mysql_free_result((MYSQL_RES *) m_pres);
//         }
//      }
//      catch(...)
//      {
//
//      }
//
//      try
//      {
//
//      }
//      catch(...)
//      {
//      }
//
//      return true;
//
//   }
//
//
//   MYSQL_ROW dataset::fetch_row()
//   {
//
//      MYSQL_ROW row;
//
//      if(m_pres == nullptr)
//         return nullptr;
//
//      row = mysql_fetch_row((MYSQL_RES *) m_pres);
//
//      if(mysql_errno ((MYSQL *)(dynamic_cast < ::mysql::database * > ( m_pdatabase))->m_pmysql) != 0)
//      {
//
//         m_pdatabase->trace_error1( "mysql_fetch_row() failed");
//
//      }
//
//      return row;
//
//   }
//
//
//   unsigned long * dataset::fetch_lengths()
//   {
//      unsigned long * lengths;
//      if(m_pres == nullptr)
//         return nullptr;
//      lengths = mysql_fetch_lengths((MYSQL_RES *) m_pres);
//      if(mysql_errno((MYSQL *)(dynamic_cast < ::mysql::database * > (m_pdatabase))->m_pmysql) != 0)
//         m_pdatabase->trace_error1( "mysql_fetch_row() failed");
//      return lengths;
//   }
//
//   i32 dataset::num_fields()
//   {
//      return mysql_num_fields((MYSQL_RES *) m_pres);
//   }
//
//   i64 dataset::num_rows()
//   {
//      return mysql_num_rows ((MYSQL_RES *) m_pres);
//   }
//
//
//   /* process rows and then free the dataset set */
//   //process_result_set (conn, res_set);
//
//
//
//
//} // namespace mysql
//
//
//#endif