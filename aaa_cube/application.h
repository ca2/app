// Created by camilo on 2025-05-16 23:15 <3ThomasBorregaardSorensen!!
#pragma once


#include "core/platform/application.h"
#include "bred/graphics3d/camera.h"


namespace cube
{


   class CLASS_DECL_AURA application :
      virtual public ::core::application
   {
   public:

      
      //int m_iWidth;

      //int m_iHeight;

      //::pointer<impact> m_pimpact;

      ::pointer<::gpu::approach>                        m_pgpu;




      application();
      ~application();


      virtual ::gpu::approach* get_gpu();
      virtual ::gpu::approach* gpu();
      virtual void create_gpu();

      //virtual ::graphics3d::camera get_default_camera();


      virtual ::file::path assets_folder();

      virtual ::file::path shaders_folder();


      //virtual void initialize_cube(::user::graphics3d* pimpact);

      //virtual void run_application();

      //virtual void on_layout_cube(int cx, int cy);

      virtual ::string graphics3d_get_implementation_name();


   };


} // namespace cube



