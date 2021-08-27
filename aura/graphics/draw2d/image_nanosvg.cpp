#include "framework.h"
#include "third/nanosvg/nanosvg.h"
#include "third/nanosvg/nanosvgrast.h"

double get_default_screen_dpi();

bool nanosvg(::image * pimage, NSVGimage * psvgimage)
{

   NSVGrasterizer * rast = nsvgCreateRasterizer();

   if (rast == nullptr)
   {

      output_debug_string("Could not init rasterizer.\n");

      return false;

   }

   int w = (int)pimage->width();

   int h = (int)pimage->height();

   ::color32_t * pdata = nullptr;

   int iScan = 0;

   {

      pdata = pimage->colorref();

      iScan = pimage->m_iScan;

      nsvgRasterize(rast, psvgimage, 0, 0, 1, (unsigned char *)pdata, w, h, iScan);

#ifdef _UWP

      u8 * point = (u8 *)pimage->colorref();

      for (index iLine = 0; iLine < h; iLine++)
      {

         u8 * pline = &point[iLine * iScan];

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


bool image::nanosvg(char * pszXml, double dDpi)
{

   if (dDpi <= 0.0)
   {

      dDpi = 300.0;

   }

   NSVGimage * psvgimage;

   psvgimage = nsvgParse(pszXml, "px", 300.0f);

   if (::is_null(psvgimage))
   {

      return false;

   }

   try
   {

      map();

      ::nanosvg(this, psvgimage);

      unmap();

      return true;

   }
   catch (...)
   {

   }

   nsvgDelete(psvgimage);

   return false;

}


bool image::create_nanosvg(char * pszXml, double dDpi)
{

   NSVGimage * psvgimage;

   if (dDpi <= 0.0)
   {

      dDpi = get_default_screen_dpi();

   }

   psvgimage = nsvgParse(pszXml, "px", (float)dDpi);

   if (::is_null(psvgimage))
   {

      return false;

   }

   try
   {

      if (create({ (int)psvgimage->width, (int)psvgimage->height }))
      {

         map();

         ::nanosvg(this, psvgimage);

         unmap();

      }

   }
   catch (...)
   {

   }

   nsvgDelete(psvgimage);

   return true;

}

