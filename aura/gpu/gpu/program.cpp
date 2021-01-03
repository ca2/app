#include "framework.h"
#include "_.h"


namespace gpu
{


   program::program()
   {

   }


   program::~program()
   {

   }


   ::e_status program::create_program(const string& strVertex, const string& strFragment, const string& strGeometry)
   {

      m_strProjection = strVertex;
      m_strFragment = strFragment;
      m_strGeometry = strGeometry;

      ::e_status estatus = __construct_new(m_pshader);

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



