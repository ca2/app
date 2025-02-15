/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * X11 GDI
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

#ifndef __XF_GDI_H
#define __XF_GDI_H

#include <freerdp/gdi/gdi.h>

#include "xf_client.h"
#include "xfreerdp.h"

void xf_gdi_register_update_callbacks(rdpUpdate* update);
BOOL xf_gdi_bitmap_update(rdpContext* action_context, BITMAP_UPDATE* bitmapUpdate);
unsigned int xf_convert_rdp_order_color(xfContext* xfc, unsigned int color);

#endif /* __XF_GDI_H */
