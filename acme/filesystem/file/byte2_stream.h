//
// Created by camilo on 2025-08-31 17:12 <3ThomasBorregaarSorensen!!
//
#pragma once


#include "file.h"
#include "stream.h"
#include "acme/prototype/prototype/memory.h"

class byte2_stream;

template < typename BYTE2_EXCHANGABLE >
concept byte2_exchangable = requires(BYTE2_EXCHANGABLE & t, ::byte2_stream &s)
{
t.byte2_exchange(s);

};
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
   byte2_stream & operator << (int  i);
   byte2_stream & operator >>(long long & ll);
   byte2_stream & operator << (long long ll);
   byte2_stream & operator >>(string & str);
   byte2_stream & operator << (string & str);

   template < byte2_exchangable BYTE2_EXCHANGABLE >
   byte2_stream & operator >>(BYTE2_EXCHANGABLE & t)
   {

      t.byte2_exchange(*this);

      return *this;

   }

   template < byte2_exchangable BYTE2_EXCHANGABLE >
   byte2_stream & operator <<(BYTE2_EXCHANGABLE & t)
   {

      t.byte2_exchange(*this);

      return *this;

   }


   template < typename TYPE >
   void exchange(TYPE & t)
   {
      if(m_estream == file::e_stream_output)
      {

         *this << t;

      }
      else if(m_estream == file::e_stream_input)
      {

         *this >> t;

      }
      else
      {

         throw "byte2_stream unsupported m_estream";

      }

   }


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
   output_byte2_stream(const ::block & block);
   ~output_byte2_stream() override;



};



