#include "framework.h"


namespace draw2d
{


   object::object()
   {

      set_modified();

   }


   object::~object()
   {

   }


   void object::dump(dump_context& dumpcontext) const
   {

      UNREFERENCED_PARAMETER(dumpcontext);

      ::exception::throw_interface_only();

   }


   void object::assert_valid() const
   {

      ::exception::throw_interface_only();

   }


   bool object::CreateStockObject(i32 nIndex)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool object::UnrealizeObject()
   {

      ::exception::throw_interface_only();

      return false;

   }


 /*  void* object::get_os_data(::draw2d::graphcis* pgraphics, ::index i)
   {

      if (!m_bUpdated2 || !m_osdata[0])
      {

         defer_update(pgraphics);

      }


   }

   return (POINTER)get_os_data(pgraphics, i);

}*/

   
   UINT object::GetObjectType() const
   {
      
      ::exception::throw_interface_only();
      
      return 0;

   }

   
   bool object::operator==(const object & obj) const
   {
      
      UNREFERENCED_PARAMETER(obj);

      ::exception::throw_interface_only();

      return false;

   }


   bool object::operator!=(const object & obj) const
   {

      UNREFERENCED_PARAMETER(obj);

      ::exception::throw_interface_only();

      return false;

   }


   void object::defer_update(::draw2d::graphics* pgraphics, ::i8 i) const
   {

      if(is_modified() || !m_osdata[i])
      {

         ::draw2d::object* pthis = (::draw2d::object*) this;

         pthis->destroy();

         pthis->clear_os_data();

         if (pthis->create(pgraphics, i))
         {

            pthis->set_updated();

         }

      }

   }


   bool object::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

      return true;

   }


   void object::destroy()
   {

   }


} // namespace draw2d


e_trace_category object_trace_category(::generic_object * pobject)
{

   return pobject->trace_category();

}


const char * topic_text(::generic_object * pobject)
{

   if (::is_null(pobject))
   {

      return nullptr;

   }

   return pobject->topic_text();

}



