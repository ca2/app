//#include "operating_system/config.h"
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#ifdef WINDOWS
//#pragma warning(disable:4101)
//#endif


//#include "acme/_start.h"

#include <nanosvg/nanosvg.h>
#define NANOSVGRAST_IMPLEMENTATION
#include <nanosvg/nanosvgrast.h>


// Preserve the parser's channel order throughout gradient calculations.
// The rasterizer's swap mode otherwise converts gradient stops twice.
void nsvg_rasterize(NSVGrasterizer * prasterizer, NSVGimage * pimage,
   unsigned char * pdata, int width, int height, int stride, int iRedLower)
{

   prasterizer->m_iRedLower = 1;
   nsvgRasterize(prasterizer, pimage, 0, 0, 1, pdata, width, height, stride);

   // This NanoSVG parser packs colors differently under WINDOWS and LINUX.
   // Convert once from that order to the requested destination buffer order.
#if defined(WINDOWS) || defined(LINUX)
   const bool bParserRedLower = false;
#else
   const bool bParserRedLower = true;
#endif

   if ((iRedLower != 0) != bParserRedLower)
   {

      for (int y = 0; y < height; ++y)
      {

         unsigned char * pixel = pdata + y * stride;

         for (int x = 0; x < width; ++x, pixel += 4)
         {

            const unsigned char red = pixel[0];
            pixel[0] = pixel[2];
            pixel[2] = red;

         }

      }

   }

}
