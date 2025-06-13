// Created by camilo with Mom and Bilbo support on
// 2025-06-02 03:16 <3ThomasBorregaardSorensen!!
#pragma once


#include "character.h"


namespace draw2d_gpu
{


   class CLASS_DECL_BRED face :
      virtual public ::particle
   {
   public:


      int m_iPixelSize;
      ::string m_strFontName;
      ::string_map<character> m_mapCharacter;
//      unsigned int m_VAO, m_VBO;


      face();
      ~face() override;

      virtual character& get_character(const ::scoped_string& scopedstr);


      virtual void create_character(character& ch, const ::scoped_string& scopedstr);

      void create_draw_buffers();

      void create_texture(character& ch, const unsigned char* p);


   };


} // namespace draw2d_gpu

