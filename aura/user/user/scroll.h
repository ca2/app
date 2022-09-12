#pragma once


#include "scroll_base.h"


namespace user
{


   template < typename BASE >
   class scroll :
      virtual public scroll_base,
      virtual public BASE
   {
   public:


      scroll()
      {
      }

      virtual ~scroll()
      {
      }

      virtual void install_message_routing(::channel* pchannel) override
      {

         ::user::scroll_base::install_message_routing(pchannel);
         BASE::install_message_routing(pchannel);

      }

   };


} // namespace user



