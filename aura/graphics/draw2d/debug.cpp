#include "framework.h"


dump_context & operator<<(dump_context & dumpcontext,const ::size_i32 & size)
{
   dumpcontext << "(" << size.cx << " x " << size.cy << ")";
   
   return dumpcontext;
   
}

dump_context & operator<<(dump_context & dumpcontext,const ::point_i32 & point)
{
   dumpcontext << "(" << point.x << ", " << point.y << ")";
   return dumpcontext;
}

dump_context & operator<<(dump_context & dumpcontext,const ::rectangle_i32 & rectangle)
{
   dumpcontext << "(L " << rectangle.left << ", T " << rectangle.top << ", R " <<
          rectangle.right << ", B " << rectangle.bottom << ")";
   return dumpcontext;
}


