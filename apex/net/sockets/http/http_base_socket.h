/**
 **   \file http_base_socket.h
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

   
   class response;


   class CLASS_DECL_APEX http_base_socket :
      virtual public http_socket
   {
   public:


      i32 m_iContentLength;


      http_base_socket(base_socket_handler& h);
      ~http_base_socket();


      virtual void OnFirst();
      virtual void OnHeader(id idKey, const string & value);
      virtual void OnHeaderComplete();
      virtual void OnData(const char *, memsize);
      virtual void OnDataComplete();

      void Respond();

      void OnWriteComplete();


      virtual void OnExecute();
      virtual void OnResponseComplete();

      //string set_cookie(
      //const char * name,
      //::payload payload,
      //i32 iExpire,
      //const char * path,
      //const char * domain,
      //bool bSecure);

      virtual void on_compress();



      http_base_socket(const http_base_socket& s);
      void Reset();

      void Execute();

      
      virtual bool read_file(const ::file::path& pcszParam, pointer_array < int_array >* prangea = nullptr, const char* pszContentType = nullptr);


   };




} // namespace sockets


