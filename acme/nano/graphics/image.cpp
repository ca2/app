//
//  image.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  Created by camilo on 2026-06-06 00:05 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "image.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/filesystem/file/memory_file.h"


namespace nano
{


   namespace graphics
   {

   
      image::image()
      {

      }

      
      image::~image()
      {


      }

      ::i32_size image::size() const
      {
      
         return{};

      }

      
      void image::create_image(const ::i32_size & size)
      {
      
         throw ::interface_only();
      
      }
   
   
      void * image::get_buffer()
      {
         
         throw ::interface_only();
         
         return nullptr;
         
      
      }
   
   
      void image::load_image_from_file(::file::file * pfile)
      {

         auto memory = pfile->as_memory();

         load_image_file(memory.data(), memory.size());

      }


      void image::load_image_file(const void *p, memsize size)
      {

         auto pfile = create_memory_file({p, size});

         load_image_from_file(pfile);

      }
   

   } // graphics


} // nano



