#pragma once


#include "berg/platform/system.h"


namespace bred
{


   class CLASS_DECL_BRED system :
      virtual public ::berg::system
   {
   public:


      ::pointer<::typeface::typeface> m_ptypeface;
      ::pointer<::typeface::allocator> m_ptypefaceallocator;


      system();
      ~system() override;


      void common_construct();



      virtual ::typeface::typeface * typeface();
      virtual ::typeface::allocator *typeface_allocator();


      virtual ::string typeface_get_default_typeface_name();


      //void on_set_platform() override;


      //virtual void initialize(::particle * pparticle) override;

      //virtual void on_add_session(::platform::session * pacmesession) override;


   };


} // namespace bred




