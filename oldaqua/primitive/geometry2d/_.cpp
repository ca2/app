#include "framework.h"



CLASS_DECL_AQUA double d_distance(const point & point1, const point & point2)
{

   return sqrt((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));

}


