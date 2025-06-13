// Created by camilo on 2025-06-12 21:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "snapshot.h"
#include "texture.h"


namespace gpu
{


   snapshot::snapshot()
   {


   }


   snapshot::~snapshot()
   {


   }


   void snapshot::initialize_gpu_snapshot(context * pcontext, texture* ptexture, const ::int_rectangle& rectangleTarget)
   {

      m_pgpucontext = pcontext;
      m_pgputexture = ptexture;
      m_rectangleTarget = rectangleTarget;

   }


} // namespace gpu


