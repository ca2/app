//#include "operating_system/config.h"
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#ifdef WINDOWS
//#pragma warning(disable:4101)
//#endif


#include "acme/_start.h"


#include "nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"


void nsvg_rasterizer_set_output_format(NSVGrasterizer * prasterizer, int iRedLower)
{

   prasterizer->m_iRedLower = iRedLower;

}



