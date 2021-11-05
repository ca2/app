#include "framework.h"

//
//namespace exception
//{


   class exception_engine * g_pexceptionengine = nullptr;


   CLASS_DECL_ACME class ::exception_engine & exception_engine()
   {

      return *g_pexceptionengine;

   }

//
//} // namespace exception
//
//
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

//
//} // namespace excpetion
//
//

