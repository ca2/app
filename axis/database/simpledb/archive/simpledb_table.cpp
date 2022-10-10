#include "framework.h"


namespace simpledb
{


   table::table(database * pdatabase, const ::string & pszName) :
      object(pdatabase->get_app()),
      m_spfileMeta(pdatabase->get_app()),
      m_spfileFixed(pdatabase->get_app()),
      m_xmldocumentMeta(pdatabase->get_app())
   {


      m_strName = pszName;
      m_pdatabase = pdatabase;



      string strMetaPath;

      strMetaPath = pcontext->m_papexcontext->dir().install() / "database" / m_pdatabase->getDatabase() / m_strName/ "meta.xml";

      if(!m_spfileMeta->open(strMetaPath, ::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_share_exclusive))
         throw ::exception(::exception("integer_exception 1"));

      reader is(m_spfileMeta);

      if(!m_xmldocumentMeta.load(is))
         throw ::exception(::exception("integer_exception 1"));

      ::pointer<::xml::node>pfields = m_xmldocumentMeta.get_root()->get_child("fields");

      for(i32 i = 0; i < pfields->get_children_count(); i++)
      {
         ::pointer<::xml::node>pfield = pfields->child_at(i);
         if(pfield->get_name() != "field")
            continue;
         ::database::field_definition_item item;
         item = *pfield;
         m_fielddefinition.add(item);
      }

      string strFixedPath = m_xmldocumentMeta.get_root()->attr("fixed_path");
      if(strFixedPath.is_empty())
         strFixedPath = strMetaPath = pcontext->m_papexcontext->dir().install() / "database" / m_pdatabase->getDatabase() /  m_strName/"fixed.txt";

      if(!m_spfileFixed->open(strMetaPath, ::file::e_open_create | ::file::e_open_no_truncate | ::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_share_exclusive |
                              ::file::e_open_defer_create_directory))
         throw ::exception(::exception("integer_exception 1"));

   }


} // namespace simpledb


