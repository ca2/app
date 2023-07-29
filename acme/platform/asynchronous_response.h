//
//  nano_http_response.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 23:16
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once

template < typename PAYLOAD >
n   class http_response :
      virtual public ::particle
   {
   public:
      
      ::property_set    m_set;
      
      memory            m_memory;
      
      bool              m_bTimeout;
   
   };


