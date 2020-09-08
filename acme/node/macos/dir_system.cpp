//
//  dir_system.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//

#include "framework.h"
#include "acme/os/_.h"
#include "acme/os/_os.h"
//#include "acme/xml/_.h"

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




   ::estatus dir_system::initialize(::generic * pobjectContext)
   {
      
      auto estatus = ::dir_system::initialize(pobjectContext);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;

   }


   ::estatus dir_system::init_system()
   {

      auto estatus = ::dir_system::init_system();
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      ::file::path pathCa2Module = System.m_pfilesystem->m_pathCa2Module;
      
      m_pathHome = getenv("HOME");
      
      m_pathCa2 = pathCa2Module;
      
      m_pathCa2 -= 2;
      
      ::str::ends_eat_ci(m_pathCa2, ".app");

      return estatus;
      
   }


} // namespace macos

