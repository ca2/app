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
      ::int_size     m_size;


      icon();
      ~icon() override;


      virtual void _create();
      virtual void create(const ::payload & payloadFile, const ::int_size & size);


   };


} // namespace innate_ui



