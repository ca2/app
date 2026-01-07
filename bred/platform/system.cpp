#include "framework.h"
#include "acme/platform/system_setup.h"
#include "bred/const/idpool.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "bred/graphics3d/camera.h"
#include "bred/typeface/allocator.h"


namespace bred
{


   system::system()
   {

      common_construct();

      factory()->add_factory_item < ::bred::application, ::apex::application >();
      factory()->add_factory_item < ::bred::session, ::apex::session >();
      factory()->add_factory_item<::graphics3d::camera>();

   }


   system::~system()
   {


   }


   void system::common_construct()
   {

      //factory()->add_factory_item < ::bred::idpool, ::acme::idpool >();
      //add_factory_item < ::core::user, ::user::user >();
      //add_factory_item < ::bred::idpool, ::apex::idpool >();

   }


   // void system::on_set_platform()
   // {
   //
   //    ::berg::system::on_set_platform();
   //
   //    factory()->add_factory_item < ::bred::application, ::apex::application >();
   //    factory()->add_factory_item < ::bred::session, ::apex::session >();
   //
   //
   // }


   // void system::initialize(::particle * pparticle)
   // {
   //
   //    //auto estatus =
   //
   //    ::berg::system::initialize(pparticle);
   //
   //    //if (!estatus)
   //    //{
   //
   //    //   return estatus;
   //
   //    //}
   //
   //    //return estatus;
   //
   // }



   //void system::on_add_session(::apex::session* papexsession)
   //{

   //   ::berg::system::on_add_session(papexsession);

   //   if (papexsession->m_iEdge == 0)
   //   {

   //      if (!m_pbredsession)
   //      {

   //         m_pbredsession = papexsession->m_pbredsession;

   //      }

   //   }

   //   papexsession->m_pbredsystem = this;

   //}
   //void system::initialize_rich_text()
   //{

   //   if (!__rich_text_initialize())
   //   {

   //      return false;

   //   }

   //   return ::success;

   //}

  
   //__namespace_system_factory(system);


   ::string system::typeface_get_default_typeface_name()
   {

      ::string strDefaultTypeface;

#ifdef WINDOWS

      strDefaultTypeface = "gdiplus";

#else

      strDefaultTypeface = "fontconfig";

#endif

      return strDefaultTypeface;

   }


   ::typeface::typeface *system::typeface()
   {

      if (::is_null(m_ptypeface))
      {

         ::string strDefaultTypeface;
         
         strDefaultTypeface = typeface_get_default_typeface_name();

         m_ptypeface = typeface_allocator()->create_typeface(strDefaultTypeface);

      }

      return m_ptypeface;

   }


   ::typeface::allocator * system::typeface_allocator()
   {

      if (::is_null(m_ptypefaceallocator))
      {

         auto pfactory = typeface_factory();

         m_ptypefaceallocator = øcreate<::typeface::allocator>(pfactory);

      }

      return m_ptypefaceallocator;

   }


} // namespace bred



