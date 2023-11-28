//
//  reference_count_debug.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//  More work on 2023-11-22 22:21 <3ThomasBorregaardSorensen!!
//
#pragma once


class reference_item_array;


class CLASS_DECL_ACME reference_item
{
public:


   ::reference_item_array *      m_pitema;
   int                           m_iStep;
   reference_referer             m_referer;
   ::string                      m_strDebug;
   ::string                      m_strDebugDecrement;
   bool                          m_bOn;


   reference_item(::reference_item_array * pitema);
   ~reference_item();


};




