//
// Created by camilo on 2024-09-24 23:06 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/object.h"


namespace nano
{


   namespace graphics
   {


      class CLASS_DECL_ACME icon :
         virtual public ::nano::graphics::object
      {
      public:


         //::memory_file_pointer      m_pfile;


         icon();
         ~icon() override;


         virtual ::i32_size size() const;


         virtual void load_image_from_file(::file::file * pfile);
         virtual void load_image_file(const ::block & block);

   
      };


   } // graphics


} // nano



