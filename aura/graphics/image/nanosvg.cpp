#include "framework.h"
#include "nanosvg.h"
#include "nanosvgrast.h"
#include "image.h"
#include "imaging.h"
////#include "acme/exception/exception.h"


void nsvg_rasterizer_set_output_format(NSVGrasterizer * prasterizer, ::i32 iRedLower);


::f64 get_default_screen_dpi();


namespace image
{


   bool imaging::nanosvg(::image::image * pimage, void * pNSVGimage, ::i32 iRedLower)
   {

      NSVGrasterizer * rast = nsvgCreateRasterizer();

      if (rast == nullptr)
      {

         informationf("Could not init rasterizer.\n");

         return false;

      }

      nsvg_rasterizer_set_output_format(rast, iRedLower);

      ::i32 w = (::i32)pimage->width();

      ::i32 h = (::i32)pimage->height();

      ::image32_t * pdata = nullptr;

      ::i32 iScan = 0;

      auto psvgimage = (NSVGimage *)pNSVGimage;

      {

         pdata = pimage->image32();

         iScan = pimage->m_iScan;

         nsvgRasterize(rast, psvgimage, 0, 0, 1, (::u8 *)pdata, w, h, iScan);

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


   void image::nanosvg(char_pointer pszXml, ::f64 dDpi)
   {

      if (dDpi <= 0.0)
      {

         dDpi = 300.0;

      }

      NSVGimage * psvgimage;

      psvgimage = nsvgParse(pszXml, "px", 300.0f);

      if (::is_null(psvgimage))
      {

         throw ::exception(error_null_pointer);

      }

      try
      {

         map();

         imaging()->nanosvg(this, psvgimage, m_iRedLower);

         unmap();

         //return true;

      }
      catch (...)
      {

      }

      nsvgDelete(psvgimage);

      //return false;

   }


   void image::create_nanosvg(char_pointer pszXml, ::f64 dDpi)
   {

      NSVGimage * psvgimage;

      if (dDpi <= 0.0)
      {

         dDpi = get_default_screen_dpi();

      }

      psvgimage = nsvgParse(pszXml, "px", (::f32)dDpi);

      if (::is_null(psvgimage))
      {

         throw ::exception(error_null_pointer);

      }

      try
      {

         create({ (::i32)psvgimage->width, (::i32)psvgimage->height });

         map();

         imaging()->nanosvg(this, psvgimage, m_iRedLower);

         unmap();

      }
      catch (...)
      {

      }

      nsvgDelete(psvgimage);

      //return true;

   }


} // namespace image




