// From definition.h by camilo on 2022-09-06 17:13 <3ThomasBorregaardSorensen!!
#pragma once


namespace database
{


   enum enum_dataset
   {

      e_dataset_none,
      e_dataset_select,
      e_dataset_insert,
      e_dataset_edit,
      e_dataset_update,
      e_dataset_delete,

   };


   enum enum_connection
   {

      e_connection_none,
      e_connection_ok

   };


   enum enum_sql
   {

      e_sql_none,
      e_sql_execute,
      e_sql_select,
      e_sql_update,
      e_sql_insert,
      e_sql_delete,

   };

   enum enum_data_type
   {

      e_data_type_string,
      e_data_type_boolean,
      e_data_type_char,
      e_data_type_wchar,
      e_data_type_wide_string,
      e_data_type_short,
      e_data_type_ushort,
      e_data_type_long,
      e_data_type_i64,
      e_data_type_ulong,
      e_data_type_float,
      e_data_type_double,
      e_data_type_long_double,
      e_data_type_object

   };


} // namespace database



