#pragma once


#define __BEGIN_RELEASE_TIME(library) \
namespace library { \
extern "C" release_time_for_project library ## _release_time() \
{ \
return ::platform::get()->as_release_time_for_project(\


#define __END_RELEASE_TIME() \
); \
} \
} // namespace ##library



