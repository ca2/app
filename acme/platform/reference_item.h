//
//  reference_count_debug.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//  More work on 2023-11-22 22:21 <3ThomasBorregaardSorensen!!
//
#pragma once
#if   REFERENCING_DEBUGGING

class reference_item_array;


CLASS_DECL_ACME ::raw::index new_reference_item_serial();


class CLASS_DECL_ACME reference_item
{
public:


   ::reference_item_array *      m_pitema;
   int                           m_iStep;
   ::raw::index                       m_iSerial = ::new_reference_item_serial();
   reference_referer *           m_preferer = ::allocator::pop_referer();
   ::string                      m_strDebug;
   ::string                      m_strDebugDecrement;
   //bool                          m_bOn;


   reference_item(::reference_item_array * pitema);
   ~reference_item();


};


#endif

