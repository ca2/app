#include "framework.h"


namespace simpledb
{


   file_set::file_set(::layered * pobjectContext) :
      ::object(pobject),
      ::file::set_pointer(e_create)
   {

   }


   file_set::~file_set()
   {

   }


   void file_set::data_on_after_change(::message::message * pmessage)
   {

      SCAST_PTR(::database::change_event, pchange, pmessage);

      if(pchange->m_key.m_id == m_dataid)
      {

         refresh();

      }

   }


   bool file_set::refresh()
   {

      m_p->clear_search();

      string_array stra;

      bool_array baRecursive;

      if(!data_get(::base::system::idEmpty, stra))
         return false;

      data_get("recursive") >> baRecursive;

      // add_search calls Ex2FileSet refresh internally
      m_p->add_search(stra, baRecursive);

      return true;

   }


   bool file_set::add_search(const char * pszSearchDirectory)
   {

      string_array stra;

      data_get(::base::system::idEmpty, stra);

      if(stra.add_unique(pszSearchDirectory) < 0)
         return true;

      if(!data_set(::base::system::idEmpty, stra))
         return false;

      if(!refresh())
         return false;

      return true;

   }


   bool file_set::clear_search()
   {

      string_array stra;

      if(!data_set(::base::system::idEmpty, stra))
         return false;

      if(!refresh())
         return false;

      return true;

   }


} // namespace simpledb



