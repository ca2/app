#pragma once


#include "aura/_.h"
#include "aura/gpu/gpu/_.h"


#ifdef _APP_SHADER_LIBRARY
#define CLASS_DECL_APP_SHADER  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SHADER  CLASS_DECL_IMPORT
#endif


namespace app_shader
{


   class application;
   class main_window;


} // namespace flag


namespace opengl
{


   class opengl;
   class shader;
   class buffer;
   class program;


} // namespace opengl


#include "render.h"


#include "application.h"



