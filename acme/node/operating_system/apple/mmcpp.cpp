//
//  mmcpp.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "framework.h"
#undef DEBUG
#include <Carbon/Carbon.h>

#if defined(__APPLE__)

CFDataRef get_os_cf_data(const ::memory_base & memory, memsize pos, memsize size)
{
   if (pos > memory.get_size())
      __throw(error_invalid_argument);
   if(size < 0)
   {
      size = memory.get_size() - pos;

   }
   else if (pos + size > memory.get_size())
   {
      size = memory.get_size() - pos;
   }
   return CFDataCreate(kCFAllocatorDefault, (const ::u8 *)&memory.get_data()[pos], (CFIndex)size);
}


void set_os_cf_data(memory_base &memory, CFDataRef data, memsize pos, memsize size)
{

   if (pos > CFDataGetLength(data))
   {

      __throw(error_invalid_argument);

   }

   if (pos > CFDataGetLength(data))
   {

      __throw(error_invalid_argument);

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

   ::memcpy_dup(memory.get_data(), &CFDataGetBytePtr(data)[pos], size);

}


#endif

