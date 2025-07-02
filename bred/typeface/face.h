// Created by camilo with Mom and Bilbo support on
// 2025-06-02 03:16 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/typeface/character.h"


namespace typeface
{


   class CLASS_DECL_BRED face :
      virtual public ::particle
   {
   public:


      ::pointer < ::gpu::renderer > m_pgpurenderer;

      int m_iPixelSize;
      ::string m_strFontName;
      ::string_map<::typeface::character> m_mapCharacter;
//      unsigned int m_VAO, m_VBO;
      ::pointer < ::gpu::model_buffer > m_pmodelbufferBox;


      face();
      ~face() override;


      virtual void initialize_gpu_buffer(::gpu::renderer* pgpurenderer);

      virtual character& get_character(const ::scoped_string& scopedstr);


      virtual void create_character(character& ch, const ::scoped_string& scopedstr);

      void create_draw_buffers();

      void create_texture(character& ch, const unsigned char* p);


   };


} // namespace typeface



