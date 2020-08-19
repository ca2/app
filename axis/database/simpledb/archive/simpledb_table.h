
#pragma once

namespace simpledb
{

   class database;

   class CLASS_DECL_CORE table :
      virtual public ::object
   {
   public:


      database *                        m_pdatabase;
      file_pointer                 m_spfileMeta;
      ::xml::document               m_xmldocumentMeta;
      file_pointer                 m_spfileFixed;
      memory             m_memoryFixed;
      string                        m_strName;
      ::database::field_definition    m_fielddefinition;


      table(database * pdatabase, const char * pszName);

      database * get_database();

   };


} // namespace simpledb
