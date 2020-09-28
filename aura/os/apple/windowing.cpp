//
//  windowing.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 24/09/20.
//

#include "framework.h"
#include "windowing.h"


iptr get_window_long_ptr(oswindow_data * oswindow, int iIndex)
{

   return oswindow->get_window_long_ptr(iIndex);

}


iptr set_window_long_ptr(oswindow_data * oswindow, int iIndex, iptr i)
{

   return oswindow->set_window_long_ptr(iIndex, i);
   
}



