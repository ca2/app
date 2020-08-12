#include "framework.h"


dump_context & operator<<(dump_context & dumpcontext,const ::size & size)
{
   dumpcontext << "(" << size.cx << " x " << size.cy << ")";
   
   return dumpcontext;
   
}

dump_context & operator<<(dump_context & dumpcontext,const ::point & point)
{
   dumpcontext << "(" << point.x << ", " << point.y << ")";
   return dumpcontext;
}

dump_context & operator<<(dump_context & dumpcontext,const ::rect & rect)
{
   dumpcontext << "(L " << rect.left << ", T " << rect.top << ", R " <<
          rect.right << ", B " << rect.bottom << ")";
   return dumpcontext;
}


