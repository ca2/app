#pragma once


#if !defined(WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(__ANDROID__) && !defined(FREEBSD) && !defined(OPENBSD)

namespace std { enum class align_val_t : std::size_t {}; }

#endif

