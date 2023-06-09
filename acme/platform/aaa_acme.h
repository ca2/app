//
//  base_static_start.h
//  acme
//
//  Created by camilo on 14/04/2021. 00:30 BRT <3TBS_!!
//
#pragma once

//
//namespace acme
//{


   class CLASS_DECL_ACME main
   {
   public:


      pointer_array < ::particle >* m_pelementaddraReleaseOnEnd = nullptr;

      class ::time                     m_timeStart;
      
      ::pointer < ::sub_system >       m_psubsystem;

#if defined(WINDOWS)  && defined(UNICODE)
      main(int argc, wchar_t* wargv[], wchar_t* wenvp[]);
#else
      main(int argc, platform_char** argv, platform_char** envp);
#endif
      ~main();

      
      void common_construct();


      class ::time start_nanosecond();


   };


//} // namespace acme



