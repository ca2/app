#include "framework.h"
#include "nanosvg/nanosvg.h"
#include "nanosvg/nanosvgrast.h"
#include "image.h"
#include "acme/exception/exception.h"


void nsvg_rasterizer_set_output_format(NSVGrasterizer * prasterizer, int iRedLower);


double get_default_screen_dpi();


bool nanosvg(::image * pimage, NSVGimage * psvgimage, int iRedLower)
{

   NSVGrasterizer * rast = nsvgCreateRasterizer();

   if (rast == nullptr)
   {

      output_debug_string("Could not init rasterizer.\n");

      return false;

   }

   nsvg_rasterizer_set_output_format(rast, iRedLower);

   int w = (int)pimage->width();

   int h = (int)pimage->height();

   ::color32_t * pdata = nullptr;

   int iScan = 0;

   {

      pdata = pimage->colorref();

      iScan = pimage->m_iScan;

      nsvgRasterize(rast, psvgimage, 0, 0, 1, (unsigned char *)pdata, w, h, iScan);

#ifdef _UWP

      u8 * pcolorref = (u8 *)pimage->colorref();

      for (index iLine = 0; iLine < h; iLine++)
      {

         u8 * pline = &pcolorref[iLine * iScan];

         for (index x = 0; x < w; x++)
         {

            byte b = pline[0];

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


void image::nanosvg(char * pszXml, double dDpi)
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

      ::nanosvg(this, psvgimage, m_iRedLower);

      unmap();

      //return true;

   }
   catch (...)
   {

   }

   nsvgDelete(psvgimage);

   //return false;

}


void image::create_nanosvg(char * pszXml, double dDpi)
{

   NSVGimage * psvgimage;

   if (dDpi <= 0.0)
   {

      dDpi = get_default_screen_dpi();

   }

   psvgimage = nsvgParse(pszXml, "px", (float)dDpi);

   if (::is_null(psvgimage))
   {

      throw ::exception(error_null_pointer);

   }

   try
   {

      create({ (int)psvgimage->width, (int)psvgimage->height });

      map();

      ::nanosvg(this, psvgimage, m_iRedLower);

      unmap();

   }
   catch (...)
   {

   }

   nsvgDelete(psvgimage);

   //return true;

}

