//
//  dir_system.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//

#include "framework.h"
#include "aura/os/_.h"
#include "aura/os/_os.h"
#include "aqua/xml.h"

#include "_.h"

char * ns_user_local_desktop_folder();
char * ns_user_local_documents_folder();
char * ns_user_local_downloads_folder();
char * ns_user_local_music_folder();
char * ns_user_local_image_folder();
char * ns_user_local_video_folder();


namespace macos
{


   dir_system::dir_system()
   {


   }




   ::e_status dir_system::initialize(::context_object * pcontextobject)
   {
      
      auto estatus = ::dir_system::initialize(pcontextobject);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;

   }


   ::e_status dir_system::init_system()
   {

      auto estatus = ::dir_system::init_system();
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      ::file::path pathCa2Module = psystem->m_pfilesystem->m_pathCa2Module;
      
      m_pathHome = getenv("HOME");
      
      m_pathCa2 = pathCa2Module;
      
      m_pathCa2 -= 2;
      
      ::str::ends_eat_ci(m_pathCa2, ".app");

      return estatus;
      
   }


} // namespace macos

