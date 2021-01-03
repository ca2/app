#pragma once


CLASS_DECL_ACME int __node_is_debugger_attached();

CLASS_DECL_ACME int is_debugger_attached();

CLASS_DECL_ACME bool EnforceFilter( bool bEnforce );

CLASS_DECL_ACME bool WriteMemory( byte* pTarget, const byte* pSource, u32 size );



