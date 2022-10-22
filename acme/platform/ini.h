// From property_set.h by camilo on 2022-10-22 20:15 <3ThomasBorregaardSorensen!!
#pragma once


// <3tbs!! - Talking... ~ and then end up creating a Handler that handles...
namespace handle
{
   //
   //
   class CLASS_DECL_ACME ini :
      public ::property_set
   {
   public:


      ini() {}
      ini(const ::string & str);
      ini(::file::file * pfile);
      ini(const ::property_set & set) : ::property_set(set) {}
      ini(::property_set && set) : ::property_set(::move(set)) {}
      ini(const ini & ini) : ::property_set(ini) {}
      ini(ini && ini) : property_set(::move(ini)) {}


      ini & operator =(const ini & ini) { if (this != &ini) ::property_set::operator=(ini); return *this; }
      ini & operator =(ini && ini) { if (this != &ini) ::property_set::operator=(::move(ini)); return *this; }


   };


   //class CLASS_DECL_ACME localini :
   //   public ini
   //{
   //public:

   //   localini(::matter * pobject);

   //};


} // namespace handle


inline ::pointer<::handle::ini>operator ""_pini(const char * psz, size_t s)
{

   return __new(::handle::ini(string(psz, s)));

}
