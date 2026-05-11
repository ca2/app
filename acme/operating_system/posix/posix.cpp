//
//  posix.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!!
//





namespace operating_system
{


   CLASS_DECL_ACME ::error_code last_error_code()
   {
   
      return { e_error_code_type_errno, (::i64) errno };
   
   }


} // namespace operating_system



