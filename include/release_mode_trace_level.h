#pragma once

// Release builds default to warnings. Temporarily set this to
// e_trace_level_information when detailed diagnostics are needed; only the
// translation unit that resolves the process trace level includes this file.
#ifndef CA2_RELEASE_MODE_TRACE_LEVEL
#define CA2_RELEASE_MODE_TRACE_LEVEL e_trace_level_information
#endif
