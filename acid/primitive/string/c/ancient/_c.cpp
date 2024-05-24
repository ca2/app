//
//  _c.c
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 07/11/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "_c.h"
#include <string.h>


char * libc_strdup(const char * psz)
{
   
   return strdup(psz);
   
}



