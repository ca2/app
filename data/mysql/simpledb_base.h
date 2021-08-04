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
      i32                           m_iErrorCode;


      base(::object * pobject);


      virtual i32 connect();


      virtual class ::simpledb::set * create_dataset() const;

      table * get_table(const ::string & pszName);
      table * create_table(const ::string & pszName);


      // class ::database::base
      virtual class ::database::set * create_dataset() const;
      virtual i32 setErr(i32 err_code);
      virtual long nextid(const ::string & sname);



   };


} // namespace simpledb
