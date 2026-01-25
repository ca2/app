//
//  _glad.cpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 23/01/26.
//
#include "framework.h"
#include "_gpu_opengl.h"

//#define GLAD_GLAPI_EXPORT
//#include <glad/glad.h>


void gl_insert_debug_message(const_char_pointer pszMessage)
{
   
   if(glDebugMessageInsert)
   {
      glDebugMessageInsert(
                           GL_DEBUG_SOURCE_APPLICATION,
                           GL_DEBUG_TYPE_OTHER,
                           0,
                           GL_DEBUG_SEVERITY_LOW,
                           -1,
                           pszMessage
                           );
   }
   else if(glDebugMessageInsertARB)
   {
      glDebugMessageInsertARB(
                              GL_DEBUG_SOURCE_APPLICATION_ARB,
                              GL_DEBUG_TYPE_OTHER_ARB,
                              0,
                              GL_DEBUG_SEVERITY_LOW_ARB,
                              -1,
                              pszMessage
                              );
   }
}

