#pragma once


// Experimental at ca2 Framework
// Selecting this define, should disable IME
#undef ENABLE_TEXT_SERVICES_FRAMEWORK



#ifdef _output_type_staticlibrary

#ifndef CUBE

#define CUBE
#define STATIC_CUBE

#else

#error "CUBE already defined"

#endif

#endif



