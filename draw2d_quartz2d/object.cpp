#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   
   object::object()
   {
      
   }
   
   
   object::~object()
   {
      
   }
   
   
   i32 object::get_object(i32 nCount, LPVOID lpObject) const
   {
      
      return 0;
      
   }
   
   
   bool object::CreateStockObject(i32 nIndex)
   {
      
      return 0;
      
   }
   
   
   bool object::UnrealizeObject()
   {
   
      return 0;
      
   }
   
   
   UINT object::GetObjectType() const
   {
   
      return 0;
      
   }
   
   
   bool object::operator==(const ::draw2d::object& obj) const
   {
      
      return false;
      
   }
   
   
   bool object::operator!=(const ::draw2d::object& obj) const
   {
      
      return true;
      
   }
   
   
   object * graphics_object_allocator(::base::application * papp, HANDLE h)
   {
      
      return nullptr;
      
   }
   
   
   bool object::delete_object()
   {

      return false;
      
   }
   

   void object::dump(dump_context & dumpcontext) const
   {

      ::context_object::dump(dumpcontext);
      
   }
   

   void object::assert_valid() const
   {

      ::context_object::assert_valid();

   }
   

   
   
} // namespace draw2d_quartz2d



