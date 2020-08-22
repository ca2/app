#pragma once


#if !defined(WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)

namespace std { enum class align_val_t : std::size_t {}; }

#endif

