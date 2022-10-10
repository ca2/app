#pragma once


#include "result_set.h"
#include "parameter_list.h"


namespace database
{


   class database;


   class CLASS_DECL_AXIS dataset :
      virtual public ::object
   {
   public:


      database *        m_pdatabase;
      enum_dataset      m_edataset;
      //field_array       m_fielda;
      ::database::row   m_row;
      ::database::row   m_rowEdit;
      result_set        m_result;


      bool              m_bActive;
      bool              m_bError;
      i32           m_iLastResult;
      string            m_strQueryErrorMessage;
      string            m_strDatabaseErrorMessage;

      str_helper        m_strhelper;

      parameter_list    m_parameterlist;
      //bool              m_bBOF;
      //bool              m_bEOF;
      bool              m_bAutoCommit;

      string            m_strSqlExecute;

      string            m_strSqlEmpty;       // Executed when result dataset is is_empty
      string            m_strSqlSelect;       // May be only single string ::payload

      string_array           m_strSqlUpdate;       // May be an array in complex queries
      /* Field values for updating must has prefix :NEW_ and :OLD_ and field name
         Example:
         update  wt_story dataset idobject dataset idobject=:NEW_idobject,body=:NEW_body
         where idobject=:OLD_idobject
         Essentually fields idobject and body must present in the
         result dataset (select_sql statement) */

      string_array           m_strSqlInsert;       // May be an array in complex queries
      /* Field values for inserting must has prefix :NEW_ and field name
         Example:
         insert into wt_story (idobject, body) values (:NEW_idobject, :NEW_body)
         Essentually fields idobject and body must present in the
         result dataset (select_sql statement) */

      string_array           m_strSqlDelete;       // May be an array in complex queries
      /* Field values for deleing must has prefix :OLD_ and field name
         Example:
         delete from wt_story where idobject=:OLD_idobject
         Essentually field idobject must present in the
         result dataset (select_sql statement) */


      virtual void make_insert() = 0;
      virtual void make_edit() = 0;
      virtual void make_deletion() = 0;

      virtual void fill_fields()=0;

      void parse_sql(const ::string & sql);

      dataset(database * pdatabase);

      virtual ~dataset();

      virtual database * get_database() { return m_pdatabase; }
      virtual void * get_handle();

      //virtual bool isActive() { return isActive(); }

      virtual ::count num_rows()= 0;

      virtual void open(const ::string & sql) = 0;
      virtual void open() = 0;
      virtual bool exec(const ::string & sql) = 0;
      virtual bool exec() = 0;
      virtual bool query(const ::string &sql) = 0;

      virtual void close();



      virtual void insert();
      virtual void append() { insert(); }
      virtual void edit();

      virtual void post();
      virtual void deletion();
      virtual void cancel() {};

      //virtual void setParamList(const parameter_list &params);
      //virtual bool locate();
      //virtual bool locate(const parameter_list &params);
      //virtual bool findNext();

      virtual ::count field_count();
      virtual ::pointer<class field> field_at(index n);

      virtual ::database::row * proper_row();


      //virtual bool set_field_value(const ::string &f, const ::payload &v);

      virtual class field * field(const ::string & name);
      virtual ::payload field_value(const ::string & name);
      virtual ::payload select_field_value(index iField);
      virtual ::payload field_value_at(index i);

      virtual index field_index(const ::string & name);

      virtual void set_autocommit(bool bAutoCommit) { m_bAutoCommit = bAutoCommit; }
      virtual bool get_autocommit() { return m_bAutoCommit; }

      ::pointer<field_array>& fields() { return m_result.m_pfielda; }
      ::database::row & row() { return m_row; }
      ::database::row & edit_row() { return m_rowEdit; }

      void set_dataset_state(enum_dataset new_state) {m_edataset = new_state;};

      enum_dataset get_dataset_state() {return m_edataset; }

      virtual void set_sql(enum_sql esql, const ::string & sql);

      virtual void clear_sql(enum_sql esql);

      virtual string get_sql(enum_sql esql);

      virtual ::pointer<row_array>query_rows(const ::string &query);
      virtual ::pointer<payload_array>query_items(const ::string &query);
      virtual ::payload query_item(const ::string &query);

      virtual bool query_rows(::pointer<row_array>& rows, const ::string &query);
      virtual bool query_items(::pointer<payload_array>& items, const ::string &query);
      virtual bool query_item(::payload & item, const ::string &query);

   };


} // namespace sqlite




