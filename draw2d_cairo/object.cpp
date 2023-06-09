#include "framework.h"
#include "object.h"


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

//   bool object::CreateStockObject(i32 nIndex)
//   {
//      //return (set_handle(::GetStockObject(nIndex))) != nullptr;
//      return 0;
//   }
//   bool object::UnrealizeObject()
//   {
//      //ASSERT(get_handle() != nullptr); return ::UnrealizeObject(get_handle());
//      return 0;
//   }
//   ::u32 object::GetObjectType() const
//   {
//      //return (::u32)::GetObjectType(get_handle());
//      return 0;
//   }
//   bool object::operator==(const object& obj) const
//   {
//      //return ((HGDIOBJ) obj.get_os_data()) == get_handle();
//      return false;
//   }
//   bool object::operator!=(const object& obj) const
//   {
//      //return ((HGDIOBJ) obj.get_os_data()) != get_handle();
//      return true;
//   }


#ifdef WINDOWS_DESKTOP


   object * graphics_object_allocator(::particle * pparticle, HANDLE h)
   {
      /*switch(::GetObjectType(h))
      {
      case OBJ_BITMAP:
         return dynamic_cast < object * > (memory_new bitmap(pparticle));
      case OBJ_REGION:
         return dynamic_cast < object * > (memory_new region(pparticle));
      case OBJ_PEN:
         return dynamic_cast < object * > (memory_new pen(pparticle));
      case OBJ_BRUSH:
         return dynamic_cast < object * > (memory_new brush(pparticle));
      case OBJ_PAL:
         return dynamic_cast < object * > (memory_new palette(pparticle));
      case OBJ_FONT:
         return dynamic_cast < object * > (memory_new font(pparticle));
      }
      return memory_new object();*/
      return nullptr;
   }


#endif


//   void object::dump(dump_context & dumpcontext) const
//   {
//
//      ::draw2d::object::dump(dumpcontext);
//
//      /*dumpcontext << "get_handle() = " << 0;
//      dumpcontext << "\n";*/
//
//   }
//
//
//   void object::assert_ok() const
//   {
//
//      ::draw2d::object::assert_ok();
//
//   }


//   bool object::delete_object()
//   {
//      //if (get_os_data() == nullptr)
//        // return false;
//      //return ::DeleteObject(Detach());
//      return false;
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
//   void object::assert_ok() const
//   {
//      ::object::assert_ok();
//      //ASSERT(get_handle() == nullptr ||
//        // (::windows_definition::Data.bWin95 || ::GetObjectType(get_handle()) != 0));
//   }
//
//
//   void * object::detach_os_data()
//   {
//
//      return Detach();
//
//   }


   //void * object::get_os_data() const
   //{

   //   return ::draw2d::object::get_os_data();

   //}



} // namespace draw2d_cairo





