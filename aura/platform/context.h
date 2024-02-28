// Created on 2021-03-29 at 13:00 BRT <3TBS_, Mummi and bilbo!!
#pragma once


#include "acme/graphics/image/_configuration.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "apex/platform/context.h"


namespace aura
{


   class CLASS_DECL_AURA context :
      virtual public ::apex::context
   {
   public:


      context();
      ~context() override;


      void initialize_context() override;

      void initialize_context_1() override;

      virtual void defer_initialize_context_image();

      void finalize() override;

      virtual ::image_pointer create_image();


      virtual ::image_pointer create_image(const ::size_i32 & size, const image32_t * pcolor = nullptr, int iScan = -1, ::enum_flag eflagFlag = DEFAULT_CREATE_IMAGE_FLAG);


   };


} // namespace apex



