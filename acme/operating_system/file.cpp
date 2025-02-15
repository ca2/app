//
//  file.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 09/06/22 07:42.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#include "framework.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/system.h"


void file_put_contents(const ::scoped_string & scopedstrFilePath, const ::scoped_string & scopedstr)
{
   
   auto ptask = ::get_task();
   
   ptask->file_system()->put_contents(scopedstrFilePath, scopedstr);
   
}


