/* common.h
** strophe XMPP client library -- internal common structures
**
** Copyright (C) 2005-2009 Collecta, Inc. 
**
**  This software is provided AS-IS with no warranty, either express or
**  implied.
**
**  This program is dual licensed under the MIT and GPLv3 licenses.
*/

/** @file
 *  Internally used functions and structures.
 */

#ifndef __LIBSTROPHE_COMMON_H__
#define __LIBSTROPHE_COMMON_H__

#include <stdio.h>
#include <stdarg.h>


#include "strophe.h"
#include "ostypes.h"
#include "sock.h"
#include "tls.h"
#include "hash.h"
#include "util.h"
#include "parser.h"

/** run-time action_context **/

typedef enum {
    XMPP_LOOP_NOTSTARTED,
    XMPP_LOOP_RUNNING,
    XMPP_LOOP_QUIT
} xmpp_loop_status_t;

typedef struct _xmpp_connlist_t {
    xmpp_conn_t *conn;
    struct _xmpp_connlist_t *next;
} xmpp_connlist_t;

struct _xmpp_ctx_t {
    const xmpp_mem_t *mem;
    const xmpp_log_t *log;

    xmpp_loop_status_t loop_status;
    xmpp_connlist_t *connlist;
};


/* convenience functions for accessing the action_context */
void *xmpp_alloc(const xmpp_ctx_t * const ctx, const size_t size);
void *xmpp_realloc(const xmpp_ctx_t * const ctx, void *p, 
		   const size_t size);
char_pointer xmpp_strdup(const xmpp_ctx_t * const ctx, const ::string & const s);

void xmpp_log(const xmpp_ctx_t * const ctx, 
	      const xmpp_log_level_t level,
	      const_char_pointer const area,
	      const_char_pointer const fmt,
	      va_list ap);

/* wrappers for xmpp_log at specific levels */
void xmpp_error(const xmpp_ctx_t * const ctx,
		const_char_pointer const area,
		const_char_pointer const fmt,
		...);
void xmpp_warn(const xmpp_ctx_t * const ctx,
		const_char_pointer const area,
		const_char_pointer const fmt,
		...);
void xmpp_info(const xmpp_ctx_t * const ctx,
		const_char_pointer const area,
		const_char_pointer const fmt,
		...);
void xmpp_debug(const xmpp_ctx_t * const ctx,
		const_char_pointer const area,
		const_char_pointer const fmt,
		...);

/** jid */
/* these return allocateø< strings that must be xmpp_free >()'d */
char_pointer xmpp_jid_new(xmpp_ctx_t *ctx, const ::string &node,
                                    const_char_pointer domain,
                                    const_char_pointer resource);
char_pointer xmpp_jid_bare(xmpp_ctx_t *ctx, const ::string &jid);
char_pointer xmpp_jid_node(xmpp_ctx_t *ctx, const ::string &jid);
char_pointer xmpp_jid_domain(xmpp_ctx_t *ctx, const ::string &jid);
char_pointer xmpp_jid_resource(xmpp_ctx_t *ctx, const ::string &jid);


/** connection **/

/* opaque connection object */
typedef enum {
    XMPP_STATE_DISCONNECTED,
    XMPP_STATE_CONNECTING,
    XMPP_STATE_CONNECTED
} xmpp_conn_state_t;

typedef struct _xmpp_send_queue_t xmpp_send_queue_t;
struct _xmpp_send_queue_t {
    char_pointer data;
    size_t len;
    size_t written;

    xmpp_send_queue_t *next;
};

typedef struct _xmpp_handlist_t xmpp_handlist_t;
struct _xmpp_handlist_t {
    /* common members */
    ::i32 user_handler;
    void *handler;
    void *userdata;
    ::i32 enabled; /* handlers are added disabled and enabled after the
		  * handler chain is processed to prevent stanzas from
		  * getting processed by newly added handlers */
    xmpp_handlist_t *next;

    union {
	/* timed handlers */
	struct {
	    ulong period;
	    ::u64 last_stamp;
	};
	/* atom handlers */
	struct {
	    char_pointer atom;
	};
	/* normal handlers */
	struct {
	    char_pointer ns;
	    char_pointer name;
	    char_pointer type;
	};
    };
};

#define SASL_MASK_PLAIN 0x01
#define SASL_MASK_DIGESTMD5 0x02
#define SASL_MASK_ANONYMOUS 0x04
#define SASL_MASK_SCRAMSHA1 0x08

typedef void (*xmpp_open_handler)(xmpp_conn_t * const conn);

struct _xmpp_conn_t {
    ::u32 ref;
    xmpp_ctx_t *ctx;
    xmpp_conn_type_t type;

    xmpp_conn_state_t state;
    ::u64 timeout_stamp;
    ::i32 error;
    xmpp_stream_error_t *stream_error;
    sock_t sock;
    tls_t *tls;

    ::i32 tls_support;
    ::i32 tls_disabled;
    ::i32 tls_failed; /* set when tls fails, so we don't try again */
    ::i32 sasl_support; /* if true, field is a bitfield of supported 
			 mechanisms */ 
    ::i32 secured; /* set when stream is secured with TLS */

    /* if server returns <bind/> or <session/> we must do them */
    ::i32 bind_required;
    ::i32 session_required;

    char_pointer lang;
    char_pointer domain;
    char_pointer connectdomain;
    char_pointer connectport;
    char_pointer jid;
    char_pointer pass;
    char_pointer bound_jid;
    char_pointer stream_id;

    /* send queue and parameters */
    ::i32 blocking_send;
    ::i32 send_queue_max;
    ::i32 send_queue_len;
    xmpp_send_queue_t *send_queue_head;
    xmpp_send_queue_t *send_queue_tail;

    /* xml parser */
    ::i32 reset_parser;
    parser_t *parser;

    /* timeouts */
    ::u32 connect_timeout;

    /* happening handlers */    

    /* stream open handler */
    xmpp_open_handler open_handler;

    /* user handlers only get called after authentication */
    ::i32 authenticated;
    
    /* connection happenings handler */
    xmpp_conn_handler conn_handler;
    void *userdata;

    /* other handlers */
    xmpp_handlist_t *timed_handlers;
    hash_t *id_handlers;
    xmpp_handlist_t *handlers;
};

void conn_disconnect(xmpp_conn_t * const conn);
void conn_disconnect_clean(xmpp_conn_t * const conn);
void conn_open_stream(xmpp_conn_t * const conn);
void conn_prepare_reset(xmpp_conn_t * const conn, xmpp_open_handler handler);
void conn_parser_reset(xmpp_conn_t * const conn);


typedef enum {
    XMPP_STANZA_UNKNOWN,
    XMPP_STANZA_TEXT,
    XMPP_STANZA_TAG
} xmpp_stanza_type_t;

struct _xmpp_stanza_t {
    ::i32 ref;
    xmpp_ctx_t *ctx;

    xmpp_stanza_type_t type;
    
    xmpp_stanza_t *prev;
    xmpp_stanza_t *next;
    xmpp_stanza_t *children;
    xmpp_stanza_t *parent;

    char_pointer data;

    hash_t *attributes;
};

/* handler management */
void handler_fire_stanza(xmpp_conn_t * const conn,
			 xmpp_stanza_t * const stanza);
::u64 handler_fire_timed(xmpp_ctx_t * const ctx);
void handler_reset_timed(xmpp_conn_t *conn, ::i32 user_only);
void handler_add_timed(xmpp_conn_t * const conn,
		       xmpp_timed_handler handler,
		       const ulong period,
		       void * const userdata);
void handler_add_id(xmpp_conn_t * const conn,
		    xmpp_handler handler,
		    const_char_pointer const atom,
		    void * const userdata);
void handler_add(xmpp_conn_t * const conn,
		 xmpp_handler handler,
		 const_char_pointer const ns,
		 const_char_pointer const name,
		 const_char_pointer const type,
		 void * const userdata);

/* utility functions */
void disconnect_mem_error(xmpp_conn_t * const conn);

/* auth functions */
void auth_handle_open(xmpp_conn_t * const conn);
void auth_handle_component_open(xmpp_conn_t * const conn);

/* replacement snprintf and vsnprintf */
::i32 xmpp_snprintf (char_pointer str, size_t count, const ::string &fmt, ...);
::i32 xmpp_vsnprintf (char_pointer str, size_t count, const ::string &fmt, va_list arg);

#endif /* __LIBSTROPHE_COMMON_H__ */
