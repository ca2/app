#include "framework.h"
#include <stdio.h>
#include "sqlite3.h"


//extern "C" i32 axis_sqlite_callback(void * res_ptr,i32 ncol, char** reslt,char** cols);
//
//
//namespace sqlite
//{
//
//
//   dataset::dataset(database * pdatabase) :
//      ::object(pdatabase),
//      ::database::dataset(pdatabase)
//   {
//
//      m_bError   = false;
//
//   }
//
//
//   //dataset::dataset(database * newDb) :
//   //   object(newDb->get_context_application()),
//   //   ::database::dataset(newDb)
//   //{
//
//   //   m_bError = false;
//   //   m_pdatabase = newDb;
//
//   //}
//
//
//   dataset::~dataset()
//   {
//
//
//   }
//
//
//   void dataset::make_query(string_array &_sql)
//   {
//
//      string strQuery;
//
//      try
//      {
//
//         __pointer(::database::transaction) ptransaction;
//
//         if (m_bAutoCommit)
//         {
//
//            ptransaction = m_pdatabase->transaction();
//
//         }
//
//         if (m_pdatabase == nullptr)
//         {
//
//            __throw(::database::exception("No database Connection"));
//
//         }
//
//         for (i32 i = 0; i <_sql.get_size(); i++)
//         {
//
//            strQuery = _sql.element_at(i);
//
//            char * err=nullptr;
//
//            dataset::parse_sql(strQuery);
//
//            i32 iResult = sqlite3_exec((sqlite3 *)get_handle(), strQuery, nullptr, nullptr, &err);
//
//            m_pdatabase->set_error_code(iResult);
//
//            if(iResult != SQLITE_OK)
//            {
//
//               fprintf(stderr,"Error: %s",err);
//
//               sqlite3_free(err);
//
//               __throw(::database::exception(m_pdatabase->get_error_message()));
//
//            }
//
//         } // end of for
//
//
//         if (ptransaction.is_set())
//         {
//
//            ptransaction->commit();
//
//         }
//
//         m_bActive = true;
//         m_edataset = ::database::dataset_select;
//         //refresh();
//
//      } // end of try
//      catch(...)
//      {
//      }
//   }
//
//
//   void dataset::make_insert()
//   {
//      make_query(m_strSqlInsert);
//      //last();
//   }
//
//
//   void dataset::make_edit()
//   {
//      make_query(m_strSqlUpdate);
//   }
//
//
//   void dataset::make_deletion()
//   {
//      make_query(m_strSqlDelete);
//   }
//
//
//   void dataset::fill_fields()
//   {
//      ////cout <<"rr "<<m_result.m_records.size()<<"|" << frecno <<"\n";
//      //if ((m_pdatabase == nullptr)
//      //      || (m_result.m_record_header.get_size() == 0)
//      //      || (m_result.m_records.get_size() < frecno))
//      //   return;
//
//      //if (fields_object.get_size() == 0) // Filling columns name
//      //{
//      //   fields_object.set_size(m_result.m_record_header.get_size());
//      //   edit_object.set_size(m_result.m_record_header.get_size());
//      //   for (i32 i = 0; i < m_result.m_record_header.get_size(); i++)
//      //   {
//      //      fields_object[i].m_properties    = m_result.m_record_header[i];
//      //      edit_object[i].m_properties      = m_result.m_record_header[i];
//      //   }
//      //}
//
//      ////Filling m_result
//      //if (m_result.m_records.get_size() != 0)
//      //{
//      //   for (i32 i = 0; i < m_result.m_records[frecno].get_size(); i++)
//      //   {
//      //      fields_object[i].m_value   = m_result.m_records[frecno][i];
//      //      edit_object[i].m_value     = m_result.m_records[frecno][i];
//      //   }
//      //}
//      //else
//      //   for (i32 i = 0; i < m_result.m_record_header.get_size(); i++)
//      //   {
//      //      fields_object[i].m_value = "";
//      //      edit_object[i].m_value = "";
//      //   }
//
//   }
//
//   bool dataset::exec(const char * sql)
//   {
//
//      if (!get_handle())
//      {
//
//         TRACE("sqlite::dataset::exec: No database Connection");
//         m_strQueryErrorMessage = "No database Connection";
//         m_strDatabaseErrorMessage = "No database Connection";
//
//         return false;
//
//      }
//
//      char * errmsg = nullptr;
//
//      m_resultsetExecute.m_fielda.remove_all();
//
//      m_resultsetExecute.m_rowa.remove_all();
//
//      m_iLastResult = sqlite3_exec((sqlite3 *)get_handle(), sql, &axis_sqlite_callback, &m_resultsetExecute, &errmsg);
//
//      m_pdatabase->set_error_code(m_iLastResult);
//
//      if(m_iLastResult == SQLITE_OK)
//      {
//
//         m_strQueryErrorMessage = "";
//
//         m_strDatabaseErrorMessage = "";
//
//         if (errmsg != nullptr)
//         {
//
//            sqlite3_free(errmsg);
//
//            errmsg = nullptr;
//
//         }
//
//         return true;
//
//      }
//      else
//      {
//
//         m_strQueryErrorMessage = errmsg;
//
//         if (errmsg != nullptr)
//         {
//
//            sqlite3_free(errmsg);
//
//            errmsg = nullptr;
//
//         }
//
//         m_strDatabaseErrorMessage = m_pdatabase->get_error_message();
//
//         TRACE("sqlite::dataset::exec: Error %s, %s", m_strQueryErrorMessage.c_str(), m_strDatabaseErrorMessage.c_str());
//
//         return false;
//
//      }
//
//   }
//
//
//   bool dataset::exec()
//   {
//
//      return exec(m_strSqlExecute);
//
//   }
//
//   //const void * dataset::getExecRes()
//   //{
//   //   return &m_resultsetExecute;
//   //}
//
//
//   bool dataset::query(const char *query)
//   {
//
//      if(m_pdatabase == nullptr)
//      {
//         TRACE("dataset::query: database is not Defined");
//         m_strQueryErrorMessage = "database is not defined";
//         m_strDatabaseErrorMessage = "database is not defined";
//         return false;
//      }
//      if(dynamic_cast<database*>(m_pdatabase) == nullptr)
//      {
//         TRACE("dataset::query: database is not valid");
//         m_strQueryErrorMessage = "database is not valid";
//         m_strDatabaseErrorMessage = "database is not valid";
//         return false;
//      }
//      if(dynamic_cast<database*>(m_pdatabase)->get_handle() == nullptr)
//      {
//         TRACE("dataset::query: No database connection");
//         m_strQueryErrorMessage = "No database Connection";
//         m_strDatabaseErrorMessage = "No database Connection";
//         return false;
//      }
//
//      if(!::str::begins_ci(query, "select"))
//      {
//
//         TRACE("dataset::query: Must be select SQL");
//
//         return false;
//
//      }
//
//      sync_lock sl(m_pdatabase->mutex());
//
//      close();
//
//      char * errmsg = nullptr;
//
//      int iResult = sqlite3_exec((sqlite3 *) get_handle(),query,&axis_sqlite_callback,&m_result,&errmsg);
//
//      m_pdatabase->set_error_code(iResult);
//
//      if(iResult == SQLITE_OK)
//      {
//
//         m_strQueryErrorMessage = "";
//
//         m_strDatabaseErrorMessage = "";
//
//         if (errmsg != nullptr)
//         {
//
//            sqlite3_free(errmsg);
//
//            errmsg = nullptr;
//
//         }
//
//         m_bActive = true;
//
//         m_edataset = ::database::dataset_select;
//
//         return true;
//
//      }
//      else
//      {
//
//         m_strQueryErrorMessage = errmsg;
//
//         if (errmsg != nullptr)
//         {
//
//            sqlite3_free(errmsg);
//
//            errmsg = nullptr;
//
//         }
//
//         m_strDatabaseErrorMessage = m_pdatabase->get_error_message();
//
//         TRACE("dataset::query: Error: %s, %s", m_strQueryErrorMessage.c_str(), m_strDatabaseErrorMessage.c_str());
//
//         return false;
//
//      }
//
//   }
//
//
//   void dataset::open(const char * sql)
//   {
//
//      set_sql(::database::sql_select, sql);
//
//      open();
//
//   }
//
//
//   void dataset::open()
//   {
//
//      if (!m_strSqlSelect.is_empty())
//      {
//
//
//         query(m_strSqlSelect);
//
//      }
//      else
//      {
//
//         m_edataset = ::database::dataset_none;
//
//      }
//
//   }
//
//
//   void dataset::close()
//   {
//
//      ::database::dataset::close();
//
//      m_result.m_rowa.remove_all();
//      m_result.m_fielda.remove_all();
//      m_row.remove_all();
//      m_rowEdit.remove_all();
//      m_edataset = ::database::dataset_none;
//      m_bActive = false;
//
//   }
//
//
//   void dataset::cancel()
//   {
//
//      if ((m_edataset == ::database::dataset_insert) || (m_edataset==::database::dataset_edit))
//      {
//
//         if(m_result.m_rowa.has_elements())
//         {
//
//            m_edataset = ::database::dataset_select;
//
//         }
//         else
//         {
//
//            m_edataset = ::database::dataset_none;
//
//         }
//
//      }
//
//   }
//
//
//   ::count dataset::num_rows()
//   {
//
//      return m_result.m_rowa.get_size();
//
//   }
//
//
//   //bool dataset::eof()
//   //{
//   //   return feof;
//   //}
//
//
//   //bool dataset::bof()
//   //{
//   //   return fbof;
//   //}
//
//
//   //void dataset::first()
//   //{
//   //   ::database::dataset::first();
//   //   this->fill_fields();
//   //   //cout << "In first "<< fields_object.size()<<"\n";
//   //}
//
//   //void dataset::last()
//   //{
//   //   ::database::dataset::last();
//   //   fill_fields();
//   //}
//
//   //void dataset::prev()
//   //{
//   //   ::database::dataset::prev();
//   //   fill_fields();
//   //}
//
//   //void dataset::next()
//   //{
//   //   ::database::dataset::next();
//   //   if (!eof())
//   //      fill_fields();
//   //}
//
//
//   //bool dataset::seek(index pos)
//   //{
//   //   if (m_edataset == ::database::dataset_select)
//   //   {
//   //      dataset::seek(pos);
//   //      fill_fields();
//   //      return true;
//   //   }
//   //   return false;
//   //}
//
//   /*
//
//      long dataset::nextid(const char *seq_name)
//      {
//         if(get_handle())
//            return m_pdatabase->nextid(seq_name);
//         else
//            return DB_UNEXPECTED_RESULT;
//      }
//
//      bool dataset::remove_row()
//      {
//         if(feof || fbof)
//         {
//            return false;
//         }
//
//         m_result.m_records.remove_at(frecno);
//
//         fbof = feof = (num_rows()==0)? true: false;
//
//         return true;
//      }
//   */
//
////   bool dataset::SetFieldValue(const char *f_name, const payload &value)
////   {
////      bool found = false;
////      if(m_edataset == ::database::dataset_select)
////      {
////         for (i32 i=0; i < fields_object.get_size(); i++)
////         {
////            if(m_result.m_record_header[i].name == f_name)
////            {
////               m_result.m_records[frecno][i] = value;
////               found = true;
////            }
////         }
////         if (!found)
////         {
////            __throw(::database::exception(::get_context_application(),"Field not found: %s",f_name));
////         }
////         return true;
////      }
////      else
////      {
////         return dataset::SetFieldValue(f_name, value);
////      }
//////      __throw(::database::exception(::get_context_application(),"Not in Insert or Edit or Select state"));
//////      //  return false;
////   }
////
////   bool dataset::SetFieldValue(index iFieldIndex, const payload &value)
////   {
////      if(m_edataset == ::database::dataset_select)
////      {
////         if(iFieldIndex >= 0 && iFieldIndex < m_result.m_record_header.get_size())
////         {
////            m_result.m_records[frecno][iFieldIndex] = value;
////            return true;
////         }
////         else
////         {
////            __throw(::database::exception(::get_context_application(),"Field not found: %d",iFieldIndex));
////         }
////      }
////      else
////      {
////         ASSERT(FALSE);
////         //      return dataset::SetFieldValue(f_name, value);
////      }
////      __throw(::database::exception(::get_context_application(),"Not in Insert or Edit or Select state"));
////      //  return false;
////   }
////
////   payload dataset::field_value_at(index iFieldIndex)
////   {
////
////      return FieldValueAt(iFieldIndex);
////
////   }
////
////   payload dataset::FieldValueAt(index iFieldIndex)
////   {
////      //if(m_edataset == dataset_select)
////      {
////         if(iFieldIndex >= 0 && iFieldIndex < m_result.m_record_header.get_size())
////         {
////            if(frecno >= 0 && frecno < m_result.m_records.get_size())
////            {
////               if(iFieldIndex >= 0 && iFieldIndex < m_result.m_records[frecno].get_size())
////               {
////                  return m_result.m_records[frecno][iFieldIndex];
////               }
////            }
////            return false;
////         }
////         else
////         {
////            __throw(::database::exception(::get_context_application(),"Field not found: %d",iFieldIndex));
////         }
////      }
////      //   else
////      {
////         ASSERT(FALSE);
////         //return dataset::SetFieldValue(f_name, value);
////
////      }
////      //__throw(::database::exception(::get_context_application(),"Not in Insert or Edit or Select state"));
////      //  return false;
////   }
////
////
////   i32 dataset::GetFieldIndex(const char *f_name)
////   {
////
////      for (i32 i=0; i < fields_object.get_size(); i++)
////      {
////
////         if(m_result.m_record_header[i].name == f_name)
////         {
////
////            return i;
////
////         }
////
////      }
////
////      return -1;
////
////   }
//
//
//   //bool dataset::find_first(const char * fieldname, payload & value)
//   //{
//   //   i32 iFound = -1;
//   //   if(m_edataset == ::database::dataset_select)
//   //   {
//   //      i32 i;
//   //      for(i=0; i < fields_object.get_size(); i++)
//   //         if(m_result.m_record_header[i].name == fieldname)
//   //         {
//   //            iFound = i;
//   //            break;
//   //         }
//   //      if (iFound < 0) __throw(::database::exception(::get_context_application(),"Field not found: %s",fieldname));
//   //      ::count iNumRows = num_rows();
//   //      for(i=0; i < iNumRows; i++)
//   //         if(m_result.m_records[i][iFound] == value)
//   //         {
//   //            seek(i);
//   //            return true;
//   //         }
//
//   //      return false;
//   //   }
//   //   __throw(::database::exception(::get_context_application(),"not in Select state"));
//   //}
//
//   /*void dataset::query_items(string_array & stra, const char * pszSql)
//   {
//      if(query(pszSql))
//      {
//         first();
//         while(!eof())
//         {
//            stra.add(FieldValueAt(0).get_string());
//            next();
//         }
//      }
//   }
//
//   */
//
//
//} // namespace sqlite
//
//
///**********************************************************************
// * Copyright (ca) 2002, Leo Seib, Hannover
// *
// * Project:CSQLiteDataset C++ Dynamic Library
// * Module: CSQLiteDataset class realisation file
// * Author: Leo Seib      E-Mail: lev@almaty.pointstrike.net
// * begin: 5/04/2002
// *
// * Permission is hereby granted, free of charge, to any person obtaining a copy
// * of this software and associated documentation files (the "Software"), to deal
// * in the Software without restriction, including without limitation the rights
// * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// * copies of the Software, and to permit persons to whom the Software is
// * furnished to do so, subject to the following conditions:
// *
// * The above copyright notice and this permission notice shall be included in
// * all copies or substantial portions of the Software.
// *
// * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// * THE SOFTWARE.
// *
// **********************************************************************/
////************* Callback function ***************************
//
//extern "C"
//i32 axis_sqlite_callback(void * res_ptr,i32 ncol, char** reslt,char** cols)
//{
//
//   database::result_set * presultset = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
//
//   database::field_array & fielda = presultset->m_fielda;
//
//   database::row_array & rowa = presultset->m_rowa;
//
//   if (fielda.get_size() <= 0)
//   {
//
//      fielda.set_size(ncol);
//
//      for (index i = 0; i < ncol; i++)
//      {
//
//         fielda[i].defer_alloc(presultset);
//
//         fielda[i]->m_strName = cols[i];
//
////         if(cols[i + ncol] != nullptr)
////         {
////            string str(cols[i + ncol]);
////            str.make_lower();
////            if(str == "integer")
////            {
////               r->m_record_header[i].type = database::DataTypeLong;
////            }
////            else if(str == "string")
////            {
////               r->m_record_header[i].type = database::DataTypeString;
////            }
////            else if(str == "numeric")
////            {
////               r->m_record_header[i].type = database::DataTypeDouble;
////            }
////         }
//      }
//
//   }
//
//   if (reslt != nullptr)
//   {
//
//      index iCurrentLine = rowa.get_size();
//
//      database::row row;
//
//      payload payload;
//
//      for (i32 i = 0; i < ncol; i++)
//      {
//
//         if (reslt[i] == nullptr)
//         {
//
//            payload.set_type(::e_type_null);
//
//         }
//         else
//         {
//
//            payload = reslt[i];
//
//         }
//
//         row.set_at_grow(i, payload);
//      }
//
//      rowa.set_at_grow(iCurrentLine, row);
//
//   }
//
//   return 0;
//
//}
//
