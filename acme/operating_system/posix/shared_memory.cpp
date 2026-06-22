
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

#if defined(__ANDROID__)
#include <android/sharedmem.h>
#include <mutex>
#include <string>
#include <unordered_map>
#endif


#if defined(__ANDROID__)

namespace
{

   struct shared_memory_entry
   {

      int m_fd = -1;
      memsize m_memsize = 0;
      int m_iReferenceCount = 0;

   };


   std::mutex g_sharedmemoryMutex;
   std::unordered_map<std::string, shared_memory_entry> g_sharedmemoryMap;


   const char * android_shared_memory_name(const_char_pointer pszName)
   {

      if (pszName == nullptr || *pszName == '\0')
      {

         throw ::exception(error_bad_argument);

      }

      return pszName[0] == '/' ? pszName + 1 : pszName;

   }


   void close_shared_memory_entry(shared_memory_entry & entry)
   {

      if (entry.m_fd >= 0)
      {

         close(entry.m_fd);

         entry.m_fd = -1;

      }

      entry.m_memsize = 0;
      entry.m_iReferenceCount = 0;

   }

} // namespace

#endif


namespace posix
{

shared_memory::shared_memory()
{
   
   m_memsize = 0;
   m_fd = -1;
   m_p = nullptr;
   
}


shared_memory::~shared_memory()
{
   Close();
}


void shared_memory::CreateSharedMemory(const_char_pointer name, memsize size)
{
   m_memsize = size;

#if defined(__ANDROID__)

   auto pszName = android_shared_memory_name(name);

   int fd = -1;

   {

      std::lock_guard<std::mutex> synchronouslock(g_sharedmemoryMutex);

      auto & entry = g_sharedmemoryMap[pszName];

      if (entry.m_fd < 0)
      {

         entry.m_fd = ASharedMemory_create(pszName, size);

         if (entry.m_fd < 0)
         {

            g_sharedmemoryMap.erase(pszName);

            throw ::exception(error_resource);

         }

         entry.m_memsize = size;

      }
      else if (entry.m_memsize != size)
      {

         throw ::exception(error_no_memory);

      }

      fd = dup(entry.m_fd);

      if (fd < 0)
      {

         if (entry.m_iReferenceCount <= 0)
         {

            close_shared_memory_entry(entry);

            g_sharedmemoryMap.erase(pszName);

         }

         throw ::exception(error_resource);

      }

      entry.m_iReferenceCount++;

   }

   m_fd = fd;
   m_strName = pszName;

#else
   
   m_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
   
   if (m_fd < 0)
   {
      throw ::exception(error_resource);
      
   }
   
   if (ftruncate(m_fd, size) != 0)
   {

      Close();

      throw ::exception(error_no_memory);
      
   }

#endif
   
   m_p = mmap(
              nullptr,
              size,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              m_fd,
              0);
   
   if(m_p == MAP_FAILED)
   {

      m_p = nullptr;

      Close();

      throw ::exception(error_resource);
   }
}

void shared_memory::OpenSharedMemory(const_char_pointer pszName, memsize size)
{
   m_memsize = size;

#if defined(__ANDROID__)

   auto pszAndroidName = android_shared_memory_name(pszName);

   int fd = -1;

   {

      std::lock_guard<std::mutex> synchronouslock(g_sharedmemoryMutex);

      auto iterator = g_sharedmemoryMap.find(pszAndroidName);

      if (iterator == g_sharedmemoryMap.end()
         || iterator->second.m_fd < 0
         || iterator->second.m_memsize != size)
      {

         throw ::exception(error_resource);

      }

      fd = dup(iterator->second.m_fd);

      if (fd < 0)
      {

         throw ::exception(error_resource);

      }

      iterator->second.m_iReferenceCount++;

   }

   m_fd = fd;
   m_strName = pszAndroidName;

#else
   
   m_fd = shm_open(pszName, O_RDWR, 0666);
   
   if (m_fd < 0)
   {
      throw ::exception(error_resource);
      
   }

#endif
   
   m_p = mmap(
              nullptr,
              size,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              m_fd,
              0);
   
   if(m_p == MAP_FAILED)
   {

      m_p = nullptr;

      Close();

      throw ::exception(error_resource);
   }
}



   void shared_memory::Close()
   {
      
      
      if (m_p && m_p != MAP_FAILED)
      {
         munmap(m_p, m_memsize);
         m_p = nullptr;
      }
      
      if (m_fd >= 0)
      {
         close(m_fd);
         m_fd = -1;
      }

#if defined(__ANDROID__)

      if (m_strName.has_character())
      {

         std::lock_guard<std::mutex> synchronouslock(g_sharedmemoryMutex);

         auto iterator = g_sharedmemoryMap.find(m_strName.c_str());

         if (iterator != g_sharedmemoryMap.end())
         {

            iterator->second.m_iReferenceCount--;

            if (iterator->second.m_iReferenceCount <= 0)
            {

               close_shared_memory_entry(iterator->second);

               g_sharedmemoryMap.erase(iterator);

            }

         }

         m_strName.empty();

      }

#endif
      
   }


} // namespace posix
