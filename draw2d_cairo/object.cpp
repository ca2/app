#include "framework.h"


namespace draw2d_cairo
{



   object::object()
   {
      //set_handle(nullptr);
   }

   object::~object()
   {
      //delete_object();
   }

   i32 object::get_object(i32 nCount, void * lpObject) const
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
   ::u32 object::GetObjectType() const
   {
      //return (::u32)::GetObjectType(get_handle());
      return 0;
   }
   bool object::operator==(const object& obj) const
   {
      //return ((HGDIOBJ) obj.get_os_data()) == get_handle();
      return FALSE;
   }
   bool object::operator!=(const object& obj) const
   {
      //return ((HGDIOBJ) obj.get_os_data()) != get_handle();
      return TRUE;
   }


#ifdef WINDOWS_DESKTOP


   object * graphics_object_allocator(::object * pobject, HANDLE h)
   {
      /*switch(::GetObjectType(h))
      {
      case OBJ_BITMAP:
         return dynamic_cast < object * > (new bitmap(pobject));
      case OBJ_REGION:
         return dynamic_cast < object * > (new region(pobject));
      case OBJ_PEN:
         return dynamic_cast < object * > (new pen(pobject));
      case OBJ_BRUSH:
         return dynamic_cast < object * > (new brush(pobject));
      case OBJ_PAL:
         return dynamic_cast < object * > (new palette(pobject));
      case OBJ_FONT:
         return dynamic_cast < object * > (new font(pobject));
      }
      return new object();*/
      return nullptr;
   }


#endif


   void object::dump(dump_context & dumpcontext) const
   {

      ::context_object::dump(dumpcontext);

      dumpcontext << "get_handle() = " << 0;
      dumpcontext << "\n";

   }


   void object::assert_valid() const
   {

      ::context_object::assert_valid();

   }


//   bool object::delete_object()
//   {
//      //if (get_os_data() == nullptr)
//        // return FALSE;
//      //return ::DeleteObject(Detach());
//      return FALSE;
//   }
//
//   /////////////////////////////////////////////////////////////////////////////
//   // object
//
//
//   void object::dump(dump_context & dumpcontext) const
//   {
//      ::object::dump(dumpcontext);
//
//   //      dumpcontext << "get_handle() = " << get_handle();
//   //    dumpcontext << "\n";
//   }
//
//   void object::assert_valid() const
//   {
//      ::object::assert_valid();
//      //ASSERT(get_handle() == nullptr ||
//        // (afxData.bWin95 || ::GetObjectType(get_handle()) != 0));
//   }
//
//
//   void * object::detach_os_data()
//   {
//
//      return Detach();
//
//   }


   void * object::get_os_data() const
   {

      return get_os_data();

   }



} // namespace draw2d_cairo





