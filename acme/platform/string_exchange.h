//
//  exchange.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 02/10/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

class CLASS_DECL_ACME string_exchange
{
public:
   
   mutable string * m_pstr;
   
   string_exchange(string & str) :m_pstr(&str){}
   
   
   
   string_exchange &operator = (const ::string & str )const;
   
   
   
   
   
};
