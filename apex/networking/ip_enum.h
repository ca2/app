/*
Module : IPENUM.H
Purpose: Interface for an apex API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (ca) 1998 by PJ Naughter.


*/
#pragma once


namespace net
{


   class CLASS_DECL_APEX ip_enum :
      virtual public ::object
   {
   public:



      ip_enum();
      virtual ~ip_enum();


      virtual ::count enumerate(array < ::net::address > & ipa);


   };


   typedef ___pointer < ip_enum > ip_enum_pointer;


} // namespace net



