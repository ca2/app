//
//  audio_core_aligned.h
//  audio_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 05/11/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


#undef new
template < typename TYPE >
class aligned
{
public:
   
   TYPE * m_p;
   
   aligned()   { m_p = (TYPE *) aligned_memory_alloc(sizeof(TYPE)); new(m_p) TYPE(); }
   ~aligned()  { ((TYPE *)m_p)->~TYPE(); memory_free(m_p); }
   
   TYPE * operator ->()
   {
      return m_p;
   }
   
   operator TYPE * ()
   {
      return m_p;
   }
   
   TYPE & operator * ()
   {
      return *m_p;
   }
   
   
};
#define new DEBUG_NEW