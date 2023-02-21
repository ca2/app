// Created by camilo on 2021-11-10 10:33 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/_.h"


#include <zlib.h>
//#include <zutil.h>


#if defined(_folder_zip_project)
#define CLASS_DECL_FOLDER_ZIP  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_FOLDER_ZIP  CLASS_DECL_IMPORT
#endif


namespace folder_zip
{


   class file;
   class folder;


} // namespace folder_zip



