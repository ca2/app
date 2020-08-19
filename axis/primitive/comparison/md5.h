/////////////////////////////////////////////////////////////////////////
// MD5.h
// Implementation file for MD5 class
//
// This C++ Class implementation of the original RSA Data Security, Inc.
// MD5 Message-Digest Algorithm is copyright (c) 2002, Gary McNickle.
// All rights reserved.  This software is a derivative of the "RSA Data
//  Security, Inc. MD5 Message-Digest Algorithm"
//
// You may use this software free of any charge, but without any
// warranty or implied warranty, provided that you follow the terms
// of the original RSA copyright, listed below.
//
// Original RSA Data Security, Inc. Copyright notice
/////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
// rights reserved.
//
// License to copy and use this software is granted provided that it
// is identified as the "RSA Data Security, Inc. MD5 Message-Digest
// Algorithm" in all material mentioning or referencing this software
// or this function.
// License is also granted to make and use derivative works provided
// that such works are identified as "derived from the RSA Data
// Security, Inc. MD5 Message-Digest Algorithm" in all material
// mentioning or referencing the derived work.
// RSA Data Security, Inc. makes no representations concerning either
// the merchantability of this software or the suitability of this
// software for any particular purpose. It is provided "as is"
// without express or implied warranty of any kind.
// These notices must be retained in any copies of any part of this
// documentation and/or software.
/////////////////////////////////////////////////////////////////////////

/*
* This is an OpenSSL-compatible implementation of the RSA Data Security, Inc.
* MD5 Message-Digest Algorithm (RFC 1321).
*
* Homepage:
* http://openwall.info/wiki/people/solar/software/public-domain-source-code/md5
*
* Author:
* Alexander Peslyak, better known as Solar Designer <solar at openwall.com>
*
* This software was written by Alexander Peslyak in 2001.  No copyright is
* claimed, and the software is hereby placed in the public domain.
* In case this attempt to disclaim copyright and place the software in the
* public domain is deemed nullptr and void, then the software is
* Copyright (c) 2001 Alexander Peslyak and it is hereby released to the
* general public under the following terms:
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted.
*
* There's ABSOLUTELY NO WARRANTY, express or implied.
*
* See md5.c for more information.
*/
#pragma once


//namespace md5
//{
//
//
//	class CLASS_DECL_AURA md5
//	{
//	public:
//
//
//		typedef struct
//		{
//			size_t            lo;
//			size_t            hi;
//			u32             a;
//			u32             b;
//			u32             c;
//			u32             d;
//			uchar             buffer[64];
//			u32             block[16];
//		} action_context;
//
//
//		action_context     m_ctx;
//		uchar       m_uchaDigest[16];
//
//
//		md5();
//
//
//		void	            initialize();
//		void	            update(const void * pdata, size_t nInputLen);
//		void	            finalize();
//		const unsigned char *   
//                        digest();
//		string			   to_string();
//		const void *		body(const void *data, u32 size);
//      void              get(memory & mem);
//
//
//	};
//
//
//} // namespace md5



