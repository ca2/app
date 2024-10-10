// Created by camilo on 2024-09-13 07:13 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/geometry2d/size.h"


namespace innate_ui
{


   class CLASS_DECL_APEX icon :
      virtual public ::object
   {
   public:


      ::memory       m_memory;
      ::size_i32     m_size;


      icon();
      ~icon() override;


      virtual void _create();
      virtual void create(const ::payload & payloadFile, const ::size_i32 & size);


   };


} // namespace innate_ui



