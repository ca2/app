#pragma once





#define __BEGIN_RELEASE_TIME(library) \
extern "C" const char * library ## _release_time() \
{ \
const char * pszReleaseTime = \


#define __END_RELEASE_TIME() \
;
return pszReleaseTime; \
}



