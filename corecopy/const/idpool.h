#pragma once


namespace core
{

   class CLASS_DECL_CORE idpool :
      public ::idpool
   {
   public:


      

      idpool();



   };


} // namespace core


#undef __id
#define __id(x) (((::core::idpool *)::idpool::g_p)->x)



