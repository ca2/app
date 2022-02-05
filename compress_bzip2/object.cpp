#include "framework.h"

namespace draw2d_gdiplus
{

   object::object()
   {
      //set_handle(nullptr);
   }

   object::~object()
   {
      //delete_object();
   }

   i32 object::get_object(i32 nCount, LPVOID pObject) const

   {
      //return ::GetObject(get_handle(), nCount, pObject);

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
   bool object::operator==(const ::draw2d::object& obj) const
   {
      //return ((HGDIOBJ) obj.get_os_data()) == get_handle();
      return false;
   }
   bool object::operator!=(const ::draw2d::object& obj) const
   {
      //return ((HGDIOBJ) obj.get_os_data()) != get_handle();
      return true;
   }


   bool object::delete_object()
   {
      //if (get_os_data() == nullptr)
      // return false;
      //return ::DeleteObject(detach());
      return false;
   }

#ifdef DEBUG

   void object::dump(dump_context & dumpcontext) const
   {

      ::object::dump(dumpcontext);

   }


   void object::assert_ok() const
   {
      ::object::assert_ok();
      //ASSERT(get_handle() == nullptr ||
      // (afxData.bWin95 || ::GetObjectType(get_handle()) != 0));
   }

#endif

   /*void * object::detach_os_data()
   {
      return detach();
   }*/

   /*void * object::get_os_data() const
   {
   return get_os_data();
   }*/


   void * object::get_os_data() const
   {

      return nullptr;

   }


} // namespace draw2d_gdiplus



