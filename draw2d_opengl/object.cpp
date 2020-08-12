#include "framework.h"

namespace draw2d_opengl
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
   bool object::operator==(const ::draw2d::object& obj) const
   { 
      //return ((HGDIOBJ) obj.get_os_data()) == get_handle(); 
      return FALSE;
   }
   bool object::operator!=(const ::draw2d::object& obj) const
   { 
      //return ((HGDIOBJ) obj.get_os_data()) != get_handle(); 
      return TRUE;
   }


   bool object::delete_object()
   {
      //if (get_os_data() == nullptr)
        // return FALSE;
      //return ::DeleteObject(detach());
      return FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::draw2d::object


   void object::dump(dump_context & dumpcontext) const
   {
      //::object::dump(dumpcontext);

//      dumpcontext << "get_handle() = " << get_handle();
  //    dumpcontext << "\n";
   }


   void object::assert_valid() const
   {
      //::object::assert_valid();
      //ASSERT(get_handle() == nullptr ||
        // (afxData.bWin95 || ::GetObjectType(get_handle()) != 0));
   }


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


} // namespace draw2d_opengl



