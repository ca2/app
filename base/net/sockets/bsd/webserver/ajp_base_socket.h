/**
 **   \file AjpBaseSocket.h
 **   \date  2007-10-05
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2007  Anders Hedstrom

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#pragma once


namespace sockets
{


   class CLASS_DECL_BASE AjpBaseSocket : public tcp_socket
   {
   public:


      i32 m_iState;
      i32 m_length;
      i32 m_ptr;
      char m_message[8192];

      class Initializer
      {
      public:
         Initializer();
         virtual ~Initializer() {}

         int_to_string Method;
         int_to_string header;
         int_to_string Attribute;
         string_map < i32 > ResponseHeader;

      };

      AjpBaseSocket(base_socket_handler& h);

      virtual void OnRawData(char *buf, memsize sz) override;

      virtual void OnHeader( i16 id, i16 len ) = 0;
      virtual void OnPacket( const char *buf, memsize sz ) = 0;

   protected:
      uchar get_byte(const char *buf, i32& ptr);
      bool get_boolean(const char *buf, i32& ptr);
      i16 get_integer(const char *buf, i32& ptr);
      string get_string(const char *buf, i32& ptr);

      void put_byte(char *buf, i32& ptr, uchar zz);
      void put_boolean(char *buf, i32& ptr, bool zz);
      void put_integer(char *buf, i32& ptr, i16 zz);
      void put_string(char *buf, i32& ptr, const char * psz);

   };


} // namespace sockets



