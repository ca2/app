//
// Created by camilo on 2025-08-21 17:59 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "model.h"
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


   ::graphics3d::transform &scene_object::transform()
   {

         return m_transform;

   }


   long long scene_object::getId()
   {

      return m_llId;

   }


   IModel *scene_object::model()
   {

      return m_pmodel;
   }


   void scene_object::set_model(IModel * pmodel)
   {

      m_pmodel = pmodel;

   }


   void scene_object::on_update(float deltaTime)
   {
   }

   color::color scene_object::color()
   {

      return m_color;

   }



} // namespace graphics3d
