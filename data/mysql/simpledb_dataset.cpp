#include "framework.h"

namespace simpledb
{

   int callback(void * res_ptr,int ncol, char** reslt,char** cols);

   set::set() :
      ::database::set()
   {
      //errmsg      = nullptr;
      haveError   = false;
      db          = nullptr;
   }


   set::set(base *newDb) :
      ::database::set(newDb)
   {
      //errmsg      = nullptr;
      haveError = false;
      db = newDb;
   }

   set::~set()
   {
      //  if(errmsg != nullptr)
      //  {
      //      sqlite_free_table(&errmsg);
      // }
   }

   bool set::exec(const ::scoped_string & scopedstrSql)
   {
      ::database::result_set * r = (::database::result_set *) &m_resultset;
      r->record_header.erase_all();
      r->records.erase_all();

      string strInstruction = sql_consume_keyword(scopedstrSql);

      if(strInstruction == "select")
      {
         return sql_do_select(scopedstrSql);
      }
      else if(strInstruction == "insert")
      {
         return sql_do_insert(scopedstrSql);
      }

      return false;
   }
   /*if (!handle())
   {
      informationf("sqlite::set::exec: No Database Connection");
      m_strQueryErrorMessage = "No Database Connection";
      m_strDatabaseErrorMessage = "No Database Connection";
      return false;
   }*/
   /*      m_resultsetExec.record_header.erase_all();
         m_resultsetExec.records.erase_all();
      database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
      int sz = r->records.get_size();

      //if (reslt == nullptr ) cout << "EMPTY!!!\n";
      if (r->record_header.get_size() <= 0)
      {
         r->record_header.set_size(ncol, 32);
         for (int i=0; i < ncol; i++)
         {
            r->record_header[i].name = cols[i];
            if(cols[i + ncol] != nullptr)
            {
               string str(cols[i + ncol]);
               str.make_lower();
               if(str == "integer")
               {
                  r->record_header[i].type = database::DataTypeLong;
               }
               else if(str == "string")
               {
                  r->record_header[i].type = database::DataTypeString;
               }
               else if(str == "numeric")
               {
                  r->record_header[i].type = database::DataTypeDouble;
               }
            }
         }
      }


      database::SqlRecord rec;
      ::payload v;

      if (reslt != nullptr)
      {
         for (int i=0; i<ncol; i++)
         {
            if (reslt[i] == nullptr)
            {
               v = "";
               v.set_type(::e_type_null);
            }
            else
            {
               //if(r->record_header[i].type == sqlite::DataTypeDouble)
               //{
                 // v.SetDouble(strtod(reslt[i], nullptr));
               //}
               //if(r->record_header[i].type == sqlite::DataTypeLong)
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
         r->records.set_at_grow(sz, rec);
      }
      //cout <<"Fsz:"<<r->record_header.size()<<"\n";
      // cout << "Recs:"<<r->records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
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
            informationf("sqlite::set::exec: Error %s, %s", errmsg, db->getErrorMsg());
            return false;
         }
      }

      database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
      int sz = r->records.get_size();

      //if (reslt == nullptr ) cout << "EMPTY!!!\n";
      if (r->record_header.get_size() <= 0)
      {
         r->record_header.set_size(ncol, 32);
         for (int i=0; i < ncol; i++)
         {
            r->record_header[i].name = cols[i];
            if(cols[i + ncol] != nullptr)
            {
               string str(cols[i + ncol]);
               str.make_lower();
               if(str == "integer")
               {
                  r->record_header[i].type = database::DataTypeLong;
               }
               else if(str == "string")
               {
                  r->record_header[i].type = database::DataTypeString;
               }
               else if(str == "numeric")
               {
                  r->record_header[i].type = database::DataTypeDouble;
               }
            }
         }
      }


      database::SqlRecord rec;
      ::payload v;

      if (reslt != nullptr)
      {
         for (int i=0; i<ncol; i++)
         {
            if (reslt[i] == nullptr)
            {
               v = "";
               v.set_type(::e_type_null);
            }
            else
            {
               //if(r->record_header[i].type == sqlite::DataTypeDouble)
               //{
                 // v.SetDouble(strtod(reslt[i], nullptr));
               //}
               //if(r->record_header[i].type == sqlite::DataTypeLong)
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
         r->records.set_at_grow(sz, rec);
      }
      //cout <<"Fsz:"<<r->record_header.size()<<"\n";
      // cout << "Recs:"<<r->records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
     return 0;  */


   bool set::sql_do_select(const char * & pszSql)
   {
      string_array straField;

      string str;


      ::str::consume_spaces(scopedstrSql, 0);

      if(::str::begins_consume(scopedstrSql, "*"))
      {
         ::str::consume_spaces(scopedstrSql, 0);
      }
      else
      {
         for(;;)
         {
            str = sql_consume_field(scopedstrSql);
            if(str.is_empty())
            {
               return false;
            }
            straField.add(str);
            try
            {
               ::str::consume(scopedstrSql, ",");
            }
            catch(...)
            {
               break;
            }
         }
      }
      str = sql_consume_keyword(scopedstrSql);
      if(str != "from")
         return false;

      string_array straTable;
      for(;;)
      {
         str = sql_consume_table(scopedstrSql);
         if(str.is_empty())
         {
            return false;
         }
         straTable.add("table:" + str);
         try
         {
            ::str::consume(scopedstrSql, ",");
         }
         catch(...)
         {
            try
            {

               str = sql_consume_keyword(scopedstrSql);
               if(str == "inner")
               {
                  str = sql_consume_keyword(scopedstrSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:inner");
               }
               else if(str == "left")
               {
                  str = sql_consume_keyword(scopedstrSql);
                  if(str != "outer")
                     return false;
                  str = sql_consume_keyword(scopedstrSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:left_outer");
                  return false;
               }
               else if(str == "right")
               {
                  str = sql_consume_keyword(scopedstrSql);
                  if(str != "outer")
                     return false;
                  str = sql_consume_keyword(scopedstrSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:right_outer");
                  return false;
               }
               else if(str == "on")
               {
                  str = sql_consume_join_on(scopedstrSql);
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
            ::simpledb::table table(dynamic_cast < ::simpledb::base * > (db), strTable);
            ::simpledb::record_row recrow;
            recrow.m_ptable = &table;
            filesize posEnd = (filesize) table.m_spfileFixed->get_length();
            table.m_spfileFixed->seek_to_begin();
            stream stream((::file::file *) table.m_spfileFixed.m_p);
            while(true)
            {
               if(table.m_spfileFixed->get_position() >= posEnd)
                  break;
               try
               {
                  recrow.read(stream);
               }
               catch(...)
               {
                  return false;
               }
               ::database::record rec;
               rec.::payload_array::operator = (recrow.m_var.payloada());
               m_resultset.records.add(rec);
               recrow.m_var.payloada().erase_all();
            }
         }
      }

      return true;

   }

   bool set::sql_do_insert(const char * & pszSql)
   {

      try
      {
         string str = sql_consume_keyword(scopedstrSql);
         if(str != "into")
            return false;

         string strTable;
         strTable = sql_consume_table(scopedstrSql);
         if(strTable.is_empty())
         {
            return false;
         }

         str = sql_consume_keyword(scopedstrSql);
         if(str != "values")
            return false;

         ::str::consume_spaces(scopedstrSql, 0);

         if(!::str::begins_consume(scopedstrSql, "("))
            return false;

         ::str::consume_spaces(scopedstrSql, 0);

         string_array straValue;
         for(;;)
         {
            try
            {
               str = sql_consume_value(scopedstrSql);
            }
            catch(...)
            {
               break;
            }
            straValue.add(str);
            ::str::consume_spaces(scopedstrSql, 0);
            if(::str::begins_consume(scopedstrSql, ")"))
               break;
            if(!::str::begins_consume(scopedstrSql, ","))
               return false;

         }


         if(straValue.get_count() <= 0)
            return false;


         ::simpledb::table table(dynamic_cast < ::simpledb::base * > (db), strTable);
         ::simpledb::record_row rec;
         rec.m_ptable = &table;
         rec.m_var = straValue;
         table.m_spfileFixed->seek_to_end();
         stream stream((::file::file *) table.m_spfileFixed.m_p);
         rec.write(stream);

         {
            ::database::record rec;
            rec.add(string("one row inserted"));
            m_resultset.records.add(rec);
         }
         return true;
      }
      catch(...)
      {
         ::database::record rec;
         rec.add(string("could not add row"));
         m_resultset.records.add(rec);
         return false;
      }


   }

   string set::consume_quoted_value(const char * & pszXml)
   {
      const ::scoped_string & scopedstr = pszXml;
      string qc = ::str::get_utf8_char(scopedstr);
      if(qc != "\'")
      {
         throw ::exception(::exception("Quote character is required here"));
      }
      string str;
      while(true)
      {
         unicode_increment(scopedstr);
         string qc2 = ::str::get_utf8_char(scopedstr);
         //string str = utf8_to_unicode(qc2);
         if(qc2.is_empty())
         {
            throw ::exception(::exception("Quote character is required here, premature end"));
         }
         if(qc2 == qc)
            break;
         str += qc2;
      }
      unicode_increment(scopedstr);
      pszXml = psz;
      return str;
   }

   string set::sql_consume_value(const char * & pszSql)
   {
      ::str::consume_spaces(scopedstrSql, 0);
      string str = consume_quoted_value(scopedstrSql);
      str.make_lower();
      return str;
   }

   string set::sql_consume_keyword(const char * & pszSql)
   {
      ::str::consume_spaces(scopedstrSql, 0);
      string str = ::str::consume_nc_name(scopedstrSql);
      str.make_lower();
      return str;
   }

   string set::sql_consume_field(const char * & pszSql)
   {
      ::str::consume_spaces(scopedstrSql, 0);
      return ::str::consume_nc_name(scopedstrSql);
   }

   string set::sql_consume_table(const char * & pszSql)
   {
      ::str::consume_spaces(scopedstrSql, 0);
      return ::str::consume_nc_name(scopedstrSql);
   }

   string set::sql_consume_join_on(const char * & pszSql)
   {
      __UNREFERENCED_PARAMETER(scopedstrSql);
      return "";
   }

   base * set::get_database()
   {
      return dynamic_cast < base * > (db);
   }

   void set::make_query(string_array &_sql)
   {
      string query;

      try
      {

         if(autocommit)
            db->start_transaction();

         if(db == nullptr)
            throw ::exception(::database::exception("No base Connection"));

         //close();

         for (int i = 0; i <_sql.get_size(); i++)
         {
            query = _sql.element_at(i);
//            char* err=nullptr;
            set::parse_sql(query);
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
         ds_state = ::database::dataset_select;
         refresh();

      } // end of try
      catch(...)
      {
         if (db->in_transaction()) db->rollback_transaction();
      }
   }


   void set::make_insert()
   {
      //make_query(insert_sql);
      last();
   }


   void set::make_edit()
   {
      //make_query(update_sql);
   }


   void set::make_deletion()
   {
      //make_query(delete_sql);
   }


   void set::fill_fields()
   {
      //cout <<"rr "<<m_resultset.records.size()<<"|" << frecno <<"\n";
      /*if ((db == nullptr)
      || (m_resultset.record_header.get_size() == 0)
      || (m_resultset.records.get_size() < frecno))
         return;

      if (fields_object.get_size() == 0) // Filling columns name
      {
         fields_object.set_size(m_resultset.record_header.get_size());
         edit_object.set_size(m_resultset.record_header.get_size());
         for (int i = 0; i < m_resultset.record_header.get_size(); i++)
         {
            fields_object[i].m_properties    = m_resultset.record_header[i];
            edit_object[i].m_properties      = m_resultset.record_header[i];
         }
      }

      //Filling m_resultset
      if (m_resultset.records.get_size() != 0)
      {
         for (int i = 0; i < m_resultset.records[frecno].get_size(); i++)
         {
            fields_object[i].m_value   = m_resultset.records[frecno][i];
            edit_object[i].m_value     = m_resultset.records[frecno][i];
         }
      }
      else
         for (int i = 0; i < m_resultset.record_header.get_size(); i++)
         {
            fields_object[i].m_value = "";
            edit_object[i].m_value = "";
         }
         */
   }



   bool set::exec()
   {
      return exec(sql);
   }

   const void * set::getExecRes()
   {
      return &m_resultsetExec;
   }


   bool set::query(const ::scoped_string & scopedstrQuery)
   {
      __UNREFERENCED_PARAMETER(query);
      if(db == nullptr)
      {
         informationf("set::query: base is not Defined");
         m_strQueryErrorMessage = "base is not defined";
         m_strDatabaseErrorMessage = "base is not defined";
         return false;
      }
      if(dynamic_cast<base*>(db) == nullptr)
      {
         informationf("set::query: base is not valid");
         m_strQueryErrorMessage = "base is not valid";
         m_strDatabaseErrorMessage = "base is not valid";
         return false;
      }
      /*      if(dynamic_cast<base*>(db)->getHandle() == nullptr)
            {
               informationf("set::query: No base connection");
               m_strQueryErrorMessage = "No base Connection";
               m_strDatabaseErrorMessage = "No base Connection";
               return false;
            }
            if(ansi_count_compare("select",query,6) != 0)
            {
               informationf("set::query: Must be select SQL");
               return false;
            }

            close();

            if(db->setErr(sqlite3_exec((::sqlite3::sqlite3 *) handle(),query,&callback,&m_resultset,&errmsg)) == SQLITE_OK)
            {
               m_strQueryErrorMessage = "";
               m_strDatabaseErrorMessage = "";
               active = true;
               ds_state = database::dataset_select;
               first();
               return true;
            }
            else
            {
               //m_strQueryErrorMessage = errmsg;
               //m_strDatabaseErrorMessage = db->getErrorMsg();
               //informationf("set::query: Error: %s, %s", errmsg, db->getErrorMsg());
               //return false;
            }*/
      return false;
   }

   void set::open(const ::scoped_string & scopedstrSql)
   {
      set_select_sql(sql);
      open();
   }

   void set::open()
   {
      if (!select_sql.is_empty())
      {
         //cout <<select_sql <<"  open\n\n";
         query(select_sql);
      }
      else
      {
         ds_state = ::database::dataset_none;
      }
   }


   void set::close()
   {
      ::database::set::close();
      m_resultset.record_header.erase_all();
      m_resultset.records.erase_all();
      edit_object.erase_all();
      fields_object.erase_all();
      ds_state = database::dataset_none;
      active = false;
   }


   void set::cancel()
   {
      if ((ds_state == database::dsInsert) || (ds_state==database::dsEdit))
      {
         if(m_resultset.record_header.get_size())
         {
            ds_state = database::dataset_select;
         }
         else
         {
            ds_state = database::dataset_none;
         }
      }
   }


   ::collection::count set::num_rows()
   {
      return m_resultset.records.get_size();
   }


   bool set::eof()
   {
      return feof;
   }


   bool set::bof()
   {
      return fbof;
   }


   void set::first()
   {
      ::database::set::first();
      this->fill_fields();
      //cout << "In first "<< fields_object.size()<<"\n";
   }

   void set::last()
   {
      ::database::set::last();
      fill_fields();
   }

   void set::prev()
   {
      ::database::set::prev();
      fill_fields();
   }

   void set::next()
   {
      ::database::set::next();
      if (!eof())
         fill_fields();
   }


   bool set::seek(index pos)
   {
      if (ds_state == database::dataset_select)
      {
         set::seek(pos);
         fill_fields();
         return true;
      }
      return false;
   }



   long set::nextid(const ::string &seq_name)
   {
      __UNREFERENCED_PARAMETER(seq_name);
      /*      if(handle())
               return db->nextid(seq_name);
            else*/
      return DB_UNEXPECTED_RESULT;
   }

   bool set::erase_row()
   {
      if(feof || fbof)
      {
         return false;
      }

      m_resultset.records.erase_at(frecno);

      fbof = feof = (num_rows()==0)? true: false;

      return true;
   }

   bool set::SetFieldValue(const ::string &f_name, const ::payload &value)
   {
      bool found = false;
      if(ds_state == database::dataset_select)
      {
         for (int i=0; i < fields_object.get_size(); i++)
         {
            if(m_resultset.record_header[i].name == f_name)
            {
               m_resultset.records[frecno][i] = value;
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
         return set::SetFieldValue(f_name, value);
      }
      throw ::exception(::database::exception("Not in Insert or Edit or Select state"));
      //  return false;
   }

   bool set::SetFieldValue(::collection::index iFieldIndex, const ::payload &value)
   {
      if(ds_state == database::dataset_select)
      {
         if(iFieldIndex >= 0 && iFieldIndex < m_resultset.record_header.get_size())
         {
            m_resultset.records[frecno][iFieldIndex] = value;
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
         //      return set::SetFieldValue(f_name, value);
      }
      throw ::exception(::database::exception("Not in Insert or Edit or Select state"));
      //  return false;
   }

   ::payload & set::FieldValueAt(::collection::index iFieldIndex)
   {
      //if(ds_state == dataset_select)
      {
         if(iFieldIndex >= 0 && iFieldIndex < m_resultset.record_header.get_size())
         {
            return m_resultset.records[frecno][iFieldIndex];
         }
         else
         {
            throw ::exception(::database::exception("Field not found: %d",iFieldIndex));
         }
      }
      //   else
      {
         ASSERT(false);
         //return set::SetFieldValue(f_name, value);

      }
      throw ::exception(::database::exception("Not in Insert or Edit or Select state"));
      //  return false;
   }

   int set::GetFieldIndex(const ::string &f_name)
   {
      for (int i=0; i < fields_object.get_size(); i++)
      {
         if(m_resultset.record_header[i].name == f_name)
         {
            return i;

         }
      }
      return -1;
   }

   bool set::find_first(char * fieldname, ::payload & value)
   {
      ::collection::index iFound = -1;
      if(ds_state == database::dataset_select)
      {
         ::collection::index i;
         for(i=0; i < fields_object.get_size(); i++)
            if(m_resultset.record_header[i].name == fieldname)
            {
               iFound = i;
               break;
            }
         if (iFound < 0) throw ::exception(::database::exception("Field not found: %s",fieldname));
         ::collection::count iNumRows = num_rows();
         for(i=0; i < iNumRows; i++)
            if(m_resultset.records[i][iFound] == value)
            {
               seek(i);
               return true;
            }

         return false;
      }
      throw ::exception(::database::exception("not in Select state"));
   }

   void set::query_items(string_array & stra, const ::scoped_string & scopedstrSql)
   {
      if(query(scopedstrSql))
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

   int callback(void * res_ptr,int ncol, char** reslt,char** cols)
   {

      database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
      ::collection::count sz = r->records.get_size();

      //if (reslt == nullptr ) cout << "EMPTY!!!\n";
      if (r->record_header.get_size() <= 0)
      {
         r->record_header.set_size(ncol, 32);
         for (::collection::index i=0; i < ncol; i++)
         {
            r->record_header[i].name = cols[i];
            if(cols[i + ncol] != nullptr)
            {
               string str(cols[i + ncol]);
               str.make_lower();
               if(str == "integer")
               {
                  r->record_header[i].type = database::DataTypeLong;
               }
               else if(str == "string")
               {
                  r->record_header[i].type = database::DataTypeString;
               }
               else if(str == "numeric")
               {
                  r->record_header[i].type = database::DataTypeDouble;
               }
            }
         }
      }


      database::record rec;
      ::payload v;

      if (reslt != nullptr)
      {
         for (int i=0; i<ncol; i++)
         {
            if (reslt[i] == nullptr)
            {
               v = "";
               v.set_type(::e_type_null);
            }
            else
            {
               //if(r->record_header[i].type == sqlite::DataTypeDouble)
               //{
               // v.SetDouble(strtod(reslt[i], nullptr));
               //}
               //if(r->record_header[i].type == sqlite::DataTypeLong)
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
         r->records.set_at_grow(sz, rec);
      }
      //cout <<"Fsz:"<<r->record_header.size()<<"\n";
      // cout << "Recs:"<<r->records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
      return 0;
   }


} // namespace simpledb
