#include "framework.h"
#include "edit.h"
#include "document.h"
////#include "acme/exception/exception.h"


namespace xml
{


   edit_item::edit_item() :
      m_eaction(action_none)
   {
   }


   void edit_item::set_name(const ::pointer<::xml::node>pnode)
   {

      m_eaction      = ::xml::action_set_name;
      pnode->get_indexed_path(m_iaPath);
      m_strName      = pnode->get_name();

   }

   void edit_item::set_value(const ::pointer<::xml::node>pnode)
   {

      m_eaction      = ::xml::action_set_value;
      pnode->get_indexed_path(m_iaPath);
      m_strValue     = pnode->get_value();

   }


   void edit_item::set_attribute(const ::pointer<::xml::node>pnode, const property * pproperty)
   {

      m_eaction      = ::xml::action_set_attribute;
      pnode->get_indexed_path(m_iaPath);
      m_strName      = pproperty->name();
      m_strValue     = *pproperty;

   }


   //void edit_item::add_attr(const ::pointer<::xml::node>pnode, const attr * pattr)
   //{

   //   m_eaction      = ::xml::action_add_attr;
   //   pnode->get_indexed_path(m_iaPath);
   //   m_strName      = pattr->name();
   //   m_strValue     = pattr->get_value();

   //}


   //stream & edit_item::write(::stream & stream) const
   //{

   //   stream << (i32 &) m_eaction;
   //   stream << m_iaPath;
   //   stream << m_strName;
   //   stream << m_strValue;

   //   return stream;

   //}


   //stream & edit_item::read(::stream & stream)
   //{

   //   stream >> (i32 &)m_eaction;
   //   stream >> m_iaPath;
   //   stream >> m_strName;
   //   stream >> m_strValue;

   //   return stream;

   //}


   edit::edit()
   {

      m_iEdit = -1;

   }


   edit::~edit()
   {

   }


   void edit::set_name(const ::pointer<::xml::node>pnode)
   {

      if (pnode->get_document() != m_pdocument)
      {

         throw ::exception("unmatched xml document");

      }

      edit_item * pitem = m_edititema.add_new(this);

      pitem->set_name(pnode);

   }

   void edit::set_value(const ::pointer<::xml::node>pnode)
   {

      if (pnode->get_document() != m_pdocument)
      {

         throw ::exception("unmatched xml document");

      }

      edit_item * pitem = m_edititema.add_new(this);

      pitem->set_value(pnode);

   }


   void edit::set_attribute(const ::pointer<::xml::node>pnode, const property * pproperty)
   {

      if (pnode->get_document() != m_pdocument)
      {

         throw ::exception(error_parsing, "unmatched xml document");

      }

      edit_item * pitem = m_edititema.add_new(this);

      pitem->set_attribute(pnode, pproperty);

   }


   //void edit::add_attr(const ::pointer<::xml::node>pnode, const ::xml::attr * pattr)
   //{

   //   if(pnode->get_document() != m_spdata.m_p)
   //      throw ::exception(::exception("unmatched xml document"));

   //   edit_item * pitem = add_new(this);

   //   pitem->add_attr(pnode, pattr);

   //}



} // namespace xml



