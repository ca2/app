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
virtual public ::particle
{
public:
   
   
   void*  m_data = nullptr;
   memsize m_size = 0;

#if defined(WINDOWS)
   void* m_mapping = nullptr;
#else
   int m_fd = -1;
#endif
   
   shared_memory();
   ~shared_memory();

    bool Create(const char* name, size_t size);
    bool Open(const char* name, size_t size);

    void* Data() const { return m_data; }
    memsize Size() const { return m_size; }

    void Close();

    

};
