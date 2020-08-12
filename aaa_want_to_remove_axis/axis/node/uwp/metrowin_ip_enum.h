/*
Module : IPENUM.H idea only, all new implementation for WinRT using StackOverflow Reference
Purpose: Interface for an ca2 API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (ca) 1998 by PJ Naughter.  


*/


namespace uwp
{


   class CLASS_DECL_AXIS ip_enum :
      virtual public ::net::ip_enum
   {
   public:

      
      ip_enum(::object * pobject);
      virtual ~ip_enum();

      
      virtual ::count enumerate(string_array & stra);

   };


} // namespace uwp



