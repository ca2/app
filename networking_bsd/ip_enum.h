/*
Module : IPENUM.H
Purpose: Interface for an apex API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (ca) 1998 by PJ Naughter.


*/
#pragma once


namespace networking_bsd
{


   class CLASS_DECL_NETWORKING_BSD ip_enum :
      virtual public ::networking::ip_enum
   {
   public:



      ip_enum();
      ~ip_enum() override;


      ::count enumerate(__pointer_array(::networking::address) & ipa) override;


   };


   typedef ___pointer < ip_enum > ip_enum_pointer;


} // namespace net



