//
//  move.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 31/05/22.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once

template<class T>
struct erase_reference
{
   typedef T TYPE;
};

template<class T>
struct erase_reference<T &>
{
   typedef T TYPE;
};

template<class T>
struct erase_reference<T &&>
{
   typedef T TYPE;
};


template<class T>
inline
typename erase_reference<T>::TYPE &&move(T &&t)
{

   return (static_cast<typename erase_reference<T>::TYPE &&>(t));

}





