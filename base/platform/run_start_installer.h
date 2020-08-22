#pragma once


namespace aura
{


   class run_start_installer :
      virtual public ::object
   {
   public:


      virtual void run_start_install(const char * pszInstall) = 0;


   };



} // namespace aura