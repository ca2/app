#pragma once


namespace database
{


   class database;


   class CLASS_DECL_AQUA dataset :
      virtual public ::object
   {
   public:


      database *        m_pdatabase;
      e_dataset         m_edataset;
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
      string            m_strSqlSelect;       // May be only single string var

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

      void parse_sql(const char * sql);

      dataset(database * pdatabase);

      virtual ~dataset();

      virtual database * get_database() { return m_pdatabase; }
      virtual void * get_handle();

      virtual bool isActive() { return m_bActive; }

      virtual ::count num_rows()= 0;

      virtual void open(const char * sql) = 0;
      virtual void open() = 0;
      virtual bool exec(const char * sql) = 0;
      virtual bool exec() = 0;
      virtual bool query(const char *sql) = 0;

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
      virtual __pointer(class field) field_at(index n);

      virtual ::database::row * proper_row();


      //virtual bool set_field_value(const char *f, const var &v);

      virtual class field * field(const char * name);
      virtual var field_value(const char * name);
      virtual var select_field_value(index iField);
      virtual var field_value_at(index i);

      virtual index field_index(const char * name);

      virtual void set_autocommit(bool bAutoCommit) { m_bAutoCommit = bAutoCommit; }
      virtual bool get_autocommit() { return m_bAutoCommit; }

      __pointer(field_array) & fields() { return m_result.m_pfielda; }
      ::database::row & row() { return m_row; }
      ::database::row & edit_row() { return m_rowEdit; }

      void set_dataset_state(e_dataset new_state) {m_edataset = new_state;};

      e_dataset get_dataset_state() {return m_edataset; }

      virtual void set_sql(e_sql esql, const char * sql);

      virtual void clear_sql(e_sql esql);

      virtual string get_sql(e_sql esql);

      virtual __pointer(row_array) query_rows(const char *query);
      virtual __pointer(var_array) query_items(const char *query);
      virtual var query_item(const char *query);

      virtual bool query_rows(__pointer(row_array) & rows, const char *query);
      virtual bool query_items(__pointer(var_array) & items, const char *query);
      virtual bool query_item(var & item, const char *query);

   };


} // namespace sqlite




