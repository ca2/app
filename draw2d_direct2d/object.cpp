#include "framework.h"


namespace draw2d_direct2d
{


   object::object()
   {

      //set_handle(nullptr);
      //m_pgraphics    = nullptr;
      m_powner = nullptr;

   }


   object::~object()
   {
      //delete_object();
   }

   int object::get_object(int nCount, LPVOID lpObject) const
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
   ::u32 object::GetObjectType() const
   {
      //return (::u32)::GetObjectType(get_handle());
      return 0;
   }

   bool object::operator==(const object& obj) const
   {
      //return ((HGDIOBJ) obj.get_os_data()) == get_handle();
      return false;
   }

   bool object::operator!=(const object& obj) const
   {
      //return ((HGDIOBJ) obj.get_os_data()) != get_handle();
      return true;
   }


   object * object_allocator(::object * pobject, HANDLE h)
   {

      return nullptr;

   }


   //bool object::delete_object()
   //{
   //   //if (get_os_data() == nullptr)
   //   // return false;
   //   //return ::DeleteObject(Detach());
   //   return false;
   //}

   /////////////////////////////////////////////////////////////////////////////
   // object


   void object::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);

   }


   void object::assert_valid() const
   {

      ::draw2d::object::assert_valid();

   }


   //void * object::get_os_data() const
   //{

   //   return nullptr;

   //}


   //void * object::get_os_data_ex(int i) const
   //{
   //   if(i == data_graphics)
   //   {
   //      return m_pgraphics;
   //   }
   //   return ::draw2d::object::get_os_data_ex(i);
   //}

} // namespace draw2d_direct2d




