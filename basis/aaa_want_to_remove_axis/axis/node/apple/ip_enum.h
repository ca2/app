//
//  apple_ip_enum.hpp
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/17.
//

/*
 Module : IPENUM.H
 Purpose: Interface for an ca2 API class wrapper for IP address enumeration
 Created: PJN / 21-04-1998
 History: None
 
 Copyright (c) 1998 by PJ Naughter.
 
 
 */


namespace apple
{
   
   
   class CLASS_DECL_AXIS ip_enum :
   virtual public ::net::ip_enum
   {
   public:
      
      
      ip_enum();
      virtual ~ip_enum();
      
      
      virtual ::count enumerate(string_array & stra);
      
      
   };
   
   
} // namespace apple





