//
// Created by camilo on 2025-08-21.
//
#include "framework.h"
#include "point_light.h"

namespace graphics3d 
{



   void point_light::from(const ::payload & payload)
   {

       ::floating_sequence4 sequence4Color;

      ::copy_color(sequence4Color, payload["color"]);

       m_color = ::argb(sequence4Color.a, sequence4Color.r,
           sequence4Color.g,
           sequence4Color.b
           );

      ::copy(m_sequence3Translation, payload["position"]);

      if (payload.has_property("animation"))
      {

         try
         {
           
            auto panimation = øcreate_new<animation>();

            panimation->from(payload["animation"]);

            m_panimation = panimation;

         }
         catch (...)
         {

         }

      }

   }

   void point_light::defer_animate(float Δt)
   {

      if (!m_panimation)
      {

         m_sequence3FinalPosition = m_sequence3Translation;

         m_sequence4FinalColor = {m_color.f32_red(),m_color.f32_green(), m_color.f32_blue(), m_color.f32_opacity()};

         return;

      }

      m_sequence3FinalPosition =
         m_sequence3Translation+ m_panimation->get_translation(Δt);

      m_sequence4FinalColor = {m_color.f32_red(),m_color.f32_green(), m_color.f32_blue(), m_color.f32_opacity()};

   }


   animation::animation()
   {


         }
   animation::~animation()
   {


   }


} // graphics3d




BEGIN_GPU_PROPERTIES(::gpu::point_light)
GPU_PROPERTY("position", ::gpu::e_type_seq4)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()


BEGIN_GPU_PROPERTIES(::gpu::point_light_push_constants)
GPU_PROPERTY("position", ::gpu::e_type_seq4)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
GPU_PROPERTY("radius", ::gpu::e_type_float)
END_GPU_PROPERTIES()
