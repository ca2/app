#pragma once
#include <stddef.h>

// This header is deliberately independent of framework allocation/logging.
#if defined(MEMORY_DIAGNOSTICS) && defined(_WIN32)
extern "C" {
void ca2_memory_diagnostics_allocate(void *p, size_t size, const char *annotation = nullptr);
void ca2_memory_diagnostics_free(void *p);
void ca2_memory_diagnostics_reallocate(void *old_p, void *new_p, size_t size, const char *annotation = nullptr);
__declspec(dllexport) void ca2_memory_diagnostics_snapshot();
}
#endif
