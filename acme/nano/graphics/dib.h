//
//  dib.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  Created by camilo on 2026-06-06 00:42 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


namespace nano
{


   namespace graphics
   {

      
      class CLASS_DECL_ACME dib :
         virtual public ::particle
      {
      public:


//         void *                     m_p;
//         ::i32_size                 m_size;
//         ::i32                      m_iBytesPerRow;
//         
//         ::pointer < context >      m_pcgcontext;
//         ::pointer < image >        m_pcgimage;
//         

         dib();
         ~dib();

         virtual ::i32_size size() const;
         
         
         virtual void create_image(const ::i32_size & size);
         
         virtual ::nano::graphics::image * get_image2();
         virtual ::nano::graphics::image * fetch_image();
         virtual ::nano::graphics::context * get_context();
         virtual void * get_buffer();

         virtual void load_image_from_file(::file::file * pfile);
         virtual void load_image_file(const void *p, memsize size);
   
      };

   
   } // namespace graphics


} // namespace nano




