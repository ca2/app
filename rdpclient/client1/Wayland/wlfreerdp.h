/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Wayland Client
 *
 * Copyright 2014 Manuel Bachmann <tarnyko@tarnyko.net>
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

#ifndef __WLFREERDP_H
#define __WLFREERDP_H

#include <freerdp/freerdp.h>
#include <freerdp/log.h>
#include <winpr/wtypes.h>

#define TAG CLIENT_TAG("wayland")

typedef struct wlf_context wlfContext;

#include "wlf_display.h"
#include "wlf_window.h"
#include "wlf_input.h"

struct wlf_context
{
	rdpContext action_context;

	wlfDisplay* display;
	wlfWindow* window;
	wlfInput* input;
};

#endif /* __WLFREERDP_H */

