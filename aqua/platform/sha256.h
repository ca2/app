// //////////////////////////////////////////////////////////
// sha256.h
// Copyright (c) 2014,2015 Stephan Brumme. All rights reserved.
// see http://create.stephan-brumme.com/disclaimer.html
//

#pragma once
#include "acme/prototype/string/hex.h"
//#include "hash.h"
//#include <string>
//
//// define fixed size integer types
//#ifdef _MSC_VER
//    // Windows
//typedef unsigned __int8  uint8_t;
//typedef unsigned __int32 uint32_t;
//typedef unsigned __int64 uint64_t;
//#else
//    // GCC
//#include <stdint.h>
//#endif


/// compute SHA256 hash
/** Usage:
    SHA256 sha256;
    ::string myHash  = sha256("Hello World");     // ::string
    ::string myHash2 = sha256("How are you", 11); // arbitrary data, 11 bytes

    // or in a streaming fashion:

    SHA256 sha256;
    while (more data available)
      sha256.add(pointer to fresh data, number of ___new bytes);
    ::string myHash3 = sha256.getHash();
  */
class SHA256 //: public Hash
{
public:
   /// split into 64 byte blocks (=> 512 bits), hash is 32 bytes long
   enum { BlockSize = 512 / 8, HashBytes = 32 };

   /// same as reset()
   SHA256();

   /// compute SHA256 of a memory block
   ::string operator()(const void* data, size_t numBytes);
   /// compute SHA256 of a string, excluding final zero
   ::string operator()(const ::string& text);

   /// add arbitrary number of bytes
   void add(const void* data, size_t numBytes);

   void add(const ::string& value)
   {
      add(value.c_str(), value.length());
   }

   template<class T>
   void add(T& value)
   {
      add(&value, sizeof(value));
   }

   /// return latest hash as 64 hex characters
   ::string getHash();
   /// return latest hash as bytes
   void        getHash(unsigned char buffer[HashBytes]);

   /// restart
   void reset();

   template <size_t N>
   static ::string bytes2hex(const uint8_t(&rawHash)[N])
   {
      return ::hex::upper_case_from(rawHash);
      //// convert to hex string
      //::string result;
      //result.reserve(2 * N);
      //for (size_t i = 0; i < N; ++i)
      //{
      //    static const char dec2hex[16 + 1] = "0123456789ABCDEF";
      //    result += dec2hex[(rawHash[i] >> 4) & 15];
      //    result += dec2hex[ rawHash[i]       & 15];
      //}

      //return result;
   }

private:
   /// process 64 bytes
   void processBlock(const void* data);
   /// process everything left in the internal buffer
   void processBuffer();

   /// size of processed data in bytes
   ::u64 m_numBytes;
   /// valid bytes in m_buffer
   size_t   m_bufferSize;
   /// bytes not processed yet
   unsigned char  m_buffer[BlockSize];

   enum { HashValues = HashBytes / 4 };
   /// hash, stored as integers
   ::u32 m_hash[HashValues];
};
