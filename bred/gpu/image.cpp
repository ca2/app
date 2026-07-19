#include "framework.h"
#include "image.h"
#include "context.h"
#include "context_lock.h"
#include "renderer.h"
#include "texture.h"


namespace gpu
{


   image::image()
   {

   }


   image::~image()
   {

      destroy();

   }


   ::draw2d::graphics * image::get_graphics() const
   {

      return _get_graphics();

   }


   ::gpu::texture * image::gpu_texture() const
   {

      return m_pgputexture;

   }


   void image::initialize_gpu_image(
      ::gpu::context * pgpucontext,
      const ::i32_size & size)
   {

      if (!pgpucontext || size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      ::gpu::context_lock contextlock(pgpucontext);

      auto pgpurenderer = pgpucontext->get_gpu_renderer();
      auto pgputexture = pgpurenderer->create_image_texture(size, false);

      if (!pgputexture)
      {

         throw ::exception(error_failed, "Failed to create GPU image texture.");

      }

      m_pgputexture = pgputexture;
      m_size = size;
      m_sizeRaw = size;
      m_point.clear();
      m_iScan = 0;
      m_pimage32 = nullptr;
      m_pimage32Raw = nullptr;
      set_ok_flag();

   }


   void image::destroy()
   {

      ::image::image::destroy();
      m_pgputexture.release();

   }


   void image::map(bool) const
   {

      throw ::not_implemented();

   }


   void image::unmap() const
   {

      throw ::not_implemented();

   }


} // namespace gpu
