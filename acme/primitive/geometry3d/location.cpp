//
//  geometry3d_location.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 19/06/19.
//
#include "framework.h"
#include "_.h"


poled & poled::rotate(const poled & pole)
{
   
   poled pole1;
   pole1.x = x * cos(pole.z) - y * sin(pole.z) ;
   pole1.y = x * sin(pole.z) + y * cos(pole.z) ;
   pole1.z = z;
   
   poled pole2;
   pole2.y = pole1.y * cos(pole.x) - pole1.z * sin(pole.x) ;
   pole2.z = pole1.y * sin(pole.x) + pole1.z * cos(pole.x) ;
   pole2.x = pole1.x;
   
   pole1.z = pole2.z * cos(pole.y) - pole2.x * sin(pole.y) ;
   pole1.x = pole2.z * sin(pole.y) + pole2.x * cos(pole.y) ;
   pole1.y = pole2.y;
   
   return pole1;

}



