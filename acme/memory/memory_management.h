//Created by camilo on 2021-07-29 18:23 BRT <3ThomasBorregaardSørensen!!
#pragma once


typedef void* MEMORY_REALLOCATE(void* p, memsize nSize);
typedef MEMORY_REALLOCATE* pfnMEMORY_REALLOCATE;

typedef void MEMORY_FREE(void* p);
typedef MEMORY_FREE* pfnMEMORY_FREE;

struct memory_heap
{

   pfnMEMORY_REALLOCATE       m_pfnMemoryReallocate;
   pfnMEMORY_FREE             m_pfnMemoryFree;

};



struct memory_management
{

   memory_heap       m_heapa[10];

};


extern memory_management g_memorymanagement;




void initialize_memory_management();

