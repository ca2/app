#include "framework.h"
#include "object.h"
#include "lock.h"
#include "device_lock.h"
#include "draw2d.h"
#include "acme/exception/interface_only.h"

#if REFERENCING_DEBUGGING

extern bool g_bDraw2dDisableReferencingDebugging;

#endif

namespace draw2d
{


   object::object()
   {

#if REFERENCING_DEBUGGING

      if (g_bDraw2dDisableReferencingDebugging)
      {

         disable_referencing_debugging();

      }

#endif

      //m_estatus = success;
      //m_estatusLast = success;
      set_modified();

   }


   object::~object()
   {
       
       auto psystem = system();
       
       if(::is_set(psystem))
       {
           
           auto paurasystem = psystem;
           
           if(::is_set(paurasystem))
           {
               
               auto pdraw2d = paurasystem->draw2d();
               
               if(::is_set(pdraw2d))
               {
                   
                   pdraw2d->erase_object(this);
                   
               }
               
           }
           
       }

   }


//   void object::dump(dump_context& dumpcontext) const
//   {
//
//      __UNREFERENCED_PARAMETER(dumpcontext);
//
//      throw ::interface_only();
//
//   }
//
//
//   void object::assert_ok() const
//   {
//
//      throw ::interface_only();
//
//   }


   void object::on_initialize_particle()
   {

      if (system())
      {

         system()->draw2d()->add_object(this);

      }

   }


//   bool object::CreateStockObject(i32 nIndex)
//   {
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   bool object::UnrealizeObject()
//   {
//
//      throw ::interface_only();
//
//      return false;
//
//   }


 /*  void* object::get_os_data(::draw2d::graphcis* pgraphics, ::collection::index i)
   {

      if (!m_bUpdated2 || !m_osdata[0])
      {

         defer_update(pgraphics);

      }


   }

   return (POINTER)get_os_data(pgraphics, i);

}*/

   
//   ::u32 object::GetObjectType() const
//   {
//      
//      throw ::interface_only();
//      
//      return 0;
//
//   }
//
//   
//   bool object::operator==(const object & obj) const
//   {
//      
//      __UNREFERENCED_PARAMETER(obj);
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   bool object::operator!=(const object & obj) const
//   {
//
//      __UNREFERENCED_PARAMETER(obj);
//
//      throw ::interface_only();
//
//      return false;
//
//   }


   void object::defer_update(::draw2d::graphics* pgraphics, ::i8 i) const
   {

      if(!is_up_to_date(i))
      {

         ::draw2d::object* pthis = (::draw2d::object*) this;

         //::draw2d::lock draw2dlock;

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

      clear_os_data();

   }


   void object::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

   }


   void object::destroy()
   {

      destroy_os_data();

      //return ::success;

   }


} // namespace draw2d



