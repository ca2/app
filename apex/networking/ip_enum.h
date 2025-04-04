/*
Module : IPENUM.H
Purpose: Interface for an apex API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (ca) 1998 by PJ Naughter.


*/
#pragma once


//#include "address.h"
////#include "acme/prototype/prototype/object.h"


namespace networking
{


   class CLASS_DECL_APEX ip_enum :
      virtual public ::object
   {
   public:



      ip_enum();
      ~ip_enum() override;


      virtual ::collection::count enumerate(pointer_array < ::networking::address > & ipa);


   };


   typedef ::pointer<ip_enum>ip_enum_pointer;


} // namespace net



