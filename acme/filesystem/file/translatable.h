#pragma once


#include "acme/primitive/primitive/element.h"


namespace file
{


   class CLASS_DECL_ACME translatable :
      virtual public ::particle
   {
   public:


      virtual filesize translate(filesize offset, enum_seek eseek) = 0;


      filesize operator++()
      {

         return translate(1, ::e_seek_current);

      }


      filesize operator--()
      {

         return translate(-1, ::e_seek_current);

      }


      filesize operator+=(filesize offset)
      {

         return translate(offset, ::e_seek_current);

      }


      filesize operator-=(filesize offset)
      {

         return translate(-offset, ::e_seek_current);

      }


      explicit operator filesize() const
      {

         return ((translatable *)this)->translate(0, ::e_seek_current);

      }


   };


} // namespace file



