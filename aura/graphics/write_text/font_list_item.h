// Created by camilo 2021-06-06 04:25 <3ThomasBS_!!
#pragma once


#include "acme/handler/item.h"
#include "font.h"
#include "text_box.h"


namespace write_text
{


   class CLASS_DECL_AURA font_list_item :
      virtual public ::item
   {
   public:


      //index                               m_iItem;
      text_box                            m_box[3];
      string                              m_strName;
      string                              m_strFont;
      string                              m_strBranch;
      ::file::path                        m_path;
      string                              m_strSample;
      enum_character_set_array            m_echaracterseta;


      font_list_item();
      virtual ~font_list_item();

   };


} // namespace write_text



