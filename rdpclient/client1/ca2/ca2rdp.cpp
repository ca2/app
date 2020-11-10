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

#include "ca2rdp_event.h"
#include "ca2rdp_graphics.h"

#include "ca2rdp.h"

#include <errno.h>
#include <locale.h>

#include <freerdp/freerdp.h>
#include <freerdp/constants.h>
//#include <freerdp/utils/event.h>
#include <freerdp/client/file.h>
#include <freerdp/client/cmdline.h>
#include <freerdp/client/channels.h>
#include <freerdp/client/cliprdr.h>

#include <winpr/crt.h>
#include <winpr/synch.h>

#if defined(ANDROID) || defined(__APPLE__)
#include <sys/select.h>
#endif

#define TAG CLIENT_TAG("axisrdpclient")

//int ca2rdp_context_new(freerdp* instance, rdpContext* context)
//{
//	context->channels = freerdp_channels_new();
//	return 0;
//}
//
//void ca2rdp_context_free(freerdp* instance, rdpContext* context)
//{
//
//}

BOOL ca2rdp_begin_paint(rdpContext* context)
{
   rdpGdi* gdi = context->gdi;
#ifdef WINDOWS_DESKTOP
   gdi->primary->hdc->hwnd->invalid->null = 1;
#endif
   return 1;
}

BOOL ca2rdp_end_paint(rdpContext* context)
{
   rdpGdi* gdi;
   ca2rdpInfo* ca2rdpi;
#ifdef _WIN32
   gdi = context->gdi;
   ca2rdpi = ((ca2rdpContext*) context)->ca2rdpi;

   if (gdi->primary->hdc->hwnd->invalid->null)
      return 1;

//#ifdef WINDOWS_DESKTOP
//	ca2rdpi->update_rect.left = gdi->primary->hdc->hwnd->invalid->x;
//	ca2rdpi->update_rect.top = gdi->primary->hdc->hwnd->invalid->y;
//   ca2rdpi->update_rect.right = gdi->primary->hdc->hwnd->invalid->x+gdi->primary->hdc->hwnd->invalid->w;
//   ca2rdpi->update_rect.bottom = gdi->primary->hdc->hwnd->invalid->y +gdi->primary->hdc->hwnd->invalid->h;
//#else
   ca2rdpi->x = 0;
   ca2rdpi->y = 0;
   ca2rdpi->w = gdi->width;
   ca2rdpi->h = gdi->height;
//#endif
   ::draw2d::image_copy(ca2rdpi->surface,ca2rdpi->primary);
#endif


   /*#ifdef WINDOWS
      ::draw2d::graphics_pointer g(((ca2rdpContext*)context)->get_context_application()->create_new, this);
      g->CreateCompatibleDC(nullptr);
      g->Attach(gdi->primary->hdc->alpha);
      ca2rdpi->primary->get_graphics()->BitBlt(ca2rdpi->update_rect.left,ca2rdpi->update_rect.top,
         ca2rdpi->update_rect.width(),ca2rdpi->update_rect.height,g,0, 0,SRCCOPY);
      g->Detach();
   #else
      ca2rdpi->primary->BitBlt(ca2rdpi->surface,SRCCOPY);
   #endif*/
   return 1;
}

BOOL ca2rdp_get_fds(freerdp* instance, void** rfds, int* rcount, void** wfds, int* wcount)
{
   ca2rdpInfo* ca2rdpi;

   ca2rdpi = ((ca2rdpContext*) instance->context)->ca2rdpi;

   rfds[*rcount] = (void*)(size_t)(ca2rdpi->read_fds);
   (*rcount)++;

   return TRUE;
}

BOOL ca2rdp_check_fds(freerdp* instance, fd_set* set)
{
   ca2rdpInfo* ca2rdpi;

   ca2rdpi = ((ca2rdpContext*) instance->context)->ca2rdpi;

   if (!FD_ISSET(ca2rdpi->read_fds, set))
      return TRUE;

//	if (read(ca2rdpi->read_fds, &(ca2rdpi->event), sizeof(ca2rdpi->event)) > 0)
   //	ca2rdp_event_process(instance, &(ca2rdpi->event));

   return TRUE;
}

BOOL ca2rdp_pre_connect(freerdp* instance)
{
   ca2rdpInfo* ca2rdpi;
   BOOL bitmap_cache;
   ca2rdpContext* context;
   rdpSettings* settings;

   ca2rdpi = (ca2rdpInfo*) malloc(sizeof(ca2rdpInfo));
   ZeroMemory(ca2rdpi, sizeof(ca2rdpInfo));

   context = ((ca2rdpContext*) instance->context);
   context->ca2rdpi = ca2rdpi;

   settings = instance->settings;
   bitmap_cache = settings->BitmapCacheEnabled;

   settings->OrderSupport[NEG_DSTBLT_INDEX] = TRUE;
   settings->OrderSupport[NEG_PATBLT_INDEX] = TRUE;
   settings->OrderSupport[NEG_SCRBLT_INDEX] = TRUE;
   settings->OrderSupport[NEG_OPAQUE_RECT_INDEX] = TRUE;
   settings->OrderSupport[NEG_DRAWNINEGRID_INDEX] = FALSE;
   settings->OrderSupport[NEG_MULTIDSTBLT_INDEX] = FALSE;
   settings->OrderSupport[NEG_MULTIPATBLT_INDEX] = FALSE;
   settings->OrderSupport[NEG_MULTISCRBLT_INDEX] = FALSE;
   settings->OrderSupport[NEG_MULTIOPAQUERECT_INDEX] = TRUE;
   settings->OrderSupport[NEG_MULTI_DRAWNINEGRID_INDEX] = FALSE;
   settings->OrderSupport[NEG_LINETO_INDEX] = TRUE;
   settings->OrderSupport[NEG_POLYLINE_INDEX] = TRUE;
   settings->OrderSupport[NEG_MEMBLT_INDEX] = bitmap_cache;
   settings->OrderSupport[NEG_MEM3BLT_INDEX] = FALSE;
   settings->OrderSupport[NEG_MEMBLT_V2_INDEX] = bitmap_cache;
   settings->OrderSupport[NEG_MEM3BLT_V2_INDEX] = FALSE;
   settings->OrderSupport[NEG_SAVEBITMAP_INDEX] = FALSE;
   settings->OrderSupport[NEG_GLYPH_INDEX_INDEX] = FALSE;
   settings->OrderSupport[NEG_FAST_INDEX_INDEX] = FALSE;
   settings->OrderSupport[NEG_FAST_GLYPH_INDEX] = FALSE;
   settings->OrderSupport[NEG_POLYGON_SC_INDEX] = FALSE;
   settings->OrderSupport[NEG_POLYGON_CB_INDEX] = FALSE;
   settings->OrderSupport[NEG_ELLIPSE_SC_INDEX] = FALSE;
   settings->OrderSupport[NEG_ELLIPSE_CB_INDEX] = FALSE;

   //ca2rdpi->clrconv = (CLRCONV*) malloc(sizeof(CLRCONV));
   //ZeroMemory(ca2rdpi->clrconv, sizeof(CLRCONV));

   //ca2rdpi->clrconv->alpha = 1;
   //ca2rdpi->clrconv->invert = 0;
   //ca2rdpi->clrconv->rgb555 = 0;

   //ca2rdpi->clrconv->palette = (rdpPalette*) malloc(sizeof(rdpPalette));
   //ZeroMemory(ca2rdpi->clrconv->palette, sizeof(rdpPalette));

   //freerdp_channels_pre_connect(instance->context->channels, instance);

   instance->context->cache = cache_new(instance->settings);

   return TRUE;
}

BOOL ca2rdp_post_connect(freerdp* instance)
{
   rdpGdi* gdi;
   ca2rdpInfo* ca2rdpi;
   ca2rdpContext* context;

   context = ((ca2rdpContext*) instance->context);
   ca2rdpi = context->ca2rdpi;
   //gdi->width = instance->settings->DesktopWidth;
   //gdi->height = instance->settings->DesktopHeight;

   ::draw2d::image_create(context->m_pappRdp, ca2rdpi->primary);
   ::draw2d::image_create(ca2rdpi->primary, instance->settings->DesktopWidth,instance->settings->DesktopHeight);

   ::draw2d::image_create(context->m_pappRdp, ca2rdpi->surface);
   ::draw2d::image_create(ca2rdpi->surface, instance->settings->DesktopWidth,instance->settings->DesktopHeight);

//   App(context->get_context_application()).alloc(ca2rdpi->primary);
   // ca2rdpi->primary->create(instance->settings->DesktopWidth,instance->settings->DesktopHeight);

   //App(context->get_context_application()).alloc(ca2rdpi->surface);
   //ca2rdpi->surface->create(instance->settings->DesktopWidth,instance->settings->DesktopHeight);


   gdi_init(instance, PIXEL_FORMAT_BGRX32);
   gdi = instance->context->gdi;

//	ca2rdpi->err = DirectFBCreate(&(ca2rdpi->ca2rdpb));

   //ca2rdpi->dsc.flags = DSDESC_CAPS;
   //ca2rdpi->dsc.caps = DSCAPS_PRIMARY;
   //ca2rdpi->err = ca2rdpi->ca2rdpb->CreateSurface(ca2rdpi->ca2rdpb, &(ca2rdpi->dsc), &(ca2rdpi->primary));
   //ca2rdpi->err = ca2rdpi->primary->GetSize(ca2rdpi->primary, &(gdi->width), &(gdi->height));
   //ca2rdpi->ca2rdpb->SetVideoMode(ca2rdpi->ca2rdpb, gdi->width, gdi->height, gdi->dstBpp);
   //ca2rdpi->ca2rdpb->CreateInputEventBuffer(ca2rdpi->ca2rdpb, DICAPS_ALL, DFB_TRUE, &(ca2rdpi->event_buffer));
   //ca2rdpi->event_buffer->CreateFileDescriptor(ca2rdpi->event_buffer, &(ca2rdpi->read_fds));

   //ca2rdpi->ca2rdpb->GetDisplayLayer(ca2rdpi->ca2rdpb, 0, &(ca2rdpi->layer));
   //ca2rdpi->layer->EnableCursor(ca2rdpi->layer, 1);

   //ca2rdpi->dsc.flags = DSDESC_CAPS | DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PREALLOCATED | DSDESC_PIXELFORMAT;
   //ca2rdpi->dsc.caps = DSCAPS_SYSTEMONLY;
   //ca2rdpi->dsc.width = gdi->width;
   //ca2rdpi->dsc.height = gdi->height;

   //if (gdi->dstBpp == 32 || gdi->dstBpp == 24)
   //ca2rdpi->dsc.pixelformat = DSPF_AiRGB;
   //else if (gdi->dstBpp == 16 || gdi->dstBpp == 15)
//		ca2rdpi->dsc.pixelformat = DSPF_RGB16;
//	else if (gdi->dstBpp == 8)
   //	ca2rdpi->dsc.pixelformat = DSPF_RGB332;
   //else
   //ca2rdpi->dsc.pixelformat = DSPF_AiRGB;

   //ca2rdpi->dsc.preallocated[0].data = gdi->primary_buffer;
   //ca2rdpi->dsc.preallocated[0].pitch = gdi->width * gdi->bytesPerPixel;
   //ca2rdpi->ca2rdpb->CreateSurface(ca2rdpi->ca2rdpb, &(ca2rdpi->dsc), &(ca2rdpi->surface));
//
   instance->update->BeginPaint = ca2rdp_begin_paint;
   instance->update->EndPaint = ca2rdp_end_paint;

   //ca2rdp_keyboard_init();

   pointer_cache_register_callbacks(instance->update);
   ca2rdp_register_graphics(instance->context->graphics);

   //freerdp_channels_post_connect(instance->context->channels, instance);

   return TRUE;
}

BOOL ca2rdp_verify_certificate(freerdp* instance, char* subject, char* issuer, char* fingerprint)
{
   char answer;

   printf("Certificate details:\n");
   printf("\tSubject: %s\n", subject);
   printf("\tIssuer: %s\n", issuer);
   printf("\tThumbprint: %s\n", fingerprint);
   printf("The above X.509 certificate could not be verified, possibly because you do not have "
          "the CA certificate in your certificate store, or the certificate has expired. "
          "Please look at the documentation on how to create local certificate store for a private CA.\n");

   while (1)
   {
      printf("Do you trust the above certificate? (Y/N) ");
      answer = fgetc(stdin);

      if (answer == 'y' || answer == 'Y')
      {
         return TRUE;
      }
      else if (answer == 'n' || answer == 'N')
      {
         break;
      }
   }

   return FALSE;
}

static int ca2rdp_receive_channel_data(freerdp* instance, int channelId, byte* data, int size, int flags, int total_size)
{
   return freerdp_channels_data(instance, channelId, data, size, flags, total_size);
}

//static void ca2rdp_process_cb_monitor_ready_event(rdpChannels* channels, freerdp* instance)
//{
//	wMessage* event;
//	RDP_CB_FORMAT_LIST_EVENT* format_list_event;
//
//	event = freerdp_event_new(CliprdrChannel_Class, CliprdrChannel_FormatList, nullptr, nullptr);
//
//	format_list_event = (RDP_CB_FORMAT_LIST_EVENT*) event;
//	format_list_event->num_formats = 0;
//
//	freerdp_channels_send_event(channels, event);
//}
//
//static void ca2rdp_process_channel_event(rdpChannels* channels, freerdp* instance)
//{
//	wMessage* event;
//
//	event = freerdp_channels_pop_event(channels);
//
//	if (event)
//	{
//		switch (GetMessageType(event->id))
//		{
//			case CliprdrChannel_MonitorReady:
//				ca2rdp_process_cb_monitor_ready_event(channels, instance);
//				break;
//
//			default:
//				WLog_ERR(TAG, "ca2rdp_process_channel_event: unknown event type %d\n", GetMessageType(event->id));
//				break;
//		}
//
//		freerdp_event_free(event);
//	}
//}

static void ca2rdp_free(ca2rdpInfo* ca2rdpi)
{
//	ca2rdpi->ca2rdpb->Release(ca2rdpi->ca2rdpb);
   free(ca2rdpi);
}

int ca2rdpreerdp_run(freerdp* instance)
{
   int i;
   int fds;
   int max_fds;
   int rcount;
   int wcount;
   void* rfds[32];
   void* wfds[32];
   fd_set rfds_set;
   fd_set wfds_set;
   ca2rdpInfo* ca2rdpi;
   ca2rdpContext* context;
   rdpChannels* channels;

   ZeroMemory(rfds, sizeof(rfds));
   ZeroMemory(wfds, sizeof(wfds));

   if (!freerdp_connect(instance))
      return 0;

   context = (ca2rdpContext*) instance->context;

   ca2rdpi = context->ca2rdpi;
   channels = instance->context->channels;

   while (1)
   {
      rcount = 0;
      wcount = 0;

      if (freerdp_get_fds(instance, rfds, &rcount, wfds, &wcount) != TRUE)
      {
         WLog_ERR(TAG, "Failed to get FreeRDP file descriptor\n");
         break;
      }
      if (freerdp_channels_get_fds(channels, instance, rfds, &rcount, wfds, &wcount) != TRUE)
      {
         WLog_ERR(TAG, "Failed to get channel manager file descriptor\n");
         break;
      }
      if (ca2rdp_get_fds(instance, rfds, &rcount, wfds, &wcount) != TRUE)
      {
         WLog_ERR(TAG, "Failed to get ca2rdpreerdp file descriptor\n");
         break;
      }

      max_fds = 0;
      FD_ZERO(&rfds_set);
      FD_ZERO(&wfds_set);

      for (i = 0; i < rcount; i++)
      {
         fds = (int)(size_t)(rfds[i]);

         if (fds > max_fds)
            max_fds = fds;

         FD_SET(fds, &rfds_set);
      }

      if (max_fds == 0)
         break;

      if (select(max_fds + 1, &rfds_set, &wfds_set, nullptr, nullptr) == -1)
      {
         /* these are not really errors */
         if (!((errno == EAGAIN) ||
               (errno == EWOULDBLOCK) ||
               (errno == EINPROGRESS) ||
               (errno == EINTR))) /* signal occurred */
         {
            WLog_ERR(TAG, "ca2rdpreerdp_run: select failed\n");
            break;
         }
      }

      if (freerdp_check_fds(instance) != TRUE)
      {
         WLog_ERR(TAG, "Failed to check FreeRDP file descriptor\n");
         break;
      }
      if (ca2rdp_check_fds(instance, &rfds_set) != TRUE)
      {
         WLog_ERR(TAG, "Failed to check ca2rdpreerdp file descriptor\n");
         break;
      }
      if (freerdp_channels_check_fds(channels, instance) != TRUE)
      {
         WLog_ERR(TAG, "Failed to check channel manager file descriptor\n");
         break;
      }
//		ca2rdp_process_channel_event(channels, instance);
   }

//	freerdp_channels_close(channels, instance);
   //freerdp_channels_free(channels);
   ca2rdp_free(ca2rdpi);
   gdi_free(instance);
   freerdp_disconnect(instance);
   freerdp_free(instance);

   return 0;
}

/*
void* thread_func(void* param)

{
	struct thread_data* data;
	data = (struct thread_data*) param;

	ca2rdpreerdp_run(data->instance);

	free(data);

	pthread_detach(pthread_self());

	g_thread_count--;

        if (g_thread_count < 1)
        	ReleaseSemaphore(g_sem, 1, nullptr);

	return nullptr;
}
*/

/*
int main(int argc, char* argv[])
{
	int status;
	pthread_t thread;
	freerdp* instance;
	ca2rdpContext* context;
	rdpChannels* channels;
	struct thread_data* data;

	setlocale(LC_ALL, "");

	g_sem = CreateSemaphore(nullptr, 0, 1, nullptr);

	instance = freerdp_new();
	instance->PreConnect = ca2rdp_pre_connect;
	instance->PostConnect = ca2rdp_post_connect;
	instance->VerifyCertificate = ca2rdp_verify_certificate;
	instance->ReceiveChannelData = ca2rdp_receive_channel_data;

	instance->ContextSize = sizeof(ca2rdpContext);
	instance->ContextNew = ca2rdp_context_new;
	instance->ContextFree = ca2rdp_context_free;
	freerdp_context_new(instance);

	context = (ca2rdpContext*) instance->context;
	channels = instance->context->channels;

	DirectFBInit(&argc, &argv);

	instance->context->argc = argc;
	instance->context->argv = argv;

	status = freerdp_client_settings_parse_command_line(instance->settings, argc, argv);

	if (status < 0)
		exit(0);

	freerdp_client_load_addins(instance->context->channels, instance->settings);

	data = (struct thread_data*) malloc(sizeof(struct thread_data));
	ZeroMemory(data, sizeof(sizeof(struct thread_data)));

	data->instance = instance;

	g_thread_count++;
	pthread_create(&thread, 0, thread_func, data);

	while (g_thread_count > 0)
	{
		WaitForSingleObject(g_sem, U32_INFINITE_TIMEOUT);
	}

	return 0;
}


*/


::draw2d::graphics * ca2rdp_ctx_get_graphics(ca2rdp_context * pcontext)
{
   if(pcontext->ca2rdpi == nullptr)
      return nullptr;
   return ::draw2d::image_get_graphics(pcontext->ca2rdpi->surface);

}

color32_t * ca2rdp_ctx_get_primary(ca2rdp_context * pcontext)
{
//#ifdef _WIN32
//   if(pcontext->primary == nullptr)
//      return nullptr;
//   return (color32_t *) pcontext->primary->pdata;
//#else
   if(pcontext->gdi == nullptr)
      return nullptr;
   /*   if(pcontext->gdi->drawing == nullptr)
         return nullptr;
      if(pcontext->gdi->drawing->bitmap == nullptr)
         return nullptr;
      return (color32_t *)pcontext->gdi->drawing->bitmap->p*/
   return (color32_t *)pcontext->gdi->primary_buffer;
   ;
//#endif
}

int ca2rdp_ctx_get_bitmap_size(ca2rdp_context * pcontext)
{
   if(pcontext->gdi == nullptr)
      return 0;
   /*   if(pcontext->gdi->drawing == nullptr)
   return nullptr;
   if(pcontext->gdi->drawing->bitmap == nullptr)
   return nullptr;
   return (color32_t *)pcontext->gdi->drawing->bitmap->p*/
   return pcontext->gdi->bitmap_size;
   ;
}


