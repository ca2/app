#include "framework.h"
#include "program.h"
#include "aura/graphics/gpu/shader.h"


namespace gpu_opengl
{


   program::program()
   {

   }


   program::~program()
   {

   }


   void program::create_program(::particle * pparticle, const string& strVertex, const string& strFragment, const string& strGeometry)
   {

      m_strProjection = strVertex;
      m_strFragment = strFragment;
      m_strGeometry = strGeometry;

      //::e_status estatus = 
      
      pparticle->__øconstruct(m_pshader);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      m_pshader->create_shader(m_strProjection, m_strFragment, m_strGeometry);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


} // namespace gpu_opengl



