#include "framework.h"


namespace simpledb
{


   table::table(base * pdatabase, const char * pszName) :
      matter(pdatabase->get_context_application()),
      m_spfileMeta(pdatabase->get_context_application()),
      m_spfileFixed(pdatabase->get_context_application()),
      m_xmldocumentMeta(pdatabase->get_context_application())
   {


      m_strName = pszName;
      m_pdatabase = pdatabase;

      

      string strMetaPath;

      strMetaPath = Context.dir().install("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "meta.xml");

      if(!m_spfileMeta->open(strMetaPath, ::file::type_binary | ::file::mode_read_write | ::file::share_exclusive))
         __throw(::exception::exception("integer_exception" + __str($1)));

      ::file::input_stream is(m_spfileMeta);

      if(!m_xmldocumentMeta.load(is))
         __throw(::exception::exception("integer_exception" + __str($1)));

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
         strFixedPath = strMetaPath = Context.dir().install("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "fixed.txt");

      if(!m_spfileFixed->open(strMetaPath, ::file::mode_create | ::file::mode_no_truncate | ::file::type_binary | ::file::mode_read_write | ::file::share_exclusive |
         ::file::defer_create_directory))
         __throw(::exception::exception("integer_exception" + __str($1)));

   }


} // namespace simpledb


