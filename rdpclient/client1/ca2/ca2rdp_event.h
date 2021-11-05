/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * DirectFB Event Handling
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

#ifndef __DF_EVENT_H
#define __DF_EVENT_H
#include "rdpclient/client/common/rdpclient.h"
#include "ca2rdp.h"



struct CLASS_DECL_AXIS_RDPCLIENT rdp_event_item
{

   void * input;
   int bKey;
   int down;
   ::u32 scancode;
   const ::id & id;
   POINT_I32 pt;
   void send();
};
CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_queue_event(void * input,int bKey, int down, ::u32 scancode, const ::id & id,POINT_I32 pt);
CLASS_DECL_AXIS_RDPCLIENT int  ca2rdp_get_event(rdp_event_item & item,void * input);
CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_send_event(void * input,int bKey,int down,::u32 scancode,const ::id & id,POINT_I32 pt);

//CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_send_mouse_button_event(rdpInput* input,const ::id & id,POINT_I32 pt);
//CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_send_keyboard_event(rdpInput* input,BOOL down,::u32 scancode);

#endif /* __DF_EVENT_H */
