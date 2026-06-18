// Created by camilo 2021-06-06 04:25 <3ThomasBS_!!
#pragma once


#include "font_list_item.h"
#include "acme/handler/item_container.h"


namespace write_text
{



   /// @brief  container of font_list_item
   class CLASS_DECL_AURA font_list_data :
      virtual public ::item_container
   {
   public:


      ::collection::index     m_iSerial;
      ::collection::index     m_iUpdateId;
      ::i32                     m_iBaseSize;
      ::i32_array_base        m_iaSize;
      ::i32_rectangle         m_rectangleX;
      ::i32                     m_iUpdatedCount;
      bool                    m_bLayoutStillIntersect;


   };


} // namespace write_text



