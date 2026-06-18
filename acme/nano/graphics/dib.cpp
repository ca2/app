//
//  dib.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  Created by camilo on 2026-06-06 00:43 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "dib.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/filesystem/file/memory_file.h"


namespace nano
{


   namespace graphics
   {

   
      dib::dib()
      {

      }

      
      dib::~dib()
      {


      }

      ::i32_size dib::size() const
      {
      
         return{};

      }

      
      void dib::create_image(const ::i32_size & size)
      {
      
         throw ::interface_only();
      
      }
   
      image * dib::get_image2()
      {
         
         throw ::interface_only();
         
         return nullptr;
         
      }
   
      
      image * dib::fetch_image()
      {
         
         throw ::interface_only();
         
         return nullptr;
         
      }

      
      context * dib::get_context()
      {
      
         throw ::interface_only();
         
         return nullptr;
         
      }

   
      void * dib::get_buffer()
      {
         
         throw ::interface_only();
         
         return nullptr;
         
      }
   
   
      void dib::load_image_from_file(::file::file * pfile)
      {

         auto memory = pfile->as_memory();

         load_image_file(memory.data(), memory.size());

      }


      void dib::load_image_file(const void *p, memsize size)
      {

         auto pfile = create_memory_file({p, size});

         load_image_from_file(pfile);

      }
   

   } // graphics


} // nano



