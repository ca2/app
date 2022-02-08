//
//  _.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 21/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"



//
//
//
//
//CLASS_DECL_ACME void destroy_pointer(int_handle i)
//{
//
//   if(i >= 0)
//   {
//
//      ::close(i.m_i);
//
//   }
//
//}


CLASS_DECL_ACME void destroy_pointer(FILE * p)
{

   if(::is_set(p))
   {

      fclose(p);

   }

}



