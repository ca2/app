/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * FreeRDP Client Compatibility
 *
 * Copyright 2012 Marc-Andre Moreau <marcandre.moreau@gmail.com>
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

#ifndef FREERDP_CLIENT_COMPATIBILITY_H
#define FREERDP_CLIENT_COMPATIBILITY_H

#include <freerdp/api.h>
#include <freerdp/freerdp.h>

FREERDP_API ::i32 freerdp_detect_old_command_line_syntax(::i32 argc, char_pointer * argv, ::i32* count);
FREERDP_API ::i32 freerdp_client_parse_old_command_line_arguments(::i32 argc, char_pointer * argv, rdpSettings* settings);

#endif /* FREERDP_CLIENT_COMPATIBILITY */

