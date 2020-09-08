#pragma once


CLASS_DECL_AQUA int __node_is_debugger_attached();

CLASS_DECL_AQUA int is_debugger_attached();


CLASS_DECL_AQUA bool EnforceFilter( bool bEnforce );

// WriteMemory function
//
// This function writes the specified sequence of bytes from
// the source memory into the target memory. In addition, the function
// modifies virtual memory protection attributes of the target memory page
// to make sure that it is writeable.
//
CLASS_DECL_AQUA bool WriteMemory( BYTE* pTarget, const BYTE* pSource, u32 size );



