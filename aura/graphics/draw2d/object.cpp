#include "platform.h"
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


   object::object(object&& object) :
      m_osdata(object.m_osdata),
      m_baCalculated(object.m_baCalculated),
      m_pointUserOffset(object.m_pointUserOffset)
   {



   }


   object::~object()
   {
       
       auto psystem = system();
       
       if(::is_set(psystem))
       {
           
           auto paurasystem = psystem;
           
           if(::is_set(paurasystem))
           {
               
               auto pdraw2d = paurasystem->m_pdraw2d;
               
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


//   bool object::CreateStockObject(::i32 nIndex)
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


   void object::create(::draw2d::graphics * pgraphics, ::i8 iCreate)
   {

   }


   void object::destroy()
   {

      destroy_os_data();

      //return ::success;

   }


   void object::on_changed()
   {


   }


   void object::set_modified()
   {
      m_baCalculated[0] = false;
      m_baCalculated[1] = false;
      m_baCalculated[2] = false;
      m_baCalculated[3] = false;
      m_baCalculated[4] = false;
      m_baCalculated[5] = false;
      m_baCalculated[6] = false;
      m_baCalculated[7] = false;

      on_changed();

   }


   void object::clear_os_data()
   {

      m_osdata[0] = nullptr;
      m_osdata[1] = nullptr;
      m_osdata[2] = nullptr;
      m_osdata[3] = nullptr;
      m_osdata[4] = nullptr;
      m_osdata[5] = nullptr;
      m_osdata[6] = nullptr;
      m_osdata[7] = nullptr;
      m_baCalculated[0] = false;
      m_baCalculated[1] = false;
      m_baCalculated[2] = false;
      m_baCalculated[3] = false;
      m_baCalculated[4] = false;
      m_baCalculated[5] = false;
      m_baCalculated[6] = false;
      m_baCalculated[7] = false;

   }


} // namespace draw2d



