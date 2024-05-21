// From integration/openssl.cpp on 2023-08-17 02:43 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "openssl.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/acme_directory.h"
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

      m_pcontext->m_strName = "openssl";

      m_pcontext->m_strRelease = "3.0.8";

      m_pcontext->m_pathDownloadURL = "https://www.openssl.org/source/openssl-" + m_pcontext->m_strRelease + ".tar.gz";

   }


} // namespace console_integration



