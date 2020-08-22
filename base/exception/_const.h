#pragma once



#define callstack_DEFAULT_SKIP_TRIGGER (-2)

#define SKIP_callstack (-1)


#if defined(APPLE)

#define callstack_DEFAULT_SKIP 3

#elif defined(ANDROID)

#define callstack_DEFAULT_SKIP 4

#else

#define callstack_DEFAULT_SKIP 3

#endif

