//
// Created by camilo on 2024-09-24 23:16 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "icon.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/prototype/geometry2d/size.h"


namespace nano {
namespace graphics {

icon::icon()
{

}

   icon::~icon()
{


}

   ::int_size icon::size() const
{
return{};

}

   void icon::load_image_from_file(::file::file * pfile)
{

   auto memory = pfile->as_memory();

   load_image_file(memory.data(), memory.size());

}


   void icon::load_image_file(const void *p, memsize size)
{

   auto pfile = create_memory_file({p, size});

   load_image_from_file(pfile);

}
} // graphics
} // nano