//
// Created by camilo on 2025-09-29 10:41 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "scene_renderable.h"
#include "model.h"
#include "scene_base.h"


namespace graphics3d
{


   scene_renderable::scene_renderable()
   {
      
      m_llId = -1; 
   
   }


   scene_renderable::~scene_renderable()
   {
   
   
   }


   void scene_renderable::initialize_scene_renderable(::graphics3d::scene_base *pscene)
   {
      
      m_pscene = pscene; 
   
   }


   ::graphics3d::transform &scene_renderable::transform()
   {
      
      return m_transform; 
   
   }


   long long scene_renderable::getId() 
   {
      
      return m_llId; 
   
   }


   ::graphics3d::renderable *scene_renderable::renderable()
   {
      
      return m_prenderable; 
   
   }


   void scene_renderable::set_renderable(::graphics3d::renderable *prenderable)
   {
      
      m_prenderable = prenderable; 
   
   }


   void scene_renderable::on_update(float deltaTime)
   {
   
   
   }


   color::color scene_renderable::color() 
   {
      
      return m_color; 
   
   }


   void scene_renderable::translate(const ::floating_sequence3 &floating_sequence3)
   {
      
      transform().m_sequence3Position = floating_sequence3; 
   
   }


   void scene_renderable::scale(const ::floating_sequence3 &floating_sequence3)
   {
      
      transform().m_sequence3Scale = floating_sequence3; 
   
   }


} // namespace graphics3d
