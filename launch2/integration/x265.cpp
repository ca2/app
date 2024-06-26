#include "framework.h"
#include "x265.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   x265::x265()
   {

   }


   x265::~x265()
   {

   }


   void x265::initialize(::particle * pparticle)
   {

      ::console_integration::build::initialize(pparticle);

      m_pcontext->m_strName = "x265";
      
      m_pcontext->m_pathDownloadURL = "https://github.com/cpp-port/x265";

   }


} // namespace console_integration



