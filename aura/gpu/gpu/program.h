#pragma once


#include "acme/primitive/primitive/matter.h"


namespace gpu
{


   class CLASS_DECL_AURA program :
      virtual public ::matter
   {
   public:


      string                  m_strProjection;
      string                  m_strFragment;
      string                  m_strGeometry;
      ::pointer<shader>      m_pshader;
      
      program();
      ~program() override;


      virtual void create_program(::particle * pparticle, const string& strVertex, const string& strFragment, const string& strGeometry = "");


   };


} // namespace gpu




