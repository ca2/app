// From integration/openssl.cpp on 2023-08-17 02:43 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "openssl.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   openssl::openssl()
   {

   }


   openssl::~openssl()
   {

   }


   void openssl::initialize(::particle* pparticle)
   {

      ::console_integration::build::initialize(pparticle);

      m_papplication->m_strName = "openssl";

      m_papplication->m_strRelease = "3.0.8";

      m_papplication->m_pathDownloadURL = "https://www.openssl.org/source/openssl-" + m_papplication->m_strRelease + ".tar.gz";

   }


} // namespace console_integration



