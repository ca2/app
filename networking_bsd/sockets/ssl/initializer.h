/**
 **   \file SSLInitializer.h
 **   \date  2007-04-30
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

#ifdef BSD_STYLE_SOCKETS


//#include "apex/networking/sockets/bsd/config.h"

//#include "openssl/ssl.h"

typedef struct bio_st BIO;

namespace sockets_bsd
{

   class CLASS_DECL_NETWORKING_BSD SSLInitializer :
      public object
   {
   public:

      //BIO *bio_err;

#if OPENSSL_API_COMPAT < 0x10100000L

      string m_rand_file;
      long m_rand_size;

#endif

      /**
         init openssl
         bio_err
         create random file
      */
      SSLInitializer();

      /**
         erase random file
      */
      ~SSLInitializer() override;

      
      void initialize(::particle * pparticle) override;


      void DeleteRandFile();

      /** SSL; ::pointer < ::mutex > locking function callback. */
      //static void SSL_locking_function(i32 mode, i32 n, const char *file, i32 line);

      /** Return thread atom. */
      //static unsigned long SSL_id_function();


   };




} // namespace sockets_bsd





#endif
