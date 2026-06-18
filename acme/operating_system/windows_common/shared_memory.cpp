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
#include "acme/_operating_system.h"
//#define NOMINMAX
//#include <windows.h>

SharedMemory::SharedMemory()
{
   
   
}

bool SharedMemory::Create(const_char_pointer pszName, size_t size)
{
    m_size = size;

    HANDLE h = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        nullptr,
        PAGE_READWRITE,
        0,
        (DWORD)size,
        name);

    if (!h)
        return false;

    m_mapping = h;

    m_data = MapViewOfFile(
        h,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        size);

    return m_data != nullptr;
}

bool SharedMemory::Open(const_char_pointer pszName, size_t size)
{
    m_size = size;

    HANDLE h = OpenFileMappingA(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        name);

    if (!h)
        return false;

    m_mapping = h;

    m_data = MapViewOfFile(
        h,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        size);

    return m_data != nullptr;
}

///#endif


void SharedMemory::Close()
{

    if (m_data)
    {
        UnmapViewOfFile(m_data);
        m_data = nullptr;
    }

    if (m_mapping)
    {
        CloseHandle((HANDLE)m_mapping);
        m_mapping = nullptr;
    }

}

SharedMemory::~SharedMemory()
{
    Close();
}
