#include "framework.h"



namespace simpledb
{


   file_set::file_set(::particle * pparticle) :
      ::object(pparticle),
      ::file::set_pointer(e_create)
   {

   }


   file_set::~file_set()
   {

   }


   void file_set::data_on_after_change(::message::message * pmessage)
   {

      ::pointer<::database::change_event>pchange(pmessage);

      if(pchange->m_key.id() == m_dataid)
      {

         refresh();

      }

   }


   bool file_set::refresh()
   {

      m_p->clear_search();

      string_array stra;

      bool_array baRecursive;

      if(!datastream()->get(::base::system::idEmpty, stra))
         return false;

      datastream()->get("recursive") >> baRecursive;

      // add_search calls Ex2FileSet refresh internally
      m_p->add_search(stra, baRecursive);

      return true;

   }


   bool file_set::add_search(const ::scoped_string & scopedstrSearchDirectory)
   {

      string_array stra;

      datastream()->get(::base::system::idEmpty, stra);

      if(stra.add_unique(scopedstrSearchDirectory) < 0)
         return true;

      if(!datastream()->set(::base::system::idEmpty, stra))
         return false;

      if(!refresh())
         return false;

      return true;

   }


   bool file_set::clear_search()
   {

      string_array stra;

      if(!datastream()->set(::base::system::idEmpty, stra))
         return false;

      if(!refresh())
         return false;

      return true;

   }


} // namespace simpledb



