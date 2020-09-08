#include "framework.h"


class ::exception_engine * g_pexceptionengine = nullptr;


namespace exception
{

   CLASS_DECL_AQUA class ::exception_engine & engine()
   {

      return *g_pexceptionengine;

   }

} // namespace exception


//namespace exception
//{



   exception_engine::exception_engine()
   {

   }


   exception_engine::~exception_engine()
   {


   }


   void exception_engine::reset()
   {


   }


//}
