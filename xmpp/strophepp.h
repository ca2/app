/* strophepp.h
** strophe XMPP client library C++ API
**
** Copyright (C) 2005-2009 Collecta, Inc.
**
**  This software is provided AS-IS with no warranty, either express or
**  implied.
** 
**  This program is dual licensed under the MIT and GPLv3 licenses.
*/

/** @file
 *  Strophe public C++ API definitions.
 */

#ifndef __LIBSTROPHE_STROPHEPP_H__
#define __LIBSTROPHE_STROPHEPP_H__

#include "strophe.h"

namespace XMPP {
    class Context {
    private:
	xmpp_mem_t m_mem;
	xmpp_log_t m_log;
	xmpp_ctx_t *m_ctx;

    public:
	Context();
	virtual ~Context();

	virtual void *alloc(const size_t size);
	virtual void *realloc(void *p, const size_t size);
	virtual void free(void *p);
	virtual void log(const xmpp_log_level_t level,
			 const_char_pointer const area,
			 const_char_pointer const msg);

	xmpp_ctx_t *getContext();

    private:
	static void *callAlloc(const size_t size, void * const userdata);
	static void *callRealloc(void *p, const size_t size, 
				 void * const userdata);
	static void callFree(void *p, void * const userdata);
	static void callLog(void * const userdata, 
			    const xmpp_log_level_t level,
			    const_char_pointer const area,
			    const_char_pointer const msg);
    };

    class Stanza {
    private:
	Context *m_ctx;
	xmpp_stanza_t *m_stanza;

	void *operator new(size_t size, Context *ctx);
	void operator delete(void *p);
	Stanza(Context *ctx);
	virtual ~Stanza();

    public:
	static Stanza *create(Context *ctx);
	void release();
	Stanza *clone();
	Stanza *copy();
	
	int toText(const ::string &* const buf, size_t * const buflen);
	Stanza *getChildren();
	Stanza *getChildByName(const ::string & const name);
	Stanza *getNext();
        char *getAttribute(const ::string & const name);
	char *getNamespace();
	char *getText();
	char *getName();
	void addChild(Stanza *child);
	void setNamespace(const ::string & const ns);
	void setAttribute(const ::string & const key, const ::string & const value);
	void setName(const ::string & const name);
	void setText(const ::string & const text);
	void setText(const ::string & const text, const size_t size);
	char *getType();
	char *getId();
	char *getTo();
	char *getFrom();
	void setType(const ::string & const type);
	void setId(const ::string & const atom);
	void setTo(const ::string & const to);
	void setFrom(const ::string & const from);
    };

    class Connection {
    private:
	Context *m_ctx;
	xmpp_conn_t *conn;

	void *operator new(size_t size, Context *ctx);
	Connection(Context *ctx);

    public:
	static Connection *create(Context *ctx);
	virtual ~Connection();
	Connection *clone();
	void operator delete(void *p);

	const_char_pointer getJID();
	void setJID(const ::string & const jid);
	const_char_pointer getPass();
	void setPass(const ::string & const pass);
	bool connectClient(const ::string & const domain,
			   xmpp_conn_handler callback,
			   void * const userdata);
	void disconnect();
	void send(Stanza *stanza);

	void addTimedHandler(xmpp_timed_handler handler,
			     const unsigned long perdio,
			     void * const userdata);
	void deleteTimedHandler(xmpp_timed_handler handler);
	void addHandler(xmpp_handler handler,
			const_char_pointer const ns,
			const_char_pointer const name,
			const_char_pointer const type,
			void * const userdata);
	void deleteHandler(xmpp_handler handler);
	void addIdHandler(xmpp_handler handler,
			  const_char_pointer const atom,
			  void * const userdata);
	void deleteIdHandler(xmpp_handler handler);
    };
}

#endif /* __LIBSTROPHE_STROPHEPP_H__ */
