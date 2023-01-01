#pragma once


#include "acme/primitive/primitive/particle.h"
#include "acme/constant/filesystem.h"


namespace file
{


   class CLASS_DECL_ACME translatable :
      virtual public ::particle
   {
   public:


      virtual void translate(filesize offset, enum_seek eseek) = 0;
      virtual ::filesize get_position() const = 0;


      void operator++()
      {

         return translate(1, ::e_seek_current);

      }


      void operator--()
      {

         return translate(-1, ::e_seek_current);

      }


      void operator+=(filesize offset)
      {

         return translate(offset, ::e_seek_current);

      }


      void operator-=(filesize offset)
      {

         return translate(-offset, ::e_seek_current);

      }


      explicit operator filesize() const
      {

         return this->get_position();

      }


   };


} // namespace file



