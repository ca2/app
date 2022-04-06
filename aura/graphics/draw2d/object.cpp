#include "framework.h"
#include "object.h"
#include "lock.h"
#include "device_lock.h"


namespace draw2d
{


   object::object()
   {

      //m_estatus = success;
      //m_estatusLast = success;
      set_modified();

   }


   object::~object()
   {

   }


   void object::dump(dump_context& dumpcontext) const
   {

      __UNREFERENCED_PARAMETER(dumpcontext);

      throw ::interface_only();

   }


   void object::assert_ok() const
   {

      throw ::interface_only();

   }


   bool object::CreateStockObject(i32 nIndex)
   {

      throw ::interface_only();

      return false;

   }


   bool object::UnrealizeObject()
   {

      throw ::interface_only();

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

   
   ::u32 object::GetObjectType() const
   {
      
      throw ::interface_only();
      
      return 0;

   }

   
   bool object::operator==(const object & obj) const
   {
      
      __UNREFERENCED_PARAMETER(obj);

      throw ::interface_only();

      return false;

   }


   bool object::operator!=(const object & obj) const
   {

      __UNREFERENCED_PARAMETER(obj);

      throw ::interface_only();

      return false;

   }


   void object::defer_update(::draw2d::graphics* pgraphics, ::i8 i) const
   {

      if(!is_up_to_date(i))
      {

         ::draw2d::object* pthis = (::draw2d::object*) this;

         ::draw2d::lock draw2dlock;

         ::draw2d::device_lock devicelock(pthis);

         if (this->m_osdata[0])
         {

            pthis->destroy_os_data();

            pthis->clear_os_data();

         }

         pthis->create(pgraphics, i);

         pthis->m_baCalculated[i] = true;

      }

   }


   void object::destroy_os_data()
   {

      //return true;

   }


   void object::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

      //return true;

   }


   void object::destroy()
   {

      destroy_os_data();

      //return ::success;

   }


} // namespace draw2d



