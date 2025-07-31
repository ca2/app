#pragma once

namespace simpledb
{

   class table;
   class set;

   class CLASS_DECL_AURA base :
      public ::database::base
   {
   public:

      file_pointer                 m_spfileMeta;
      ::xml::document               m_xmldocumentMeta;
      string_map < table *, table * > m_mapTable;
      int                           m_iErrorCode;


      base(::particle * pparticle);


      virtual int connect();


      virtual class ::simpledb::set * create_dataset() const;

      table * get_table(const ::scoped_string & scopedstrName);
      table * create_table(const ::scoped_string & scopedstrName);


      // class ::database::base
      virtual class ::database::set * create_dataset() const;
      virtual int setErr(int err_code);
      virtual long nextid(const ::string & sname);



   };


} // namespace simpledb
