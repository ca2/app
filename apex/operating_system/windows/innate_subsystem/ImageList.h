//
// Created by camilo on 2026-04-06 14:22 <3ThomasBorregaardSørensen!!
//
#pragma once
#include <commctrl.h>

#include "acme/subsystem/particle.h"
#include "apex/innate_subsystem/ImageList.h"
#include "acme/_operating_system.h"

namespace windows
{


namespace innate_subsystem
{


   class CLASS_DECL_APEX ImageList :
   virtual public ::subsystem::composite<::innate_subsystem::ImageListInterface>
   {
   public:

         HIMAGELIST  m_himagelist;


      ImageList();
      ~ImageList() override;

      void initialize_image_list() override;

      void create_image_list(int cx, int cy, int flags, int iInitialSize, int iGrow) override;

      void destroy_image_list() override;



   };


} // namespace innate_subsystem


} // namespace windows