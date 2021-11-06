#include "framework.h"
#include "acme/operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


critical_section::construct * critical_section::s_pconstruct = (critical_section::construct *)&::pthread_recursive_mutex_init;
critical_section::destruct * critical_section::s_pdestruct = (critical_section::destruct *)&::pthread_mutex_destroy;
critical_section::enter * critical_section::s_penter = (critical_section::enter *)::pthread_mutex_lock;
critical_section::exit * critical_section::s_pexit = (critical_section::exit *)::pthread_mutex_unlock;


#else


critical_section::construct * critical_section::s_pconstruct = (critical_section::construct *)&::InitializeCriticalSection;
critical_section::destruct * critical_section::s_pdestruct = (critical_section::destruct *)&::DeleteCriticalSection;
critical_section::enter * critical_section::s_penter = (critical_section::enter *)::EnterCriticalSection;
critical_section::exit * critical_section::s_pexit= (critical_section::exit *)::LeaveCriticalSection;


#endif



