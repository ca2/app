//
// Created by camilo on 2025-08-21 17:59 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "model.h"
#include "scene.h"
#include "scene_object.h"


namespace graphics3d
{


   scene_object::scene_object()
   {

      m_llId = -1;

   }


   scene_object::~scene_object()
   {


   }


   void scene_object::initialize_scene_object(::graphics3d::scene *pscene)
   {

      m_pscene = pscene;

   }



   ::graphics3d::transform &scene_object::transform()
   {

         return m_transform;

   }


   long long scene_object::getId()
   {

      return m_llId;

   }


   ::graphics3d::renderable *scene_object::renderable()
   {

      return m_prenderable;
   }


   void scene_object::set_renderable(::graphics3d::renderable * prenderable)
   {

      m_prenderable = prenderable;

   }


   void scene_object::on_update(float deltaTime)
   {


   }


   color::color scene_object::color()
   {

      return m_color;

   }

   void scene_object::translate(const glm::vec3 & vec3)
   {

      transform().m_vec3Translation = vec3;

   }


   void scene_object::scale(const glm::vec3 & vec3)
   {

      transform().m_vec3Scale = vec3;

   }


} // namespace graphics3d
