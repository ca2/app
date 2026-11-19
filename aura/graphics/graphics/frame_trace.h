#pragma once

// Per-frame draw/layout diagnostics are opt-in. Set this to 3 in the build
// definitions for aura, berg and core to inspect every rendered frame.
// Operational diagnostics and warnings/errors remain enabled independently.
#ifndef AURA_FRAME_TRACE_LEVEL
#define AURA_FRAME_TRACE_LEVEL 0
#endif
