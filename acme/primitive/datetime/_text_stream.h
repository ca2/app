//
//  _text_stream.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 27/06/2023.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once

// template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const ::earth::time & time)
{

   ::string strTime;
   
   strTime.format("%04d-%02d-%02d %02d:%02d:%02d",
              time.year(),
              time.month(),
              time.day(),
              time.hour(),
              time.minute(),
              time.second());
   
   return textstream << strTime;

}
