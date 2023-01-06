//
//  transfer.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 31/05/22.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


template < typename TYPE >
inline
non_reference < TYPE > && transfer(TYPE && t)
{

   return static_cast< non_reference< TYPE > && >(t);

}


template < typename TYPE >
inline
const non_reference < TYPE > &&transfer(const TYPE && t)
{

   return static_cast < const non_const < non_reference < TYPE > > && >(t);

}

template < typename TYPE >
inline
const non_reference < TYPE > * && transfer(TYPE * const & t)
{

   return (const non_reference < non_const < TYPE > > * &&)((const non_const < TYPE > * &) t);

}




