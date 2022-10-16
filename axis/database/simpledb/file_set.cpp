#include "framework.h"
#include "file_set.h"
#include "acme/primitive/collection/_array_binary_stream.h"
#include "apex/database/_binary_stream.h"


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

      ::pointer<::database::change_event>pchange(pmessage);

      if(pchange->m_datakey == m_datakey)
      {

         refresh();

      }

   }


   void file_set::refresh()
   {

      ::file::set::clear_search();

      ::pointer<::file::path_array>ppatha;

      __construct_new(ppatha);

      ::pointer<bool_array>pbaRecursive;

      __construct_new(pbaRecursive);

      if (!datastream()->get(::atom(), ppatha))
      {

         return;

      }

      datastream()->get("recursive", pbaRecursive);

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

      datastream()->get(::atom(), m_ppathaSearch);

      datastream()->get("recursive", m_pbaRecursive);

      index i = -1;

      if(!m_ppathaSearch || (i = m_ppathaSearch->find_first_ci(pathSearchFolder)) < 0)
      {

         __defer_construct_new(m_ppathaSearch);

         __defer_construct_new(m_pbaRecursive);

         m_ppathaSearch->add(pathSearchFolder);

         m_pbaRecursive->add(bRecursive);

         datastream()->set(::atom(), m_ppathaSearch);

         datastream()->set("recursive", m_pbaRecursive);

      }
      else
      {

         m_pbaRecursive->set_at_grow(i,bRecursive);

         datastream()->set("recursive", m_pbaRecursive);

      }

   }


   void file_set::clear_search()
   {

      ::file::set::clear_search();

      datastream()->set(::atom(), ::payload(e_type_new));

      datastream()->set("recursive", ::payload(e_type_new));

   }


} // namespace simpledb



