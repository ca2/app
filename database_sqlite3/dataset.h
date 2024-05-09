#pragma once

//
//namespace sqlite
//{
//
//
//   class database;
//
//
//   class CLASS_DECL_AXIS dataset :
//      public ::database::dataset
//   {
//   public:
//
//
//      ::database::result_set  m_resultset;
//      ::database::result_set  m_resultsetExecute;
//
//
//      dataset(database * pdatabase);
//      ~dataset();
//
//
//      //virtual void query_items(string_array & stra, const ::string & pszSql);
//
//      //virtual void * get_handle() override;
//
//
//      virtual void make_query(string_array &_sql);
//      virtual void make_insert() override;
//      virtual void make_edit() override;
//      virtual void make_deletion() override;
//
//
//      virtual void fill_fields() override;
//      //virtual bool erase_row();
//
//
//      virtual void open() override;
//      virtual void open(const ::string & sql) override;
//      virtual bool exec() override;
//      virtual bool exec(const ::string & sql) override;
//      virtual bool query(const ::string &query) override;
//      virtual void close() override;
//      virtual void cancel() override;
//      virtual ::collection::count num_rows() override;
//
//      //virtual bool bof() override;
//      //virtual bool eof() override;
//      //virtual void first() override;
//      //virtual void last() override;
//      //virtual void prev() override;
//      //virtual void next() override;
//
//      //virtual ::collection::index find_first(const ::string & fieldname, ::payload & value);
//      //virtual bool seek(index pos=0) override;
//
//      //virtual bool SetFieldValue(const ::string &f_name, const ::payload &value) override;
//      //virtual bool SetFieldValue(::collection::index iFieldIndex, const ::payload &value);
//
//      //virtual ::payload field_value_at(::collection::index iFieldIndex) override;
//      //virtual ::payload FieldValueAt(::collection::index iFieldIndex);
//      //virtual i32 GetFieldIndex(const ::string &f_name);
//
//
//   };
//
//
//} // namespace sqlite
//
//
//
