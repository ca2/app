// Created by camilo on 2026-08-11 16:20 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "bred/gpu/texture.h"


namespace gpu
{

   /// @brief  a texture and its sted (placement)
   class CLASS_DECL_BRED texture_site :
      virtual public ::particle
   {
   public:


      ::pointer < ::gpu::texture >     m_pgputextureSite;
      ::i32_point                      m_pointInput;
      ::i32_point                      m_pointOutput;
      //::i32_rectangle                  m_rectangleTarget;


      texture_site();
      ~texture_site() override;



      bool _is_ok() const override;


      virtual ::gpu::texture * gpu_texture() const;


      inline ::i32_rectangle input_placement() const { return { m_pointInput, m_pgputextureSite->size() }; }
      inline ::i32_rectangle output_placement() const { return { m_pointOutput, m_pgputextureSite->size() }; }
      inline ::i32_size size() const { return m_pgputextureSite->size(); }
      inline ::i32_size raw_size() const { return m_pgputextureSite->raw_size(); }
      inline ::i32 width() const { return m_pgputextureSite->width(); }
      inline ::i32 height() const { return m_pgputextureSite->height(); }
      inline ::i32 input_left() const { return m_pointInput.x; }
      inline ::i32 input_top() const { return m_pointInput.y; }
      inline ::i32 output_left() const { return m_pointOutput.x; }
      inline ::i32 output_top() const { return m_pointOutput.y; }
      inline ::i32 input_right() const { return m_pointInput.x + width(); }
      inline ::i32 input_bottom() const { return m_pointInput.y + height(); }
      inline ::i32 output_right() const { return m_pointOutput.x + width(); }
      inline ::i32 output_bottom() const { return m_pointOutput.y + height(); }


   };


} // namespace gpu
