//
//  shared_memory.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-18
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "shared_memory.h"

   
shared_memory::shared_memory()
{

}
shared_memory::~shared_memory()
{


}

bool shared_memory::CreateSharedMemory(const_char_pointer pszName, memsize size)
{

   throw ::interface_only();

   return false;

}


bool shared_memory::OpenSharedMemory(const_char_pointer pszName, memsize size)
{

   throw ::interface_only();

   return false;

}

//   void* shared_memory::Data() const
//   {
//
// throw ::interface_only();
//
// return nullptr;
//
//
//   }
//
//
//   memsize shared_memory::Size() const
//   {
//
// throw ::interface_only();
//
// return 0;
//
//   }

void shared_memory::Close()
{

   throw ::interface_only();

}
