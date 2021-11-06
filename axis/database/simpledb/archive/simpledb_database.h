#pragma once

namespace simpledb
{

   class table;
   class dataset;

   class CLASS_DECL_CORE database :
      public ::database::database
   {
   public:

      file_pointer                 m_spfileMeta;
      ::xml::document               m_xmldocumentMeta;
      string_map < table *, table * > m_mapTable;
      i32                           m_iErrorCode;


      database(::object * pobject);


      virtual i32 connect();

      virtual class ::simpledb::dataset * create_dataset();

      table * get_table(const ::string & pszName);
      table * create_table(const ::string & pszName);


      // class ::database::database
      virtual class ::database::dataset * create_dataset();
      virtual i32 setErr(i32 err_code);
      virtual long nextid(const ::string & sname);



   };


} // namespace simpledb
