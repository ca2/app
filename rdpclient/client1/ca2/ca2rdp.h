/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * DirectFB Client
 *
 * Copyright 2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __DFREERDP_H
#define __DFREERDP_H
#include "rdpclient/config.h"
#if defined(ANDROID)
#include <pthread.h>
#endif
#if defined(_WIN32) && !defined(UNIVERSAL_WINDOWS)
#include "rdpclient/client/Windows/wf_client.h"
//#elif defined(ANDROID)
//#include "axis/rdpclient/client/A"
#endif
#include <freerdp/freerdp.h>
#include <freerdp/graphics.h>
#include <freerdp/gdi/gdi.h>
#include <freerdp/codec/color.h>
#include <freerdp/channels/channels.h>

#include <stdio.h>


#ifdef _WIN32
typedef ::u32 itask_t;
#else
typedef pthread_t itask_t;
#endif


typedef struct ca2rdp_info ca2rdpInfo;

CLASS_DECL_AXIS_RDPCLIENT BOOL ca2rdp_pre_connect(freerdp* instance);

#ifdef _WIN32
#else
typedef unsigned int color32_t;
#endif

namespace aura
{
   class application;
}

namespace draw2d
{
   class dib;
   class graphics;
}

namespace draw2d
{
   class cursor;
   void cursor_alloc(::particle * pparticle,cursor * & pcursor,int xHotspot,int yHotspot);
   ::draw2d::image_pointer * cursor_get_dib(cursor * pcursor);
}


struct rdpclient_impact_interface
{
   virtual void rdpclient_set_cursor(::draw2d::cursor * pcursor) = 0;
};

namespace message
{
   class base;
   class mouse;
}

namespace draw2d
{
/*   void dib_copy(dib * pimagethis, dib *pimage);
/*   void dib_alloc(::particle * pparticle, dib * & pimage);
/*   void dib_create(dib * pimage, int w, int h);
/*   unsigned int * dib_get_data(dib * pimage);
/*   graphics * dib_get_graphics(dib * pimage);
}

struct ca2rdp_context :
#if defined(_WIN32) && !defined(UNIVERSAL_WINDOWS)
   public wf_context
#else
   public rdpContext
#endif
{
   int width;
   int height;
   int dstBpp;


#ifdef _WIN32
   ::u32 mainThreadId;
#else
   pthread_t mainThreadId;
#endif
   HANDLE thread;
   ::aura::application * m_pappRdp;
   rdpclient_impact_interface * m_pviewRdp;

   ca2rdpInfo* ca2rdpi;
};

CLASS_DECL_AXIS_RDPCLIENT ::draw2d::graphics * ca2rdp_ctx_get_graphics(ca2rdp_context * pcontext);
CLASS_DECL_AXIS_RDPCLIENT color32_t * ca2rdp_ctx_get_primary(ca2rdp_context * pcontext);
CLASS_DECL_AXIS_RDPCLIENT int ca2rdp_ctx_get_bitmap_size(ca2rdp_context * pcontext);

typedef struct ca2rdp_context ca2rdpContext;

struct ca2rdp_pointer
{
   rdpPointer pointer;
   ::draw2d::cursor * m_pcursor;
   ::u32 xhot;
   ::u32 yhot;
};
typedef struct ca2rdp_pointer ca2rdpPointer;

struct ca2rdp_info
{
   int read_fds;
   int err;
   ::user::message * event;
   //DFBEvent event;
//	HCLRCONV clrconv;
   int x;
   int y;
   int w;
   int h;
   //DFBSurfaceDescription dsc;
   ::draw2d::image_pointer * primary;
   ::draw2d::image_pointer * surface;
//	IDirectFBDisplayLayer* layer;
   //IDirectFBEventBuffer* event_buffer;



};


CLASS_DECL_AXIS_RDPCLIENT BOOL ca2rdp_post_connect(freerdp* instance);

#endif /* __DFREERDP_H */
