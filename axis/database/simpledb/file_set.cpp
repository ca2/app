#include "framework.h"
#include "_simpledb.h"




namespace simpledb
{


   file_set::file_set()
   {

      m_listing.m_bDir      = false;
      m_listing.m_bFile     = true;

   }


   file_set::~file_set()
   {

   }


   void file_set::data_on_after_change(::message::message * pmessage)
   {

      SCAST_PTR(::database::change_event, pchange, pmessage);

      if(pchange->m_datakey == m_datakey)
      {

         refresh();

      }

   }


   void file_set::refresh()
   {

      ::file::set::clear_search();

      __pointer(::file::patha) ppatha;

      __construct_new(ppatha);

      __pointer(bool_array) pbaRecursive;

      __construct_new(pbaRecursive);

      if (!data_get(::id(), ppatha))
      {

         return;

      }

      data_get("recursive", pbaRecursive);

      for (index i = pbaRecursive->get_size(); i < ppatha->get_size(); i++)
      {

         pbaRecursive->add(false);

      }

      // add_search calls Ex2FileSet refresh internally
      ::file::set::add_search(*ppatha, *pbaRecursive);

      ::file::set::refresh();

   }


   void file_set::add_search(const ::file::path & pathSearchFolder, bool bRecursive)
   {

      data_get(::id(), m_ppathaSearch);

      data_get("recursive", m_pbaRecursive);

      index i = -1;

      if(!m_ppathaSearch || (i = m_ppathaSearch->find_first_ci(pathSearchFolder)) < 0)
      {

         __defer_construct_new(m_ppathaSearch);

         __defer_construct_new(m_pbaRecursive);

         m_ppathaSearch->add(pathSearchFolder);

         m_pbaRecursive->add(bRecursive);

         data_set(::id(), m_ppathaSearch);

         data_set("recursive", m_pbaRecursive);

      }
      else
      {

         m_pbaRecursive->set_at_grow(i,bRecursive);

         data_set("recursive", m_pbaRecursive);

      }

   }


   void file_set::clear_search()
   {

      ::file::set::clear_search();

      data_set(::id(), ::payload(e_type_new));

      data_set("recursive", ::payload(e_type_new));

   }


} // namespace simpledb



