#include "framework.h"
#include "lame.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   lame::lame()
   {

   }


   lame::~lame()
   {

   }


   void lame::initialize(::particle * pparticle)
   {

      ::console_integration::build::initialize(pparticle);

      m_papplication->m_strName = "mp3lame";
      
      m_papplication->m_pathDownloadURL = "https://github.com/lameproject/lame.git";

   }


} // namespace console_integration



