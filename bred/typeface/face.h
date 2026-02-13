// Created by camilo with Mom and Bilbo support on
// 2025-06-02 03:16 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/typeface/character.h"
#include "acme/prototype/collection/map.h"


namespace typeface
{


   class CLASS_DECL_BRED face :
      virtual public ::particle
   {
   public:


      //::pointer < ::gpu::renderer > m_pgpurenderer;

      int m_iPixelSize;
      ::string m_strFontName;
      //::string_map_base<::typeface::character> m_mapCharacter;
      ::int_map<::typeface::character> m_mapCharacter;
//      unsigned int m_VAO, m_VBO;
      //::pointer < ::gpu::model_buffer > m_pmodelbufferBox;


      face();
      ~face() override;


      void initialize(::particle * pparticle) override;

      //virtual void initialize_typeface_face(::gpu::renderer* pgpurenderer);

      virtual character& get_character(const ::scoped_string& scopedstr);


      virtual void get_text_metric(::write_text::text_metric* ptextmetric);


      virtual void create_character(character& ch, const ::scoped_string& scopedstr);

      //virtual void create_draw_buffers();

      virtual void create_texture(character& ch, const unsigned char* p);


      //virtual ::gpu::model_buffer* box_model_buffer();

   };


} // namespace typeface



