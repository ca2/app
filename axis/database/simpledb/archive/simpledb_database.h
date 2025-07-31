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
      int                           m_iErrorCode;


      database(::particle * pparticle);


      virtual int connect();

      virtual class ::simpledb::dataset * create_dataset();

      table * get_table(const ::scoped_string & scopedstrName);
      table * create_table(const ::scoped_string & scopedstrName);


      // class ::database::database
      virtual class ::database::dataset * create_dataset();
      virtual int setErr(int err_code);
      virtual long nextid(const ::string & sname);



   };


} // namespace simpledb
