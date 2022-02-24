/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * DirectFB Graphical Objects
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

#include "ca2rdp_graphics.h"

#include <winpr/crt.h>


/* Pointer Class */

BOOL ca2rdp_Pointer_New(rdpContext* context, rdpPointer* pointer)
{
   ca2rdpInfo* ca2rdpi;
//	int result;
   ca2rdpPointer* ca2rdp_pointer;
   //DFBSurfaceDescription dsc;

   ca2rdpi = ((ca2rdpContext*) context)->ca2rdpi;
   ca2rdp_pointer = (ca2rdpPointer*) pointer;


//	int pitch;

   ca2rdp_pointer->xhot = pointer->xPos;
   ca2rdp_pointer->yhot = pointer->yPos;

   ::cursor_alloc(((ca2rdpContext*)context)->m_pappRdp,ca2rdp_pointer->m_pcursor,pointer->xPos,pointer->yPos);

   ::draw2d::image_pointer * dib = ::cursor_get_dib(ca2rdp_pointer->m_pcursor);

   //.m_pimage->alloc(((ca2rdpContext*)context)->get_app()->create_new, this);
   ::draw2d::image_create(dib, ca2rdp_pointer->pointer.width,ca2rdp_pointer->pointer.height);

   if ((pointer->andMaskData != 0) && (pointer->xorMaskData != 0))
   {

      if (!freerdp_image_copy_from_pointer_data(
            (byte *) ::draw2d::image_get_data(dib), PIXEL_FORMAT_RGBA32,
            0, 0, 0, pointer->width, pointer->height,
            pointer->xorMaskData, pointer->lengthXorMask,
            pointer->andMaskData, pointer->lengthAndMask,
            pointer->xorBpp, &context->gdi->palette))
      {
         //_aligned_free(ci.pixels);
         //xf_unlock_x11(xfc, false);
         return false;
      }
      //  freerdp_alpha_cursor_convert((byte *) ::draw2d::image_get_data(dib),pointer->xorMaskData,pointer->andMaskData,
      //pointer->width, pointer->height, pointer->xorBpp, ca2rdpi->clrconv);
   }

   //if (pointer->xorBpp > 24)
   //{
//     freerdp_image_swap_color_order((byte *)::draw2d::image_get_data(dib),pointer->width,pointer->height);
   //}

   return 1;
}

void ca2rdp_Pointer_Free(rdpContext* context, rdpPointer* pointer)
{
   ca2rdpPointer* ca2rdp_pointer = (ca2rdpPointer*) pointer;
///	ca2rdp_pointer->surface->Release(ca2rdp_pointer->surface);
}

BOOL ca2rdp_Pointer_Set(rdpContext* context, const rdpPointer* pointer)
{

   ca2rdpInfo* ca2rdpi;
//   int result;
   ca2rdpPointer* ca2rdp_pointer;
   //DFBSurfaceDescription dsc;

   ca2rdpContext* ctx = (ca2rdpContext*) context;
   ca2rdpi = ctx->ca2rdpi;
   ca2rdp_pointer = (ca2rdpPointer*)pointer;

   if(ca2rdp_pointer == nullptr)
   {

      ctx->m_pviewRdp->rdpclient_set_cursor(nullptr);

   }
   else
   {

      ctx->m_pviewRdp->rdpclient_set_cursor(ca2rdp_pointer->m_pcursor);

   }

   /*	ca2rdpInfo* ca2rdpi;
   	DFBResult result;
   	ca2rdpPointer* ca2rdp_pointer;

   	ca2rdpi = ((ca2rdpContext*) context)->ca2rdpi;
   	ca2rdp_pointer = (ca2rdpPointer*) pointer;

   	ca2rdpi->layer->SetCooperativeLevel(ca2rdpi->layer, DLSCL_ADMINISTRATIVE);

   	ca2rdpi->layer->SetCursorOpacity(ca2rdpi->layer, ca2rdp_pointer ? 255: 0);

   	if(ca2rdp_pointer != nullptr)
   	{
   		result = ca2rdpi->layer->SetCursorShape(ca2rdpi->layer,
   			ca2rdp_pointer->surface, ca2rdp_pointer->xhot, ca2rdp_pointer->yhot);

   		if (result != DFB_OK)
   		{
   			DirectFBErrorFatal("SetCursorShape Error", result);
   			return;
   		}
   	}

   	ca2rdpi->layer->SetCooperativeLevel(ca2rdpi->layer, DLSCL_SHARED);*/
   return 1;
}

BOOL ca2rdp_Pointer_SetNull(rdpContext* context)
{
   ca2rdp_Pointer_Set(context, nullptr);
   return 1;
}

BOOL ca2rdp_Pointer_SetDefault(rdpContext* context)
{
   return 1;
}

/* Graphics Module */

void ca2rdp_register_graphics(rdpGraphics* graphics)
{
   rdpPointer* pointer;

   pointer = (rdpPointer*) malloc(sizeof(rdpPointer));
   ZeroMemory(pointer, sizeof(rdpPointer));
   pointer->size = sizeof(ca2rdpPointer);

   pointer->New = ca2rdp_Pointer_New;
   pointer->Free = ca2rdp_Pointer_Free;
   pointer->Set = ca2rdp_Pointer_Set;
   pointer->SetNull = ca2rdp_Pointer_SetNull;
   pointer->SetDefault = ca2rdp_Pointer_SetDefault;

   graphics_register_pointer(pgraphics, pointer);
   free(pointer);
}

