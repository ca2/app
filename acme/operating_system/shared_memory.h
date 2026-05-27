//
//  shared_memory.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2025-05-11
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!!
//
#pragma once


class shared_memory :
public MEMORY,
virtual public ::subparticle
{
public:
   
   
//    void*  m_data = nullptr;
//    memsize m_size = 0;

// #if defined(WINDOWS)
//    void* m_mapping = nullptr;
// #else
//    ::i32 m_fd = -1;
// #endif
   
   shared_memory();
   ~shared_memory();

   virtual bool CreateSharedMemory(const_char_pointer pszName, memsize size);
   virtual bool OpenSharedMemory(const_char_pointer pszName, memsize size);

   //virtual void* Data() const ;
   //virtual memsize Size() const ;

   virtual void Close();

    

};
