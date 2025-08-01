//
//  _c.c
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 07/11/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "_c.h"
#include <string.h>


char * libc_strdup(const_char_pointer  psz)
{
   
   return strdup(psz);
   
}



