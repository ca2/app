#pragma once


namespace acme
{

   inline ::id id(const class var& var)
   {
      return ::id((const char*)(class var&)var);
   }

   inline ::id id(const property& prop)
   {
      return ::id((const string&)(property&)prop);
   }


   inline ::id id(const ::std::type_info& info)
   {
#ifdef WINDOWS
      return get_id_space()(info.name());
#else
      return get_id_space()(info.name());
#endif
   }

   inline ::id id(const char* psz)
   {
      return get_id_space()(psz);
   }

   inline ::id id(const string& str)
   {
      return get_id_space()(str);
   }

   inline ::id id(i64 i)
   {
      return get_id_space()(i);
   }

   inline id_space& id()
   {
      return get_id_space();
   }


} //namespace acme
