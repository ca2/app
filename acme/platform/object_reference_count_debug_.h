//
//  object_reference_count_debug.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//  More work on 2023-11-22 12:47 <3ThomasBorregaardSorensen
//
#pragma once


//#include "simple_array.h"


#include "acme/primitive/collection/array.h"


struct object_reference_count_debug_item
{

   int                  m_iStep;
   ::particle*          m_preferer;
   ::string             m_strDebug;

};


class object_reference_count_debug
{
public:


   int m_iStep = 0;

   ::array < object_reference_count_debug_item > m_itema;


   object_reference_count_debug();
   ~object_reference_count_debug();


   void add(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {
      
      object_reference_count_debug_item item;

      item.m_iStep = m_iStep;
      item.m_preferer = pReferer;
      item.m_strDebug = pszObjRefDbg;
      
      m_itema.add(item);

   }


   bool erase(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      for (::index i = 0; i < m_itema.size(); i++)
      {

         if (m_itema[i].m_preferer == pReferer)
         {

            m_itema.erase_at(i);

            return true;

         }

      }

      return false;

   }


};




