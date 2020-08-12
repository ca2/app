#include "framework.h"


namespace draw2d_xlib
{



   object::object()
   {
      //set_handle(nullptr);
   }

   object::~object()
   {
      //delete_object();
   }

   i32 object::get_object(i32 nCount, LPVOID lpObject) const
   {
      //return ::GetObject(get_handle(), nCount, lpObject);
      return 0;
   }

   bool object::CreateStockObject(i32 nIndex)
   {
      //return (set_handle(::GetStockObject(nIndex))) != nullptr;
      return 0;
   }
   bool object::UnrealizeObject()
   {
      //ASSERT(get_handle() != nullptr); return ::UnrealizeObject(get_handle());
      return 0;
   }
   UINT object::GetObjectType() const
   {
      //return (UINT)::GetObjectType(get_handle());
      return 0;
   }

   object * graphics_object_allocator(::object * pobject, HANDLE h)
   {
      return nullptr;
   }


   bool object::delete_object()
   {
      return FALSE;
   }



   void object::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

   }

   void object::assert_valid() const
   {
      ::object::assert_valid();
   }



   void * object::get_os_data() const
   {

      return nullptr;

   }


} // namespace draw2d_xlib






