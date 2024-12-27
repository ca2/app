// From activation.h by camilo on 2024-12-27 05:53 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{


   class CLASS_DECL_ACME activation_token :
      virtual public ::particle
   {
   public:


      virtual bool matches(const activation_token * pactivationtoken) const;


   };


} // namespace user



