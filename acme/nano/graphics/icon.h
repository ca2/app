//
// Created by camilo on 2024-09-24 23:06 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "object.h"


namespace nano {
namespace graphics {

class icon :
virtual public ::nano::graphics::object{
  public:

    //::memory_file_pointer      m_pfile;

    icon();
    ~icon();

   virtual ::size_i32 size() const;

   virtual void load_image_from_file(::file::file * pfile);
   virtual void load_image_file(const void *p, memsize size);

};

} // graphics
} // nano


