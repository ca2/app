// Refactoring device_lock by camilo by 2021-09-08 16:25 BRT <3ThomasBS__!!
#pragma once


namespace draw2d
{
   
   
   class CLASS_DECL_AURA device_lock
   {
   public:
   
   
      ::matter *              m_pmatter;
   
      
      device_lock(::matter * pmatter);
      ~device_lock();
   
   
   };


} // namespace draw2d



