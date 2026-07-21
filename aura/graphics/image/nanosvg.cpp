#include "framework.h"
#include "nanosvg.h"
#include "nanosvgrast.h"
#include "image.h"
#include "imaging.h"
#include "load_image.h"
////#include "acme/exception/exception.h"


void nsvg_rasterizer_set_output_format(NSVGrasterizer * prasterizer, ::i32 iRedLower);


::f64 get_default_screen_dpi();


namespace image
{


   bool imaging::nanosvg(::image::load_image * ploadimage, void * pNSVGimage, ::i32 iRedLower, ::i32 iWidth, ::i32 iHeight)
   {

      NSVGrasterizer * rast = nsvgCreateRasterizer();

      if (rast == nullptr)
      {

         informationf("Could not init rasterizer.\n");

         return false;

      }

      nsvg_rasterizer_set_output_format(rast, iRedLower);

      ::i32 w = (::i32)iWidth;

      ::i32 h = (::i32)iHeight;

      ::image32_t * pdata = nullptr;

      ::i32 iScan = 0;

      auto psvgimage = (NSVGimage *)pNSVGimage;

      {

         pdata = ploadimage->defer_image32({w, h}, &iScan);

         nsvgRasterize(rast, psvgimage, 0, 0, 1, (::u8 *)pdata, w, h, iScan);

         ploadimage->on_load_image(pdata, {w, h}, iScan);

         //, const ::e_status &estatus

#ifdef UNIVERSAL_WINDOWS

         ::u8 * pimage32 = (::u8 *)pimage->image32();

         for (::collection::index iLine = 0; iLine < h; iLine++)
         {

            ::u8 * pline = &pimage32[iLine * iScan];

            for (::collection::index x = 0; x < w; x++)
            {

               ::u8 b = pline[0];

               pline[0] = pline[2];

               pline[2] = b;

               pline += 4;


            }

         }

#endif

         //#ifdef __APPLE__
         //
         //      ::draw2d::vertical_swap(pimage->m_pdata);
         //
         //#endif
         //
      }

      nsvgDeleteRasterizer(rast);

      return true;

   }


   void load_image::nanosvg(char_pointer pszXml, ::i32 iRedLower, ::f64 fDpi)
   {

      if (fDpi <= 0.0)
      {

         fDpi = get_default_screen_dpi();

      }

      NSVGimage * psvgimage;

      psvgimage = nsvgParse(pszXml, "px", fDpi);

      if (::is_null(psvgimage))
      {

         throw ::exception(error_null_pointer);

      }

      try
      {

         //map();

         auto w = (::i32) psvgimage->width;

         auto h = (::i32) psvgimage->height;

         imaging()->nanosvg(this, psvgimage, iRedLower, w, h);

         //unmap();

         //return true;

      }
      catch (...)
      {

      }

      nsvgDelete(psvgimage);

      //return false;

   }


   //void load_image::create_nanosvg(char_pointer pszXml, ::i32 iRedLower, ::i32 width, ::i32 height)
   //{

   //   NSVGimage * psvgimage;

   //   if (fDpi <= 0.0)
   //   {

   //      fDpi = get_default_screen_dpi();

   //   }

   //   psvgimage = nsvgParse(pszXml, "px", (::f32)fDpi);

   //   if (::is_null(psvgimage))
   //   {

   //      throw ::exception(error_null_pointer);

   //   }

   //   try
   //   {

   //      //create({ (::i32)psvgimage->width, (::i32)psvgimage->height });

   //      //map();

   //      auto ploadimage = create_newø<::image::load_image>();

   //      ploadimage->init

   //      imaging()->nanosvg(this, psvgimage, iRedLower, (::i32) psvgimage->width, (::i32)psvgimage->height);

   //      //unmap();

   //   }
   //   catch (...)
   //   {

   //   }

   //   nsvgDelete(psvgimage);

   //   //return true;

   //}


} // namespace image




