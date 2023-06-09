//
//  mmcpp.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 18/08/21.
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#include "framework.h"
#include "acme/primitive/primitive/memory.h"
#undef DEBUG
#if defined(MACOS)
#include <Carbon/Carbon.h>
#endif

#if defined(__APPLE__)

CFDataRef get_os_cf_data(const ::memory_base & memory, memsize pos, memsize size)
{
   if (pos > memory.size())
      throw ::exception(error_bad_argument);
   if(size < 0)
   {
      size = memory.size() - pos;

   }
   else if (pos + size > memory.size())
   {
      size = memory.size() - pos;
   }
   return CFDataCreate(kCFAllocatorDefault, (const ::u8 *)&memory.data()[pos], (CFIndex)size);
}


void set_os_cf_data(memory_base &memory, CFDataRef data, memsize pos, memsize size)
{

   if (pos > CFDataGetLength(data))
   {

      throw ::exception(error_bad_argument);

   }

   if (pos > CFDataGetLength(data))
   {

      throw ::exception(error_bad_argument);

   }

   if(size < 0)
   {

      size = CFDataGetLength(data) - pos;

   }
   else if (pos + size > CFDataGetLength(data))
   {

      size = CFDataGetLength(data) - pos;

   }

   memory.set_size(size);

   ::memory_copy(memory.data(), &CFDataGetBytePtr(data)[pos], size);

}


#endif

