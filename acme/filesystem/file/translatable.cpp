// Created by camilo on 2023-03-15 15:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "translatable.h"
#include "acme/exception/interface_only.h"


namespace file
{


   void translatable::translate(filesize offset, enum_seek eseek)
   {

      throw ::interface_only();

   }


   ::filesize translatable::get_position() const
   {

      throw ::interface_only();

      return {};

   }


   //virtual bool is_seekable();

   //inline translatable & position() { return *this; }
   ////virtual filesize get_position() const override;
   //virtual void set_position(filesize position);
   //virtual void increment_position(filesize offset = 1);
   //virtual void decrement_position(filesize offset = 1);
   //virtual void seek_to_begin();
   //virtual void seek_to_end();
   //virtual void seek_from_end(filesize offset);


   bool translatable::is_seekable()
   {

      return true;

   }




   //filesize translatable::get_position() const
   //{

   //   throw interface_only();

   //   return 0;

   //   //return ((file *) this)->translate(0, ::e_seek_current);

   //}


   void translatable::set_position(filesize position)
   {

      ((translatable *)this)->translate(position, ::e_seek_set);

   }


   void translatable::increment_position(filesize offset)
   {

      translate(offset, ::e_seek_current);

   }


   void translatable::decrement_position(filesize offset)
   {

      return translate(-offset, ::e_seek_current);

   }


   void translatable::seek_from_end(filesize offset)
   {

      return translate(offset, ::e_seek_from_end);

   }


   void translatable::seek_to_begin()
   {

      return set_position(0);

   }


   void translatable::seek_to_end()
   {

      return translate(0, e_seek_from_end);

   }


} // namespace file



