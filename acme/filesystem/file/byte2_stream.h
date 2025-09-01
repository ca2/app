//
// Created by camilo on 2025-08-31 17:12 <3ThomasBorregaarSorensen!!
//
#pragma once


#include "file.h"
#include "stream.h"
#include "acme/prototype/prototype/memory.h"


//// template < typename FILE >
class CLASS_DECL_ACME byte2_stream :
virtual public stream_base
{
public:


   ::file_pointer          m_pfile;


   byte2_stream();
   byte2_stream(const ::block & block);
   byte2_stream(const ::file_pointer & pfile);
   ~byte2_stream() override;


   byte2_stream & operator >>(int & i);
   byte2_stream & operator << (int i);



};


class CLASS_DECL_ACME input_byte2_stream :
   virtual public byte2_stream
{
public:



   input_byte2_stream(const ::block & block);
   ~input_byte2_stream() override;



};


class CLASS_DECL_ACME output_byte2_stream :
   virtual public byte2_stream
{
public:



   output_byte2_stream();
   ~output_byte2_stream() override;



};

