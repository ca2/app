//
// Created by camilo on 2025-08-31 02:16 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/constant/message.h"
#include "acme/prototype/prototype/memory.h"


namespace platform
{


   class CLASS_DECL_ACME message : virtual public ::particle
   {
   public:


      enum_message m_emessage;

      ::i64 m_llWparam;
      ::i64 m_llLparam;
      ::memory m_memory;


      message();
      ~message() override;


      void initialize_message(enum_message emessage, ::i64 llWparam = 0,
                                          ::i64 llLparam = 0, const ::block &block = {});


   };


} // namespace platform



