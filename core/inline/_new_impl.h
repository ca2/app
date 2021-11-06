#pragma once

#if !defined(NO_AURA_MEMORY_MANAGEMENT)


void MEMORY_DECL operator delete(void * p, size_t n) del_throw_spec
{

   ::operator delete(p);

}


#endif



