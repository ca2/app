#pragma once


#include "acme/primitive/primitive/particle.h"
#include "acme/constant/filesystem.h"


namespace file
{


   class CLASS_DECL_ACME translatable :
      virtual public ::particle
   {
   public:


      // derived class must implement these
      virtual void translate(filesize offset, enum_seek eseek);
      virtual ::filesize get_position() const;


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


      virtual bool is_seekable();

      inline translatable & position() { return *this; }
      //virtual filesize get_position() const override;
      virtual void set_position(filesize position);
      virtual void increment_position(filesize offset = 1);
      virtual void decrement_position(filesize offset = 1);
      virtual void seek_to_begin();
      virtual void seek_to_end();
      virtual void seek_from_end(filesize offset);



   };


} // namespace file



