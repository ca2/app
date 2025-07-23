
#pragma once

namespace simpledb
{

   class base;

   class CLASS_DECL_AURA table :
      virtual public ::object
   {
   public:


      base *                        m_pdatabase;
      file_pointer                 m_spfileMeta;
      ::xml::document               m_xmldocumentMeta;
      file_pointer                 m_spfileFixed;
      memory             m_memoryFixed;
      string                        m_strName;
      database::field_definition    m_fielddefinition;


      table(base * pdatabase, const ::string & pszName);

      base * get_database();

   };


} // namespace simpledb
