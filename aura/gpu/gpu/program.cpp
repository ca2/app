#include "framework.h"
#include "_.h"
#include "_gpu.h"


namespace gpu
{


   program::program()
   {

   }


   program::~program()
   {

   }


   void program::create_program(::object * pobject, const string& strVertex, const string& strFragment, const string& strGeometry)
   {

      m_strProjection = strVertex;
      m_strFragment = strFragment;
      m_strGeometry = strGeometry;

      ::e_status estatus = pobject->__construct_new(m_pshader);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pshader->create_shader(m_strProjection, m_strFragment, m_strGeometry);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace gpu



