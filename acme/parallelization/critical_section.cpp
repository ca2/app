#include "framework.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


critical_section::critical_section() { ::pthread_recursive_mutex_init((pthread_mutex_t *)aligned_this()); }
critical_section::~critical_section() { ::pthread_mutex_destroy((pthread_mutex_t *)aligned_this()); }


void critical_section::lock() { ::pthread_mutex_lock((pthread_mutex_t *)aligned_this()); }
void critical_section::unlock() { ::pthread_mutex_unlock((pthread_mutex_t*)aligned_this()); }


#else


#include "acme/_operating_system.h"


critical_section::critical_section() { ::InitializeCriticalSection((CRITICAL_SECTION *)aligned_this()); }
critical_section::~critical_section() { ::DeleteCriticalSection((CRITICAL_SECTION *)aligned_this()); }


void critical_section::lock() { ::EnterCriticalSection((CRITICAL_SECTION *)aligned_this()); }
void critical_section::unlock() { ::LeaveCriticalSection((CRITICAL_SECTION*)aligned_this()); }


#endif



