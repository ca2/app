/**
 **   \file smtpd_socket.h
 **   \date  2007-05-10
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

   /** Smtp server axis class. */
   class CLASS_DECL_AXIS smtpd_socket : public tcp_socket
   {
   public:
      
      typedef enum {
         SMTP_NO_HELLO,
         SMTP_NAME_TOO_LONG,
         SMTP_DOMAIN_TOO_LONG,
         SMTP_QUIT
      } reason_t;

      bool m_hello; // we need HELO or EHLO first of all
      bool m_data;
      bool m_header;
      string m_header_line;


      smtpd_socket();

      void OnAccept();
      void OnLine(const string &);

      /** \return 'false' to abort */
      virtual bool OnHello(const string & domain) = 0;

      /** \return 'false' to abort */
      virtual bool OnMailFrom(const ::net::email_address & addr) = 0;

      /** \return 'false' to abort */
      virtual bool OnRcptTo(const ::net::email_address & addr) = 0;

      //using tcp_socket::OnHeader;
      virtual void OnHeader(id idKey, const string & value) = 0;

      virtual void OnHeaderComplete() = 0;

      virtual void OnData(const string & line) = 0;

      /** \return 'false' if message write failed (message will probably be resent) */
      virtual bool OnDataComplete() = 0;

      virtual void OnRset() = 0;

      virtual void OnAbort(reason_t) = 0;

      virtual void OnNotSupported(const string & cmd, const string & arg) = 0;

   };

} // namespace sockets


