#include "framework.h"


namespace exception
{


   class engine * g_pengine = nullptr;


   CLASS_DECL_ACME class ::exception::engine & engine()
   {

      return *g_pengine;

   }


} // namespace exception


namespace exception
{


   engine::engine()
   {

   }


   engine::~engine()
   {


   }


   void engine::reset()
   {


   }


} // namespace excpetion



