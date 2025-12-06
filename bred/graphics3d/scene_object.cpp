//
// Created by camilo on 2025-08-21 17:59 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "scene_object.h"
#include "scene_base.h"


namespace graphics3d
{


   scene_object::scene_object() 
   {
      
      //m_llId = -1; 
   
   }


   scene_object::~scene_object() 
   {
   
   
   }


   void scene_object::initialize_scene_object(::graphics3d::scene_base *pscene)
   {

      initialize_gpu_context_object(pscene->m_pgpucontext);
      
      m_pscene = pscene; 
   
   }



} // namespace graphics3d



