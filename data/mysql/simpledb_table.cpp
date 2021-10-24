#include "framework.h"


namespace simpledb
{


   table::table(base * pdatabase, const ::string & pszName) :
      matter(pdatabase->get_application()),
      m_spfileMeta(pdatabase->get_application()),
      m_spfileFixed(pdatabase->get_application()),
      m_xmldocumentMeta(pdatabase->get_application())
   {


      m_strName = pszName;
      m_pdatabase = pdatabase;

      

      string strMetaPath;

      strMetaPath = pcontext->m_papexcontext->dir().install("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "meta.xml");

      if(!m_spfileMeta->open(strMetaPath, ::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_share_exclusive))
         __throw(::exception("integer_exception" + __string($1)));

      ::file::input_stream is(m_spfileMeta);

      if(!m_xmldocumentMeta.load(is))
         __throw(::exception("integer_exception" + __string($1)));

      __pointer(::xml::node) pfields = m_xmldocumentMeta.get_root()->get_child("fields");

      for(i32 i = 0; i < pfields->get_children_count(); i++)
      {
         __pointer(::xml::node) pfield = pfields->child_at(i);
         if(pfield->get_name() != "field")
            continue;
         database::field_definition_item item;
         item = *pfield;
         m_fielddefinition.add(item);
      }

      string strFixedPath = m_xmldocumentMeta.get_root()->attr("fixed_path");
      if(strFixedPath.is_empty())
         strFixedPath = strMetaPath = pcontext->m_papexcontext->dir().install("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "fixed.txt");

      if(!m_spfileFixed->open(strMetaPath, ::file::e_open_create | ::file::e_open_no_truncate | ::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_share_exclusive |
         ::file::e_open_defer_create_directory))
         __throw(::exception("integer_exception" + __string($1)));

   }


} // namespace simpledb


