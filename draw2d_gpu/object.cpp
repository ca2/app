#include "framework.h"
//#include "_opengl.h"
#include "object.h"


namespace draw2d_gpu
{

   object::object()
   {
      //set_handle(nullptr); 
   }
   
   object::~object()
   { 
      //delete_object(); 
   }
   
   
   int object::get_object(int nCount, void * lpObject) const
   { 

      //return ::GetObject(get_handle(), nCount, lpObject); 
      return 0;

   }


   bool object::CreateStockObject(int nIndex)
   {
      //return (set_handle(::GetStockObject(nIndex))) != nullptr; 
      return 0;
   }
   bool object::UnrealizeObject()
   { 
      //ASSERT(get_handle() != nullptr); return ::UnrealizeObject(get_handle()); 
      return 0;
   }
   unsigned int object::GetObjectType() const
   {
      //return (unsigned int)::GetObjectType(get_handle());
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

   /////////////////////////////////////////////////////////////////////////////
   // ::draw2d::object

//
//   void object::dump(dump_context & dumpcontext) const
//   {
//      //::object::dump(dumpcontext);
//
////      dumpcontext << "get_handle() = " << get_handle();
//  //    dumpcontext << "\n";
//   }
//
//
//   void object::assert_ok() const
//   {
//      //::object::assert_ok();
//      //ASSERT(get_handle() == nullptr ||
//        // (::windows_definition::Data.bWin95 || ::GetObjectType(get_handle()) != 0));
//   }


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


} // namespace draw2d_gpu



