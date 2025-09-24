#include "framework.h"
#include "freetype.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   freetype::freetype()
   {

   }


   freetype::~freetype()
   {

   }


   void freetype::initialize(::particle * pparticle)
   {

      ::console_integration::build::initialize(pparticle);

      m_papplication->m_strName = "freetype";
      
      m_papplication->m_pathDownloadURL = "https://github.com/freetype/freetype.git";

   }


} // namespace console_integration



