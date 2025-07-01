// Created by camilo on 2025-06-30 22:42 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "command_buffer.h"


namespace gpu_opengl
{


   command_buffer::command_buffer()
   {


   }


   command_buffer::~command_buffer()
   {


   }


   void command_buffer::draw(int a)
   {

      glDrawArrays(GL_TRIANGLES, 0, a);
      GLCheckError("");

   }


} // namespace gpu_opengl



