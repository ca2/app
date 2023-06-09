//
//  file.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 09/06/22 07:42.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/system.h"


void file_put_contents(const ::scoped_string & scopedstrFilePath, const ::scoped_string & scopedstr)
{
   
   auto ptask = ::get_task();
   
   ptask->acmefile()->put_contents(scopedstrFilePath, scopedstr);
   
}


