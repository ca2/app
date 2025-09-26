#include "framework.h"
#include "fdk_aac.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   fdk_aac::fdk_aac()
   {

   }


   fdk_aac::~fdk_aac()
   {

   }


   void fdk_aac::initialize(::particle * pparticle)
   {

      ::console_integration::build::initialize(pparticle);

      m_papplication->m_strName = "fdk-aac";
      
      m_papplication->m_pathDownloadURL = "https://github.com/mstorsjo/fdk-aac.git";

   }


} // namespace console_integration



