//
//  file.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 09/06/22 07:42.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"

void file_put_contents(const char * pszFilePath, const char * psz)
{
   
   auto psystem = ::get_system();
   
   psystem->m_pacmefile->put_contents(pszFilePath, psz);
   
}


