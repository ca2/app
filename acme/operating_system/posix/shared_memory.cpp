
//
//  shared_memory.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/operating_system/shared_memory.h"

//#if !defined(_WIN32)

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


namespace posix
{

   shared_memory::shared_memory()
   {
      
      
      
   }


   shared_memory::~shared_memory()
   {
      Close();
   }


   void shared_memory::CreateSharedMemory(const char* name, memsize size)
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
shared_memory::shared_memory()
{
   
   

}


shared_memory::~shared_memory()
{
    Close();
}


bool shared_memory::Create(const_char_pointer pszName, size_t size)
{
    m_size = size;

    m_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    if (m_fd < 0)
        return false;

    if (ftruncate(m_fd, size) != 0)
        return false;

    m_data = mmap(
        nullptr,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        m_fd,
        0);

    return m_data != MAP_FAILED;
}

bool shared_memory::Open(const_char_pointer pszName, size_t size)
{
    m_size = size;

    m_fd = shm_open(name, O_RDWR, 0666);

    if (m_fd < 0)
        return false;

    m_data = mmap(
        nullptr,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        m_fd,
        0);

    return m_data != MAP_FAILED;
}



void shared_memory::Close()
{


    if (m_data)
    {
        munmap(m_data, m_size);
        m_data = nullptr;
    }

    if (m_fd >= 0)
    {
        close(m_fd);
        m_fd = -1;
    }

}

