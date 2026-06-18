
//
//  shared_memory.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/operating_system/posix/shared_memory.h"

//#if !defined(_WIN32)

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


namespace posix
{

shared_memory::shared_memory()
{
   
   m_p = nullptr;
   
}


shared_memory::~shared_memory()
{
   Close();
}


void shared_memory::CreateSharedMemory(const_char_pointer name, memsize size)
{
   m_memsize = size;
   
   m_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
   
   if (m_fd < 0)
   {
      throw ::exception(error_resource);
      
   }
   
   if (ftruncate(m_fd, size) != 0)
   {
      throw ::exception(error_no_memory);
      
   }
   
   m_p = mmap(
              nullptr,
              size,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              m_fd,
              0);
   
   if(m_p == MAP_FAILED)
   {
      
      throw ::exception(error_resource);
   }
}

void shared_memory::OpenSharedMemory(const_char_pointer pszName, memsize size)
{
   m_memsize = size;
   
   m_fd = shm_open(pszName, O_RDWR, 0666);
   
   if (m_fd < 0)
   {
      throw ::exception(error_resource);
      
   }
   
   m_p = mmap(
              nullptr,
              size,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              m_fd,
              0);
   
   if(m_p == MAP_FAILED)
   {
      
      throw ::exception(error_resource);
   }
}



   void shared_memory::Close()
   {
      
      
      if (m_p)
      {
         munmap(m_p, m_memsize);
         m_p = nullptr;
      }
      
      if (m_fd >= 0)
      {
         close(m_fd);
         m_fd = -1;
      }
      
   }


} // namespace posix
