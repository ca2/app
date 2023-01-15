// Created by camilo on 2023-01-15 07:14 <3ThomasBorregaardSørensen!!
#pragma once


#include "framework.h"
#include "acme/console.h"
#include <stdio.h>
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/primitive/primitive/url.h"
#include "apex/networking/http/context.h"


namespace console
{


   namespace build_library
   {


      class build_library :
         virtual public ::particle
      {
      public:


         ::file::path      m_pathFolder;
         ::file::path      m_path;
         ::string          m_strName;
         ::string          m_strRelease;
         ::string          m_strPlatform;
         ::string          m_strConfiguration;


         build_library() { }
         ~build_library() override { }


         void run() override
         {

            m_path = m_strName / m_strRelease / m_strPlatform / m_strConfiguration;

            acmedirectory()->create(m_pathFolder / m_path);

         }


      };


   } // namespace build_library


} // namespace console



