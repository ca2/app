#pragma once


namespace database
{


   class CLASS_DECL_AXIS exception :
      public ::exception
   {
   public:


      exception();
      exception(const char * pszFormat, ...);


   };


   enum e_dataset
   {

      dataset_none,
      dataset_select,
      dataset_insert,
      dataset_edit,
      dataset_update,
      dataset_delete,

   };


   enum e_connection
   {

      connection_none,
      connection_ok

   };


   enum e_sql
   {

      sql_none,
      sql_execute,
      sql_select,
      sql_update,
      sql_insert,
      sql_delete,

   };

   enum e_data_type
   {

      data_type_string,
      data_type_boolean,
      data_type_char,
      data_type_wchar,
      data_type_wide_string,
      data_type_short,
      data_type_ushort,
      data_type_long,
      data_type_i64,
      data_type_ulong,
      data_type_float,
      data_type_double,
      data_type_long_double,
      data_type_object

   };


   class CLASS_DECL_AXIS field :
      virtual public ::object
   {
   public:


      index             m_iIndex;
      e_data_type       m_edatatype;
      string            m_strName;
      string            m_strDisplayMame;
      string            m_strFieldTable;
      bool              m_bReadOnly;
      strsize           m_iLength;
      u64               m_ulFlag;


      field();

      virtual ::stream & write(::stream & stream) const override;
virtual ::stream & read(::stream & stream) override;

   };


   using row = payload_array;

   using row_array = __pointer_array(row);

   using field_array = __pointer_array(field);


   class CLASS_DECL_AXIS result_set :
      virtual public ::object
   {
   public:


      
      __pointer(field_array)     m_pfielda;
      __pointer(row_array)       m_prowa;

      ::count                    m_iMaxRowCount;
      ::count                    m_iMaxColumnCount;


      result_set();


      virtual ::stream & write(::stream & stream) const override;
virtual ::stream & read(::stream & stream) override;


   };


   class CLASS_DECL_AXIS parameter_list
   {
   public:


      string_array        m_stra;
      row            m_row;


      ::payload & get_value(index i);
      const char * get_key(index i);
      ::count get_size();
      bool is_empty();

      parameter_list & operator = (const parameter_list & paramlist);


   };


} // namespace database



