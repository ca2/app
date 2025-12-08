//
// From V0idsEmbrace.graphics3d by camilo on 2025-08-21 18:32 <3ThomasBorregaardSorensen
//
#pragma once


#include "bred/gpu/properties.h"
#include "bred/graphics3d/scene_renderable.h"


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::point_light)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::point_light_push_constants)

#include "acme/prototype/geometry/_payload.h"

namespace graphics3d
{



   enum enum_shape
   {

      e_shape_none,
      e_shape_circle,

   };

   class circle_shape
   {
   public:


      floating_sequence3 m_radius;
      floating_sequence3 m_axis;
      floating_sequence3 get_translation(const floating_angle & angle)
      { 
         auto rotation = ::floating_matrix4::rotation(m_axis, angle);

         auto translation = rotation * m_radius;

         return translation;

      }

      void from(const ::payload &payload) 
      { 
         
         ::copy(m_radius, payload["radius"]);
         ::copy(m_axis, payload["axis"]);
      
      }

   };

   class translation_animation
   {
   public:

      enum_shape m_eshape = e_shape_none;

      union
      {
         circle_shape m_circleshape;
      };
      float m_fSpeed;

      floating_sequence3 get_translation(float Δt)
      {

         if (m_eshape == e_shape_circle)
         {

            return m_circleshape.get_translation(::radians(m_fSpeed * Δt));
         }
         else
         {

            throw ::exception(error_wrong_state);
         }
      }

                  void from(const ::payload &payload)
      {
         if (payload.has_property("path"))
         {

            if (payload["path"]["shape"] == "circle")
            {
               m_eshape = e_shape_circle;
               m_fSpeed = payload["speed"].as_float();
               m_circleshape.from(payload["path"]);
            }
         }
      }

   };

   enum enum_animation
   {

      e_animation_none,
      e_animation_translation,

   };

   class CLASS_DECL_BRED animation : virtual public ::particle
   {
   public:

      enum_animation m_eanimation;

      union
      {
         translation_animation m_translationanimation;

      };

      animation();
      ~animation() override;

            void from(const ::payload &payload)
            { 
               if (payload["type"] == "translation")
               {
                  m_eanimation = e_animation_translation;

                  m_translationanimation.from(payload);

               }
               else
               {

                  throw ::exception(error_wrong_state);
               }

            }

            floating_sequence3 get_translation(float Δt)
            {
               if (m_eanimation == e_animation_translation)
               {

                  m_translationanimation.get_translation(Δt);

               }
               else
               {
                  throw ::exception(error_wrong_state);

               }

            }


   };

   class CLASS_DECL_BRED point_light :
      virtual public scene_renderable
   {
   public:

      float m_fLightIntensity = 1.0f;
      float m_fOrbitRadius = 2.0f;
      floating_sequence4 m_sequence4Color;
      floating_sequence3 m_sequence3Position;
      ::pointer<animation> m_panimation;

      floating_sequence4 m_sequence4FinalColor;
      floating_sequence3 m_sequence3FinalPosition;

      void from(const ::payload &payload);

      void defer_animate(float Δt);
      floating_sequence3 position()  const { return m_sequence3FinalPosition; }
      floating_sequence4 color()  const { return m_sequence4FinalColor; }

   };


} // namespace graphics3d






