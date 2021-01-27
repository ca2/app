#pragma once

//#ifdef _WIN64
//template <>
//inline uptr uptr_hash(iptr key)
//{
//   // default identity hash - works for most primitive values
//   return (u32)(((uptr)key) >> 32);
//}
//#else
//template <>
//inline uptr uptr_hash(iptr key)
//{
//   // default identity hash - works for most primitive values
//   return (u32)(((uptr)key) >> 16);
//}
//#endif

namespace user
{


   class primitive;


   class CLASS_DECL_AURA window_map :
      virtual public ::object
   {
   public:


      map < oswindow, ::user::primitive * > m_map;


      window_map();
      virtual ~window_map();


      ::user::primitive * get(oswindow oswindow);


      void set(oswindow oswindow, const ::user::primitive * pinterface);

   };


} // namespace user


