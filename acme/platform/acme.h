//
//  base_static_start.h
//  acme
//
//  Created by camilo on 14/04/2021. 00:30 BRT <3TBS_!!
//
#pragma once


namespace acme
{


   class CLASS_DECL_ACME acme
   {
   public:


      class ::time         m_timeStart;
      
      ::sub_system *       m_psubsystem = nullptr;


      acme();
      ~acme();


      class ::time start_nanosecond();


   };


} // namespace acme



