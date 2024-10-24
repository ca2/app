#include "framework.h"
#include "x264.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   x264::x264()
   {

   }


   x264::~x264()
   {

   }


   void x264::initialize(::particle * pparticle)
   {

      ::console_integration::build::initialize(pparticle);

      m_papplication->m_strName = "x264";
      
      m_papplication->m_pathDownloadURL = "https://code.videolan.org/videolan/x264.git";

   }


} // namespace console_integration



