//
//  exchange.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/10/20.
//  Copyright © 2020 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

class CLASS_DECL_ACME string_exchange
{
public:
   
   mutable string * m_pstr;
   
   string_exchange(string & str) :m_pstr(&str){}
   
   
   
   string_exchange &operator = (const ::string & str )const{*m_pstr = str; return (string_exchange &)(*this);}
   
   
   
   
   
};
