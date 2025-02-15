/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * X11 Clipboard Redirection
 *
 * Copyright 2010-2011 Vic Lee
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

#ifndef __XF_CLIPRDR_H
#define __XF_CLIPRDR_H

#include "xf_client.h"
#include "xfreerdp.h"

#include <freerdp/client/cliprdr.h>

xfClipboard* xf_clipboard_new(xfContext* xfc);
void xf_clipboard_free(xfClipboard* clipboard);

void xf_cliprdr_init(xfContext* xfc, CliprdrClientContext* cliprdr);
void xf_cliprdr_uninit(xfContext* xfc, CliprdrClientContext* cliprdr);

void xf_cliprdr_handle_xevent(xfContext* xfc, XEvent* happening);

#endif /* __XF_CLIPRDR_H */
