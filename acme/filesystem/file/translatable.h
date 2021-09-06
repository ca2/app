#pragma once


namespace file
{


   class CLASS_DECL_ACME translatable :
      virtual public referenceable
   {
   public:


      virtual ::index translate(::count c, enum_seek eseek) = 0;

      ::index operator++()
      {

         return translate(1, ::e_seek_current);

      }

      ::index operator--()
      {

         return translate(-1, ::e_seek_current);

      }


      ::index operator+=(::count c)
      {

         return translate(c, ::e_seek_current);

      }


      ::index operator-=(::count c)
      {

         return translate(-c, ::e_seek_current);

      }


      explicit operator ::index() const
      {

         return ((translatable *)this)->translate(0, ::e_seek_current);

      }


   };



} // namespace file



