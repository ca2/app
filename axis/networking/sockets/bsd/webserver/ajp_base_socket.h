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


   class CLASS_DECL_AXIS AjpBaseSocket : public tcp_socket
   {
   public:


      int m_iState;
      int m_length;
      int m_ptr;
      char m_message[8192];

      class Initializer
      {
      public:
         Initializer();
         virtual ~Initializer() {}

         int_to_string Method;
         int_to_string header;
         int_to_string Attribute;
         string_map < int > ResponseHeader;

      };

      AjpBaseSocket();

      virtual void OnRawData(char *buf, memsize sz) override;

      virtual void OnHeader( short atom, short len ) = 0;
      virtual void OnPacket( const_char_pointer buf, memsize sz ) = 0;

   protected:
      uchar get_byte(const ::string &buf, int& ptr);
      bool get_boolean(const ::string &buf, int& ptr);
      short get_integer(const ::string &buf, int& ptr);
      string get_string(const ::string &buf, int& ptr);

      void put_byte(char *buf, int& ptr, uchar zz);
      void put_boolean(char *buf, int& ptr, bool zz);
      void put_integer(char *buf, int& ptr, short zz);
      void put_string(char *buf, int& ptr, const ::scoped_string & scopedstr);

   };


} // namespace sockets



