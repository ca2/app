#include "framework.h"


namespace simpledb
{

   i32 callback(void * res_ptr,i32 ncol, char** reslt,char** cols);

   dataset::dataset() :
      ::database::dataset()
   {

      //errmsg      = nullptr;
      haveError   = false;
      db          = nullptr;

   }


   dataset::dataset(database *newDb) :
      ::database::dataset(newDb)
   {

      //errmsg      = nullptr;
      haveError = false;
      db = newDb;

   }


   dataset::~dataset()
   {

      //  if(errmsg != nullptr)
      //  {
      //      sqlite_free_table(&errmsg);
      // }

   }


   bool dataset::exec(const ::string & pszSql)
   {

      ::database::result_set * r = (::database::result_set *) &m_resultset;

      r->m_record_header.erase_all();

      r->m_records.erase_all();

      string strInstruction = sql_consume_keyword(pszSql);

      if(strInstruction == "select")
      {

         return sql_do_select(pszSql);

      }
      else if(strInstruction == "insert")
      {

         return sql_do_insert(pszSql);

      }

      return false;

   }

   /*if (!handle())
   {
      TRACE("sqlite::dataset::exec: No Database Connection");
      m_strQueryErrorMessage = "No Database Connection";
      m_strDatabaseErrorMessage = "No Database Connection";
      return false;
   }*/
   /*      m_resultsetExec.m_record_header.erase_all();
         m_resultsetExec.m_records.erase_all();
      database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
      i32 sz = r->m_records.get_size();

      //if (reslt == nullptr ) cout << "EMPTY!!!\n";
      if (r->m_record_header.get_size() <= 0)
      {
         r->m_record_header.set_size(ncol, 32);
         for (i32 i=0; i < ncol; i++)
         {
            r->m_record_header[i].name = cols[i];
            if(cols[i + ncol] != nullptr)
            {
               string str(cols[i + ncol]);
               str.make_lower();
               if(str == "integer")
               {
                  r->m_record_header[i].type = database::DataTypeLong;
               }
               else if(str == "string")
               {
                  r->m_record_header[i].type = database::DataTypeString;
               }
               else if(str == "numeric")
               {
                  r->m_record_header[i].type = database::DataTypeDouble;
               }
            }
         }
      }


      database::SqlRecord rec;
      ::payload v;

      if (reslt != nullptr)
      {
         for (i32 i=0; i<ncol; i++)
         {
            if (reslt[i] == nullptr)
            {
               v = "";
               v.set_type(::e_type_null);
            }
            else
            {
               //if(r->m_record_header[i].type == sqlite::DataTypeDouble)
               //{
                 // v.SetDouble(strtod(reslt[i], nullptr));
               //}
               //if(r->m_record_header[i].type == sqlite::DataTypeLong)
               //{
                 // v.SetLong(atoi(reslt[i]));
               //}
               //else
               //{
                 // string str;
                  //utf8_to_unicode(str, reslt[i]);
               v = reslt[i];
               //}
            }
            rec.set_at_grow(i, v);//(long)5;//reslt[i];
         }
         r->m_records.set_at_grow(sz, rec);
      }
      //cout <<"Fsz:"<<r->m_record_header.size()<<"\n";
      // cout << "Recs:"<<r->m_records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
     return 0;
         //if ((ansi_count_compare("select",sql,6) == 0) || (ansi_count_compare("SELECT",sql,6) == 0))
         if(m_iLastResult = db->setErr(sqlite3_exec(handle(),sql,&callback,&m_resultsetExec,&errmsg)) == SQLITE_OK)
         {
            m_strQueryErrorMessage = "";
            m_strDatabaseErrorMessage = "";
            return true;
         }
         else
         {
            m_strQueryErrorMessage = errmsg;
            m_strDatabaseErrorMessage = db->getErrorMsg();
            FORMATTED_TRACE("sqlite::dataset::exec: Error %s, %s", errmsg, db->getErrorMsg());
            return false;
         }
      }

      database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
      i32 sz = r->m_records.get_size();

      //if (reslt == nullptr ) cout << "EMPTY!!!\n";
      if (r->m_record_header.get_size() <= 0)
      {
         r->m_record_header.set_size(ncol, 32);
         for (i32 i=0; i < ncol; i++)
         {
            r->m_record_header[i].name = cols[i];
            if(cols[i + ncol] != nullptr)
            {
               string str(cols[i + ncol]);
               str.make_lower();
               if(str == "integer")
               {
                  r->m_record_header[i].type = database::DataTypeLong;
               }
               else if(str == "string")
               {
                  r->m_record_header[i].type = database::DataTypeString;
               }
               else if(str == "numeric")
               {
                  r->m_record_header[i].type = database::DataTypeDouble;
               }
            }
         }
      }


      database::SqlRecord rec;
      ::payload v;

      if (reslt != nullptr)
      {
         for (i32 i=0; i<ncol; i++)
         {
            if (reslt[i] == nullptr)
            {
               v = "";
               v.set_type(::e_type_null);
            }
            else
            {
               //if(r->m_record_header[i].type == sqlite::DataTypeDouble)
               //{
                 // v.SetDouble(strtod(reslt[i], nullptr));
               //}
               //if(r->m_record_header[i].type == sqlite::DataTypeLong)
               //{
                 // v.SetLong(atoi(reslt[i]));
               //}
               //else
               //{
                 // string str;
                  //utf8_to_unicode(str, reslt[i]);
               v = reslt[i];
               //}
            }
            rec.set_at_grow(i, v);//(long)5;//reslt[i];
         }
         r->m_records.set_at_grow(sz, rec);
      }
      //cout <<"Fsz:"<<r->m_record_header.size()<<"\n";
      // cout << "Recs:"<<r->m_records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
     return 0;  */


   bool dataset::sql_do_select(const char * & pszSql)
   {
      string_array straField;

      string str;


      ::str::consume_spaces(pszSql, 0);

      if(::str::begins_consume(pszSql, "*"))
      {
         ::str::consume_spaces(pszSql, 0);
      }
      else
      {
         for(;;)
         {
            str = sql_consume_field(pszSql);
            if(str.is_empty())
            {
               return false;
            }
            straField.add(str);
            try
            {
               ::str::consume(pszSql, ",");
            }
            catch(...)
            {
               break;
            }
         }
      }
      str = sql_consume_keyword(pszSql);
      if(str != "from")
         return false;

      string_array straTable;
      for(;;)
      {
         str = sql_consume_table(pszSql);
         if(str.is_empty())
         {
            return false;
         }
         straTable.add("table:" + str);
         try
         {
            ::str::consume(pszSql, ",");
         }
         catch(...)
         {
            try
            {

               str = sql_consume_keyword(pszSql);
               if(str == "inner")
               {
                  str = sql_consume_keyword(pszSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:inner");
               }
               else if(str == "left")
               {
                  str = sql_consume_keyword(pszSql);
                  if(str != "outer")
                     return false;
                  str = sql_consume_keyword(pszSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:left_outer");
                  return false;
               }
               else if(str == "right")
               {
                  str = sql_consume_keyword(pszSql);
                  if(str != "outer")
                     return false;
                  str = sql_consume_keyword(pszSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:right_outer");
                  return false;
               }
               else if(str == "on")
               {
                  str = sql_consume_join_on(pszSql);
                  if(str.is_empty())
                     return false;
                  straTable.add("on:" + str);
               }
            }
            catch(...)
            {
               break;
            }
         }
      }

      if(straTable.get_count() == 1)
      {
         string strTable = straTable[0];
         if(strTable.case_insensitive_begins_eat("table:"))
         {
            ::simpledb::table table(dynamic_cast < ::simpledb::database * > (db), strTable);
            ::simpledb::record_row recrow;
            recrow.m_ptable = &table;
            filesize posEnd = (filesize) table.m_spfileFixed->get_length();
            table.m_spfileFixed->seek_to_begin();
            reader reader((::file::file *) table.m_spfileFixed.m_p);
            while(true)
            {
               if(table.m_spfileFixed->get_position() >= posEnd)
                  break;
               try
               {
                  reader(recrow);
               }
               catch(...)
               {
                  return false;
               }
               ::database::record rec;
               rec.::payload_array::operator = (recrow.m_var.payloada());
               m_resultset.m_records.add(rec);
               recrow.m_var.payloada().erase_all();
            }
         }
      }

      return true;

   }

   bool dataset::sql_do_insert(const char * & pszSql)
   {

      try
      {
         string str = sql_consume_keyword(pszSql);
         if(str != "into")
            return false;

         string strTable;
         strTable = sql_consume_table(pszSql);
         if(strTable.is_empty())
         {
            return false;
         }

         str = sql_consume_keyword(pszSql);
         if(str != "values")
            return false;

         ::str::consume_spaces(pszSql, 0);

         if(!::str::begins_consume(pszSql, "("))
            return false;

         ::str::consume_spaces(pszSql, 0);

         string_array straValue;
         for(;;)
         {
            try
            {
               str = sql_consume_value(pszSql);
            }
            catch(...)
            {
               break;
            }
            straValue.add(str);
            ::str::consume_spaces(pszSql, 0);
            if(::str::begins_consume(pszSql, ")"))
               break;
            if(!::str::begins_consume(pszSql, ","))
               return false;

         }


         if(straValue.get_count() <= 0)
            return false;


         ::simpledb::table table(dynamic_cast < ::simpledb::database * > (db), strTable);
         ::simpledb::record_row rec;
         rec.m_ptable = &table;
         rec.m_var = straValue;
         table.m_spfileFixed->seek_to_end();
         writer stream((::file::file *) table.m_spfileFixed.m_p);
         stream(rec);

         {
            ::database::record rec;
            rec.add(string("one row inserted"));
            m_resultset.m_records.add(rec);
         }
         return true;
      }
      catch(...)
      {
         ::database::record rec;
         rec.add(string("could not add row"));
         m_resultset.m_records.add(rec);
         return false;
      }


   }

   string dataset::consume_quoted_value(const char * & pszXml)
   {
      const ::scoped_string & scopedstr = pszXml;
      string qc = ::str::get_utf8_char(psz);
      if(qc != "\'")
      {
         throw ::exception(::exception("Quote character is required here"));
      }
      string str;
      while(true)
      {
         unicode_increment(psz);
         string qc2 = ::str::get_utf8_char(psz);
         //string str = utf8_to_unicode(qc2);
         if(qc2.is_empty())
         {
            throw ::exception(::exception("Quote character is required here, premature end"));
         }
         if(qc2 == qc)
            break;
         str += qc2;
      }
      unicode_increment(psz);
      pszXml = psz;
      return str;
   }

   string dataset::sql_consume_value(const char * & pszSql)
   {
      ::str::consume_spaces(pszSql, 0);
      string str = consume_quoted_value(pszSql);
      str.make_lower();
      return str;
   }

   string dataset::sql_consume_keyword(const char * & pszSql)
   {
      ::str::consume_spaces(pszSql, 0);
      string str = ::str::consume_nc_name(pszSql);
      str.make_lower();
      return str;
   }

   string dataset::sql_consume_field(const char * & pszSql)
   {
      ::str::consume_spaces(pszSql, 0);
      return ::str::consume_nc_name(pszSql);
   }

   string dataset::sql_consume_table(const char * & pszSql)
   {
      ::str::consume_spaces(pszSql, 0);
      return ::str::consume_nc_name(pszSql);
   }

   string dataset::sql_consume_join_on(const char * & pszSql)
   {
      UNREFERENCED_PARAMETER(pszSql);
      return "";
   }

   database * dataset::get_database()
   {
      return dynamic_cast < database * > (db);
   }

   void dataset::make_query(string_array &_sql)
   {
      string query;

      try
      {

         if(autocommit)
            db->start_transaction();

         if(db == nullptr)
            throw ::exception(::database::exception("No database Connection"));

         //close();

         for (i32 i = 0; i <_sql.get_size(); i++)
         {
            query = _sql.element_at(i);
//            char* err=nullptr;
            dataset::parse_sql(query);
            //cout << "Executing: "<<query<<"\n\n";
            /*            if (db->setErr(sqlite3_exec((::sqlite3::sqlite3 *) this->handle(),query,nullptr,nullptr,&err))!=SQLITE_OK)
                        {
                           fprintf(stderr,"Error: %s",err);
                           throw ::exception(::database::exception(db->getErrorMsg()));
                        }*/
         } // end of for


         if(db->in_transaction() && autocommit)
            db->commit_transaction();

         active = true;
         m_edataset = ::database::dataset_select;
         refresh();

      } // end of try
      catch(...)
      {
         if (db->in_transaction()) db->rollback_transaction();
      }
   }


   void dataset::make_insert()
   {
      //make_query(insert_sql);
      last();
   }


   void dataset::make_edit()
   {
      //make_query(update_sql);
   }


   void dataset::make_deletion()
   {
      //make_query(delete_sql);
   }


   void dataset::fill_fields()
   {
      //cout <<"rr "<<m_resultset.m_records.size()<<"|" << frecno <<"\n";
      /*if ((db == nullptr)
      || (m_resultset.m_record_header.get_size() == 0)
      || (m_resultset.m_records.get_size() < frecno))
         return;

      if (fields_object.get_size() == 0) // Filling columns name
      {
         fields_object.set_size(m_resultset.m_record_header.get_size());
         edit_object.set_size(m_resultset.m_record_header.get_size());
         for (i32 i = 0; i < m_resultset.m_record_header.get_size(); i++)
         {
            fields_object[i].m_properties    = m_resultset.m_record_header[i];
            edit_object[i].m_properties      = m_resultset.m_record_header[i];
         }
      }

      //Filling m_resultset
      if (m_resultset.m_records.get_size() != 0)
      {
         for (i32 i = 0; i < m_resultset.m_records[frecno].get_size(); i++)
         {
            fields_object[i].m_value   = m_resultset.m_records[frecno][i];
            edit_object[i].m_value     = m_resultset.m_records[frecno][i];
         }
      }
      else
         for (i32 i = 0; i < m_resultset.m_record_header.get_size(); i++)
         {
            fields_object[i].m_value = "";
            edit_object[i].m_value = "";
         }
         */
   }



   bool dataset::exec()
   {
      return exec(sql);
   }

   const void * dataset::getExecRes()
   {
      return &m_resultsetExec;
   }


   bool dataset::query(const ::string &query)
   {
      UNREFERENCED_PARAMETER(query);
      if(db == nullptr)
      {
         TRACE("dataset::query: database is not Defined");
         m_strQueryErrorMessage = "database is not defined";
         m_strDatabaseErrorMessage = "database is not defined";
         return false;
      }
      if(dynamic_cast<database*>(db) == nullptr)
      {
         TRACE("dataset::query: database is not valid");
         m_strQueryErrorMessage = "database is not valid";
         m_strDatabaseErrorMessage = "database is not valid";
         return false;
      }
      /*      if(dynamic_cast<database*>(db)->getHandle() == nullptr)
            {
               TRACE("dataset::query: No database connection");
               m_strQueryErrorMessage = "No database Connection";
               m_strDatabaseErrorMessage = "No database Connection";
               return false;
            }
            if(ansi_count_compare("select",query,6) != 0)
            {
               TRACE("dataset::query: Must be select SQL");
               return false;
            }

            close();

            if(db->setErr(sqlite3_exec((::sqlite3::sqlite3 *) handle(),query,&callback,&m_resultset,&errmsg)) == SQLITE_OK)
            {
               m_strQueryErrorMessage = "";
               m_strDatabaseErrorMessage = "";
               active = true;
               m_edataset = database::dataset_select;
               first();
               return true;
            }
            else
            {
               //m_strQueryErrorMessage = errmsg;
               //m_strDatabaseErrorMessage = db->getErrorMsg();
               //FORMATTED_TRACE("dataset::query: Error: %s, %s", errmsg, db->getErrorMsg());
               //return false;
            }*/
      return false;
   }

   void dataset::open(const ::string & sql)
   {
      set_select_sql(sql);
      open();
   }

   void dataset::open()
   {
      if (!select_sql.is_empty())
      {
         //cout <<select_sql <<"  open\n\n";
         query(select_sql);
      }
      else
      {
         m_edataset = ::database::dataset_none;
      }
   }


   void dataset::close()
   {
      ::database::dataset::close();
      m_resultset.m_record_header.erase_all();
      m_resultset.m_records.erase_all();
      edit_object.erase_all();
      fields_object.erase_all();
      m_edataset = ::database::dataset_none;
      active = false;
   }


   void dataset::cancel()
   {
      if ((m_edataset == ::database::dsInsert) || (m_edataset==::database::dsEdit))
      {
         if(m_resultset.m_record_header.get_size())
         {
            m_edataset = ::database::dataset_select;
         }
         else
         {
            m_edataset = ::database::dataset_none;
         }
      }
   }


   ::count dataset::num_rows()
   {
      return m_resultset.m_records.get_size();
   }


   bool dataset::eof()
   {
      return feof;
   }


   bool dataset::bof()
   {
      return fbof;
   }


   void dataset::first()
   {
      ::database::dataset::first();
      this->fill_fields();
      //cout << "In first "<< fields_object.size()<<"\n";
   }

   void dataset::last()
   {
      ::database::dataset::last();
      fill_fields();
   }

   void dataset::prev()
   {
      ::database::dataset::prev();
      fill_fields();
   }

   void dataset::next()
   {
      ::database::dataset::next();
      if (!eof())
         fill_fields();
   }


   bool dataset::seek(index pos)
   {
      if (m_edataset == ::database::dataset_select)
      {
         dataset::seek(pos);
         fill_fields();
         return true;
      }
      return false;
   }



   long dataset::nextid(const ::string &seq_name)
   {
      UNREFERENCED_PARAMETER(seq_name);
      /*      if(handle())
               return db->nextid(seq_name);
            else*/
      return DB_UNEXPECTED_RESULT;
   }

   bool dataset::erase_row()
   {
      if(feof || fbof)
      {
         return false;
      }

      m_resultset.m_records.erase_at(frecno);

      fbof = feof = (num_rows()==0)? true: false;

      return true;
   }

   bool dataset::SetFieldValue(const ::string &f_name, const ::payload &value)
   {
      bool found = false;
      if(m_edataset == ::database::dataset_select)
      {
         for (i32 i=0; i < fields_object.get_size(); i++)
         {
            if(m_resultset.m_record_header[i].name == f_name)
            {
               m_resultset.m_records[frecno][i] = value;
               found = true;
            }
         }
         if (!found)
         {
            throw ::exception(::database::exception("Field not found: %s",f_name));
         }
         return true;
      }
      else
      {
         return dataset::SetFieldValue(f_name, value);
      }

      //throw ::exception(::database::exception("Not in Insert or Edit or Select state"));
      //  return false;

   }


   bool dataset::SetFieldValue(index iFieldIndex, const ::payload &value)
   {
      if(m_edataset == ::database::dataset_select)
      {
         if(iFieldIndex >= 0 && iFieldIndex < m_resultset.m_record_header.get_size())
         {
            m_resultset.m_records[frecno][iFieldIndex] = value;
            return true;
         }
         else
         {
            throw ::exception(::database::exception("Field not found: %d",iFieldIndex));
         }
      }
      else
      {
         ASSERT(false);
         //      return dataset::SetFieldValue(f_name, value);
      }
      throw ::exception(::database::exception("Not in Insert or Edit or Select state"));
      //  return false;
   }

   ::payload & dataset::FieldValueAt(index iFieldIndex)
   {
      //if(m_edataset == dataset_select)
      {
         if(iFieldIndex >= 0 && iFieldIndex < m_resultset.m_record_header.get_size())
         {
            return m_resultset.m_records[frecno][iFieldIndex];
         }
         else
         {
            throw ::exception(::database::exception("Field not found: %d",iFieldIndex));
         }
      }
      //   else
      {
         ASSERT(false);
         //return dataset::SetFieldValue(f_name, value);

      }
      //throw ::exception(::database::exception("Not in Insert or Edit or Select state"));
      //  return false;
   }

   i32 dataset::GetFieldIndex(const ::string &f_name)
   {
      for (i32 i=0; i < fields_object.get_size(); i++)
      {
         if(m_resultset.m_record_header[i].name == f_name)
         {
            return i;

         }
      }
      return -1;
   }

   bool dataset::find_first(char * fieldname, ::payload & value)
   {
      index iFound = -1;
      if(m_edataset == ::database::dataset_select)
      {
         index i;
         for(i=0; i < fields_object.get_size(); i++)
            if(m_resultset.m_record_header[i].name == fieldname)
            {
               iFound = i;
               break;
            }
         if (iFound < 0) throw ::exception(::database::exception("Field not found: %s",fieldname));
         ::count iNumRows = num_rows();
         for(i=0; i < iNumRows; i++)
            if(m_resultset.m_records[i][iFound] == value)
            {
               seek(i);
               return true;
            }

         return false;
      }
      throw ::exception(::database::exception("not in Select state"));
   }

   void dataset::query_items(string_array & stra, const ::string & pszSql)
   {
      if(query(pszSql))
      {
         first();
         while(!eof())
         {
            stra.add(FieldValueAt(0).get_string());
            next();
         }
      }
   }


   /**********************************************************************
   * Copyright (ca) 2002, Leo Seib, Hannover
   *
   * Project:CSQLiteDataset C++ Dynamic Library
   * Module: CSQLiteDataset class realisation file
   * Author: Leo Seib      E-Mail: lev@almaty.pointstrike.net
   * begin: 5/04/2002
   *
   * Permission is hereby granted, free of charge, to any person obtaining a copy
   * of this software and associated documentation files (the "Software"), to deal
   * in the Software without restriction, including without limitation the rights
   * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   * copies of the Software, and to permit persons to whom the Software is
   * furnished to do so, topic to the following conditions:
   *
   * The above copyright notice and this permission notice shall be included in
   * all copies or substantial portions of the Software.
   *
   * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
   * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   * THE SOFTWARE.
   *
   **********************************************************************/
   //************* Callback function ***************************

   i32 callback(void * res_ptr,i32 ncol, char** reslt,char** cols)
   {

      ::database::result_set* r = (::database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
      ::count sz = r->m_records.get_size();

      //if (reslt == nullptr ) cout << "EMPTY!!!\n";
      if (r->m_record_header.get_size() <= 0)
      {
         r->m_record_header.set_size(ncol, 32);
         for (index i=0; i < ncol; i++)
         {
            r->m_record_header[i].name = cols[i];
            if(cols[i + ncol] != nullptr)
            {
               string str(cols[i + ncol]);
               str.make_lower();
               if(str == "integer")
               {
                  r->m_record_header[i].type = ::database::DataTypeLong;
               }
               else if(str == "string")
               {
                  r->m_record_header[i].type =::database::DataTypeString;
               }
               else if(str == "numeric")
               {
                  r->m_record_header[i].type = ::database::DataTypeDouble;
               }
            }
         }
      }


      ::database::record rec;
      ::payload v;

      if (reslt != nullptr)
      {
         for (i32 i=0; i<ncol; i++)
         {
            if (reslt[i] == nullptr)
            {
               v = "";
               v.set_type(::e_type_null);
            }
            else
            {
               //if(r->m_record_header[i].type == sqlite::DataTypeDouble)
               //{
               // v.SetDouble(strtod(reslt[i], nullptr));
               //}
               //if(r->m_record_header[i].type == sqlite::DataTypeLong)
               //{
               // v.SetLong(atoi(reslt[i]));
               //}
               //else
               //{
               // string str;
               //utf8_to_unicode(str, reslt[i]);
               v = reslt[i];
               //}
            }
            rec.set_at_grow(i, v);//(long)5;//reslt[i];
         }
         r->m_records.set_at_grow(sz, rec);
      }
      //cout <<"Fsz:"<<r->m_record_header.size()<<"\n";
      // cout << "Recs:"<<r->m_records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
      return 0;
   }


} // namespace simpledb
