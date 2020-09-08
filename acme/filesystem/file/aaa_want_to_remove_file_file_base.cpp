#include "framework.h"


namespace file
{


   file::file()
   {
   }



   file::~file()
   {
   }

   
   void * file::get_internal_data()
   {

      return nullptr;

   }


   const void * file::get_internal_data() const
   {

      return ((file *) this)->get_internal_data();

   }

   memsize file::get_internal_data_size() const
   {

      return 0;

   }


   bool file::set_internal_data_size(memsize c)
   {

      return false;
      
   }

   bool file::increase_internal_data_size(memsize c)
   {

      return set_internal_data_size(c + get_internal_data_size());
      
   }


} // namespace file



