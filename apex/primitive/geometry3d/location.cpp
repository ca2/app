//
//  geometry3d_location.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 19/06/19.
//

#include "framework.h"

locationd locationd::rotate(locationd point)
{
   
   locationd point1;
   point1.x = x *cos(point.z) - y * sin(point.z) ;
   point1.y = x *sin(point.z) + y * cos(point.z) ;
   point1.z = z;
   
   locationd point2;
   point2.y = point1.y*cos(point.x) - point1.z * sin(point.x) ;
   point2.z = point1.y *sin(point.x) + point1.z * cos(point.x) ;
   point2.x = point1.x;
   
   locationd p3;
   p3.z = point2.z *cos(point.y) - point2.x * sin(point.y) ;
   p3.x = point2.z *sin(point.y) + point2.x * cos(point.y) ;
   p3.y = point2.y;
   
   return p3;
}
