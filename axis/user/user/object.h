// From design/text_format/user_object.h by camilo on
// 2022-09-04 00:14 <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/message/channel.h"


namespace user
{


   class CLASS_DECL_AXIS object :
      virtual public ::channel
   {
   public:


      object();
      ~object() override;


   };


} // namespace user



