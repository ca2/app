#include "framework.h"
#include "program.h"
#include "shader.h"
#include "acme/primitive/primitive/particle_factory.h"
//#include "_.h"
//#include "_gpu.h"


namespace gpu
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
      ::__construct_new(pparticle, m_pshader);

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


} // namespace gpu



