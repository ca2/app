/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * FreeRDP Client Command-Line Interface
 *
 * Copyright 2012 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 * Copyright 2014 Norbert Federa <norbert.federa@thincast.com>
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>

#include <winpr/crt.h>
#include <winpr/cmdline.h>

#include <freerdp/addin.h>
#include <freerdp/settings.h>
#include <freerdp/client/channels.h>
#include <freerdp/crypto/crypto.h>
#include <freerdp/locale/keyboard.h>


#include <freerdp/client/cmdline.h>
//#include <freerdp/version.h>

#include "compatibility.h"

#include <freerdp/log.h>
#define TAG CLIENT_TAG("common.cmdline")

COMMAND_LINE_ARGUMENT_A args[] =
{
	{ "v", COMMAND_LINE_VALUE_REQUIRED, "<server>[:port]", nullptr, nullptr, -1, nullptr, "Server hostname" },
	{ "port", COMMAND_LINE_VALUE_REQUIRED, "<number>", nullptr, nullptr, -1, nullptr, "Server port" },
	{ "w", COMMAND_LINE_VALUE_REQUIRED, "<width>", "1024", nullptr, -1, nullptr, "Width" },
	{ "h", COMMAND_LINE_VALUE_REQUIRED, "<height>", "768", nullptr, -1, nullptr, "Height" },
	{ "int_size", COMMAND_LINE_VALUE_REQUIRED, "<width>x<height> or <percent>%", "1024x768", nullptr, -1, nullptr, "Screen int_size" },
	{ "f", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "Fullscreen mode" },
	{ "bpp", COMMAND_LINE_VALUE_REQUIRED, "<depth>", "16", nullptr, -1, nullptr, "Session bpp (color depth)" },
	{ "kbd", COMMAND_LINE_VALUE_REQUIRED, "0x<on_layout atom> or <on_layout name>", nullptr, nullptr, -1, nullptr, "Keyboard on_layout" },
	{ "kbd-list", COMMAND_LINE_VALUE_FLAG | COMMAND_LINE_PRINT, nullptr, nullptr, nullptr, -1, nullptr, "List keyboard layouts" },
	{ "kbd-type", COMMAND_LINE_VALUE_REQUIRED, "<type atom>", nullptr, nullptr, -1, nullptr, "Keyboard type" },
	{ "kbd-subtype", COMMAND_LINE_VALUE_REQUIRED, "<subtype atom>", nullptr, nullptr, -1, nullptr, "Keyboard subtype" },
	{ "kbd-fn-key", COMMAND_LINE_VALUE_REQUIRED, "<function key count>", nullptr, nullptr, -1, nullptr, "Keyboard function key count" },
	{ "admin", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, "console", "Admin (or console) session" },
	{ "restricted-admin", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, "restrictedAdmin", "Restricted admin mode" },
	{ "pth", COMMAND_LINE_VALUE_REQUIRED, "<password hash>", nullptr, nullptr, -1, "pass-the-hash", "Pass the hash (restricted admin mode)" },
	{ "client-hostname", COMMAND_LINE_VALUE_REQUIRED, "<name>", nullptr, nullptr, -1, nullptr, "Client Hostname to send to server" },
	{ "multimon", COMMAND_LINE_VALUE_OPTIONAL, nullptr, nullptr, nullptr, -1, nullptr, "Use multiple monitors" },
	{ "span", COMMAND_LINE_VALUE_OPTIONAL, nullptr, nullptr, nullptr, -1, nullptr, "Span screen over multiple monitors" },
	{ "workarea", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "Use available work area" },
	{ "monitors", COMMAND_LINE_VALUE_REQUIRED, "<0,1,2...>", nullptr, nullptr, -1, nullptr, "Select monitors to use" },
	{ "monitor-list", COMMAND_LINE_VALUE_FLAG | COMMAND_LINE_PRINT, nullptr, nullptr, nullptr, -1, nullptr, "List detected monitors" },
	{ "t", COMMAND_LINE_VALUE_REQUIRED, "<title>", nullptr, nullptr, -1, "title", "Window title" },
	{ "decorations", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "Window decorations" },
	{ "smart-sizing", COMMAND_LINE_VALUE_OPTIONAL, "<width>x<height>", nullptr, nullptr, -1, nullptr, "Scale remote desktop to window int_size" },
	{ "a", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, "addin", "Addin" },
	{ "vc", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "Static virtual channel" },
	{ "dvc", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "Dynamic virtual channel" },
	{ "u", COMMAND_LINE_VALUE_REQUIRED, "[<domain>\\]<user> or <user>[@<domain>]", nullptr, nullptr, -1, nullptr, "Username" },
	{ "p", COMMAND_LINE_VALUE_REQUIRED, "<password>", nullptr, nullptr, -1, nullptr, "Password" },
	{ "d", COMMAND_LINE_VALUE_REQUIRED, "<domain>", nullptr, nullptr, -1, nullptr, "Domain" },
	{ "g", COMMAND_LINE_VALUE_OPTIONAL, "<gateway>[:port]", nullptr, nullptr, -1, nullptr, "Gateway Hostname" },
	{ "gu", COMMAND_LINE_VALUE_REQUIRED, "[<domain>\\]<user> or <user>[@<domain>]", nullptr, nullptr, -1, nullptr, "Gateway username" },
	{ "gp", COMMAND_LINE_VALUE_REQUIRED, "<password>", nullptr, nullptr, -1, nullptr, "Gateway password" },
	{ "gd", COMMAND_LINE_VALUE_REQUIRED, "<domain>", nullptr, nullptr, -1, nullptr, "Gateway domain" },
	{ "gt", COMMAND_LINE_VALUE_REQUIRED, "<rpc|http|auto>", nullptr, nullptr, -1, nullptr, "Gateway transport type" },
	{ "gateway-usage-method", COMMAND_LINE_VALUE_REQUIRED, "<direct|detect>", nullptr, nullptr, -1, "gum", "Gateway usage method" },
	{ "load-balance-info", COMMAND_LINE_VALUE_REQUIRED, "<info string>", nullptr, nullptr, -1, nullptr, "Load balance info" },
	{ "app", COMMAND_LINE_VALUE_REQUIRED, "<executable path> or <||alias>", nullptr, nullptr, -1, nullptr, "Remote application program" },
	{ "app-name", COMMAND_LINE_VALUE_REQUIRED, "<app name>", nullptr, nullptr, -1, nullptr, "Remote application name for user interface" },
	{ "app-icon", COMMAND_LINE_VALUE_REQUIRED, "<icon path>", nullptr, nullptr, -1, nullptr, "Remote application icon for user interface" },
	{ "app-cmd", COMMAND_LINE_VALUE_REQUIRED, "<parameters>", nullptr, nullptr, -1, nullptr, "Remote application command-line parameters" },
	{ "app-file", COMMAND_LINE_VALUE_REQUIRED, "<file name>", nullptr, nullptr, -1, nullptr, "File to open with remote application" },
	{ "app-guid", COMMAND_LINE_VALUE_REQUIRED, "<app guid>", nullptr, nullptr, -1, nullptr, "Remote application GUID" },
	{ "compression", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, "z", "Compression" },
	{ "compression-level", COMMAND_LINE_VALUE_REQUIRED, "<level>", nullptr, nullptr, -1, nullptr, "Compression level (0,1,2)" },
	{ "shell", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "Alternate shell" },
	{ "shell-dir", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "Shell working directory" },
	{ "sound", COMMAND_LINE_VALUE_OPTIONAL, "[sys][dev][format][rate][channel][latency][quality]", nullptr, nullptr, -1, "audio", "Audio output (sound)" },
	{ "microphone", COMMAND_LINE_VALUE_OPTIONAL, "[sys][dev][format][rate][channel]", nullptr, nullptr, -1, "mic", "Audio input (microphone)" },
	{ "audio-mode", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "Audio output mode" },
	{ "multimedia", COMMAND_LINE_VALUE_OPTIONAL, "[sys][dev][decoder]", nullptr, nullptr, -1, "mmr", "Redirect multimedia (video)" },
	{ "network", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "Network connection type" },
	{ "drive", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "Redirect drive" },
	{ "drives", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Redirect all drives" },
	{ "home-drive", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Redirect home drive" },
	{ "clipboard", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Redirect clipboard" },
	{ "serial", COMMAND_LINE_VALUE_OPTIONAL, nullptr, nullptr, nullptr, -1, "tty", "Redirect serial device" },
	{ "parallel", COMMAND_LINE_VALUE_OPTIONAL, nullptr, nullptr, nullptr, -1, nullptr, "Redirect parallel device" },
	{ "smartcard", COMMAND_LINE_VALUE_OPTIONAL, nullptr, nullptr, nullptr, -1, nullptr, "Redirect smartcard device" },
	{ "printer", COMMAND_LINE_VALUE_OPTIONAL, nullptr, nullptr, nullptr, -1, nullptr, "Redirect printer device" },
	{ "usb", COMMAND_LINE_VALUE_REQUIRED, "[dbg][dev][atom|addr][auto]", nullptr, nullptr, -1, nullptr, "Redirect USB device" },
	{ "multitouch", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Redirect multitouch input" },
	{ "gestures", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Consume multitouch input locally" },
	{ "echo", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, "echo", "Echo channel" },
	{ "disp", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "Display control" },
	{ "fonts", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Smooth fonts (ClearType)" },
	{ "aero", COMMAND_LINE_VALUE_BOOL, nullptr, nullptr, BoolValueFalse, -1, nullptr, "Desktop composition" },
	{ "window-drag", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Full window drag" },
	{ "menu-anims", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Menu animations" },
	{ "themes", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "Themes" },
	{ "wallpaper", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "Wallpaper" },
	{ "gdi", COMMAND_LINE_VALUE_REQUIRED, "<sw|hw>", nullptr, nullptr, -1, nullptr, "GDI rendering" },
	{ "gfx", COMMAND_LINE_VALUE_OPTIONAL, nullptr, nullptr, nullptr, -1, nullptr, "RDP8 graphics pipeline (experimental)" },
	{ "gfx-thin-client", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "RDP8 graphics pipeline thin client mode" },
	{ "gfx-small-cache", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "RDP8 graphics pipeline small cache mode" },
	{ "gfx-progressive", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "RDP8 graphics pipeline progressive codec" },
	{ "gfx-h264", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "RDP8.1 graphics pipeline H264 codec" },
	{ "rfx", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "RemoteFX" },
	{ "rfx-mode", COMMAND_LINE_VALUE_REQUIRED, "<image|video>", nullptr, nullptr, -1, nullptr, "RemoteFX mode" },
	{ "frame-ack", COMMAND_LINE_VALUE_REQUIRED, "<number>", nullptr, nullptr, -1, nullptr, "Frame acknowledgement" },
	{ "nsc", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, "nscodec", "NSCodec" },
	{ "jpeg", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "JPEG codec" },
	{ "jpeg-quality", COMMAND_LINE_VALUE_REQUIRED, "<percentage>", nullptr, nullptr, -1, nullptr, "JPEG quality" },
	{ "nego", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "protocol security negotiation" },
	{ "sec", COMMAND_LINE_VALUE_REQUIRED, "<rdp|tls|nla|ext>", nullptr, nullptr, -1, nullptr, "force specific protocol security" },
	{ "sec-rdp", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "rdp protocol security" },
	{ "sec-tls", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "tls protocol security" },
	{ "sec-nla", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "nla protocol security" },
	{ "sec-ext", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "nla extended protocol security" },
	{ "tls-ciphers", COMMAND_LINE_VALUE_REQUIRED, "<netmon|ma|ciphers>", nullptr, nullptr, -1, nullptr, "Allowed TLS ciphers" },
	{ "cert-name", COMMAND_LINE_VALUE_REQUIRED, "<name>", nullptr, nullptr, -1, nullptr, "certificate name" },
	{ "cert-ignore", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "ignore certificate" },
	{ "pcb", COMMAND_LINE_VALUE_REQUIRED, "<blob>", nullptr, nullptr, -1, nullptr, "Preconnection Blob" },
	{ "pcid", COMMAND_LINE_VALUE_REQUIRED, "<atom>", nullptr, nullptr, -1, nullptr, "Preconnection Id" },
	{ "spn-class", COMMAND_LINE_VALUE_REQUIRED, "<service class>", nullptr, nullptr, -1, nullptr, "SPN authentication service class" },
	{ "credentials-delegation", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Disable credentials delegation" },
	{ "vmconnect", COMMAND_LINE_VALUE_OPTIONAL, "<vmid>", nullptr, nullptr, -1, nullptr, "Hyper-V console (use port 2179, disable negotiation)" },
	{ "authentication", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "authentication (hack!)" },
	{ "encryption", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "encryption (hack!)" },
	{ "grab-keyboard", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "grab keyboard" },
	{ "toggle-fullscreen", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "Alt+Ctrl+Enter toggles fullscreen" },
	{ "mouse-motion", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "mouse-motion" },
	{ "parent-window", COMMAND_LINE_VALUE_REQUIRED, "<window atom>", nullptr, nullptr, -1, nullptr, "Parent window atom" },
	{ "bitmap-cache", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "bitmap cache" },
	{ "offscreen-cache", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "offscreen bitmap cache" },
	{ "glyph-cache", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "glyph cache" },
	{ "codec-cache", COMMAND_LINE_VALUE_REQUIRED, "<rfx|nsc|jpeg>", nullptr, nullptr, -1, nullptr, "bitmap codec cache" },
	{ "fast-path", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueTrue, nullptr, -1, nullptr, "fast-path input/output" },
	{ "maximum-fast-path-int_size", COMMAND_LINE_VALUE_OPTIONAL, "<int_size>", nullptr, nullptr, -1, nullptr, "maximum fast-path update int_size" },
	{ "async-input", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "asynchronous input" },
	{ "async-update", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "asynchronous update" },
	{ "async-transport", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "asynchronous transport (unstable)" },
	{ "async-channels", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "asynchronous channels (unstable)" },
	{ "wm-class", COMMAND_LINE_VALUE_REQUIRED, "<class name>", nullptr, nullptr, -1, nullptr, "set the WM_CLASS hint for the window instance" },
	{ "version", COMMAND_LINE_VALUE_FLAG | COMMAND_LINE_PRINT_VERSION, nullptr, nullptr, nullptr, -1, nullptr, "print version" },
	{ "help", COMMAND_LINE_VALUE_FLAG | COMMAND_LINE_PRINT_HELP, nullptr, nullptr, nullptr, -1, "?", "print help" },
	{ "play-rfx", COMMAND_LINE_VALUE_REQUIRED, "<pcap file>", nullptr, nullptr, -1, nullptr, "Replay rfx pcap file" },
	{ "auth-only", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Authenticate only." },
	{ "auto-reconnect", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Automatic reconnection" },
	{ "reconnect-cookie", COMMAND_LINE_VALUE_REQUIRED, "<base64 cookie>", nullptr, nullptr, -1, nullptr, "Pass base64 reconnect cookie to the connection" },
	{ "print-reconnect-cookie", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Print base64 reconnect cookie after connecting" },
	{ "heartbeat", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Support heartbeat PDUs" },
	{ "multitransport", COMMAND_LINE_VALUE_BOOL, nullptr, BoolValueFalse, nullptr, -1, nullptr, "Support multitransport protocol" },
	{ "assistance", COMMAND_LINE_VALUE_REQUIRED, "<password>", nullptr, nullptr, -1, nullptr, "Remote assistance password" },
	{ "encryption-methods", COMMAND_LINE_VALUE_REQUIRED, "<40,56,128,FIPS>", nullptr, nullptr, -1, nullptr, "RDP standard security encryption methods" },
	{ "from-stdin", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "Read credentials from stdin, do not use defaults." },
	{ nullptr, 0, nullptr, nullptr, nullptr, -1, nullptr, nullptr }
};

BOOL freerdp_client_print_version()
{
//	printf("This is FreeRDP version %s (git %s)\n", FREERDP_VERSION_FULL, GIT_REVISION);
	return 1;
}

BOOL freerdp_client_print_command_line_help(int argc, char** argv)
{
	char* str;
	int length;
	COMMAND_LINE_ARGUMENT_A* arg;

	printf("\n");
	printf("FreeRDP - A Free Remote Desktop Protocol Implementation\n");
	printf("See www.freerdp.com for more information\n");
	printf("\n");

	printf("Usage: %s [file] [options] [/v:<server>[:port]]\n", argv[0]);
	printf("\n");

	printf("Syntax:\n");
	printf("    /flag (enables flag)\n");
	printf("    /option:<value> (specifies option with value)\n");
	printf("    +toggle -toggle (enables or disables toggle, where '/' is a synonym of '+')\n");
	printf("\n");

	arg = args;

	do
	{
		if (arg->Flags & COMMAND_LINE_VALUE_FLAG)
		{
			printf("    %s", "/");
			printf("%-20s", arg->Name);
			printf("\t%s\n", arg->Text);
		}
		else if ((arg->Flags & COMMAND_LINE_VALUE_REQUIRED) || (arg->Flags & COMMAND_LINE_VALUE_OPTIONAL))
		{
			printf("    %s", "/");

			if (arg->Format)
			{
				length = (int)(strlen(arg->Name) + strlen(arg->Format) + 2);
				str = (char*) calloc(length + 1UL, sizeof(char));
				if (!str)
					return -1;
				sprintf_s(str, length + 1, "%s:%s", arg->Name, arg->Format);
				printf("%-20s", str);
				free(str);
			}
			else
			{
				printf("%-20s", arg->Name);
			}

			printf("\t%s\n", arg->Text);
		}
		else if (arg->Flags & COMMAND_LINE_VALUE_BOOL)
		{
			length = (int) strlen(arg->Name) + 32;
			str = (char*) calloc(length + 1UL, sizeof(char));
			if (!str)
				return -1;
			sprintf_s(str, length + 1, "%s (default:%s)", arg->Name,
					arg->Default ? "on" : "off");

			printf("    %s", arg->Default ? "-" : "+");

			printf("%-20s", str);
			free(str);

			printf("\t%s\n", arg->Text);
		}
	}
	while ((arg = CommandLineFindNextArgumentA(arg)) != nullptr);

	printf("\n");

	printf("Examples:\n");
	printf("    xfreerdp connection.rdp /p:Pwd123! /f\n");
	printf("    xfreerdp /u:CONTOSO\\JohnDoe /p:Pwd123! /v:rdp.contoso.com\n");
	printf("    xfreerdp /u:JohnDoe /p:Pwd123! /w:1366 /h:768 /v:192.168.1.100:4489\n");
	printf("    xfreerdp /u:JohnDoe /p:Pwd123! /vmconnect:C824F53E-95D2-46C6-9A18-23A5BB403532 /v:192.168.1.100\n");
	printf("\n");

	printf("Clipboard Redirection: +clipboard\n");
	printf("\n");

	printf("Drive Redirection: /drive:home,/home/user\n");
	printf("Smartcard Redirection: /smartcard:<device>\n");
	printf("serial Port Redirection: /serial:<name>,<device>,[SerCx2|SerCx|serial],[permissive]\n");
	printf("serial Port Redirection: /serial:COM1,/dev/ttyS0\n");
	printf("Parallel Port Redirection: /parallel:<device>\n");
	printf("Printer Redirection: /printer:<device>,<driver>\n");
	printf("\n");

	printf("Audio Output Redirection: /sound:sys:oss,dev:1,format:1\n");
	printf("Audio Output Redirection: /sound:sys:alsa\n");
	printf("Audio Input Redirection: /microphone:sys:oss,dev:1,format:1\n");
	printf("Audio Input Redirection: /microphone:sys:alsa\n");
	printf("\n");

	printf("Multimedia Redirection: /multimedia:sys:oss,dev:/dev/dsp1,decoder:ffmpeg\n");
	printf("Multimedia Redirection: /multimedia:sys:alsa\n");
	printf("USB Device Redirection: /usb:atom,dev:054c:0268\n");
	printf("\n");

	printf("More documentation is coming, in the meantime consult source files\n");
	printf("\n");

	return 1;
}

int freerdp_client_command_line_pre_filter(void* context, int index, int argc, const ::string &* argv)
{
	if (index == 1)
	{
		int length;
		rdpSettings* settings;

		length = (int) strlen(argv[index]);

		if (length > 4)
		{
			if (_stricmp(&(argv[index])[length - 4], ".rdp") == 0)
			{
				settings = (rdpSettings*) context;
				if (!(settings->ConnectionFile = _strdup(argv[index])))
					return COMMAND_LINE_ERROR_MEMORY;

				return 1;
			}
		}

		if (length > 13)
		{
			if (_stricmp(&(argv[index])[length - 13], ".msrcIncident") == 0)
			{
				settings = (rdpSettings*) context;
				if (!(settings->AssistanceFile = _strdup(argv[index])))
					return COMMAND_LINE_ERROR_MEMORY;

				return 1;
			}
		}
	}

	return 0;
}

BOOL freerdp_client_add_device_channel(rdpSettings* settings, int count, char** params)
{
	if (strcmp(params[0], "drive") == 0)
	{
		RDPDR_DRIVE* drive;

		if (count < 3)
			return -1;

		settings->DeviceRedirection = true;

		drive = (RDPDR_DRIVE*) calloc(1, sizeof(RDPDR_DRIVE));

		if (!drive)
			return -1;

		drive->Type = RDPDR_DTYP_FILESYSTEM;

		if (count > 1)
		{
			if (!(drive->Name = _strdup(params[1])))
			{
				free(drive);
				return -1;
			}
		}

		if (count > 2)
		{
			if (!(drive->Path = _strdup(params[2])))
			{
				free(drive->Name);
				free(drive);
				return -1;
			}
		}

		if (!freerdp_device_collection_add(settings, (RDPDR_DEVICE*) drive))
		{
			free(drive->Path);
			free(drive->Name);
			free(drive);
			return -1;
		}

		return 1;
	}
	else if (strcmp(params[0], "printer") == 0)
	{
		RDPDR_PRINTER* printer;

		if (count < 1)
			return -1;

		settings->RedirectPrinters = true;
		settings->DeviceRedirection = true;

		if (count > 1)
		{
			printer = (RDPDR_PRINTER*) calloc(1, sizeof(RDPDR_PRINTER));

			if (!printer)
				return -1;

			printer->Type = RDPDR_DTYP_PRINT;

			if (count > 1)
			{
				if (!(printer->Name = _strdup(params[1])))
				{
					free(printer);
					return -1;
				}
			}

			if (count > 2)
			{
				if (!(printer->DriverName = _strdup(params[2])))
				{
					free(printer->Name);
					free(printer);
					return -1;
				}
			}


			if (!freerdp_device_collection_add(settings, (RDPDR_DEVICE*) printer))
			{
				free(printer->DriverName);
				free(printer->Name);
				free(printer);
				return -1;
			}

		}

		return 1;
	}
	else if (strcmp(params[0], "smartcard") == 0)
	{
		RDPDR_SMARTCARD* smartcard;

		if (count < 1)
			return -1;

		settings->RedirectSmartCards = true;
		settings->DeviceRedirection = true;

		if (count > 1)
		{
			smartcard = (RDPDR_SMARTCARD*) calloc(1, sizeof(RDPDR_SMARTCARD));

			if (!smartcard)
				return -1;

			smartcard->Type = RDPDR_DTYP_SMARTCARD;

			if (count > 1)
			{
				if (!(smartcard->Name = _strdup(params[1])))
				{
					free(smartcard);
					return -1;
				}
			}

			if (count > 2)
			{
				if (!(smartcard->Path = _strdup(params[2])))
				{
					free(smartcard->Name);
					free(smartcard);
					return -1;
				}
			}
			if (!freerdp_device_collection_add(settings, (RDPDR_DEVICE*) smartcard))
			{
				free(smartcard->Path);
				free(smartcard->Name);
				free(smartcard);
				return -1;
			}
		}

		return 1;
	}
	else if (strcmp(params[0], "serial") == 0)
	{
		RDPDR_SERIAL* serial;

		if (count < 1)
			return -1;

		settings->RedirectSerialPorts = true;
		settings->DeviceRedirection = true;

		serial = (RDPDR_SERIAL*) calloc(1, sizeof(RDPDR_SERIAL));

		if (!serial)
			return -1;

		serial->Type = RDPDR_DTYP_SERIAL;

		if (count > 1)
		{
			if (!(serial->Name = _strdup(params[1])))
			{
				free(serial);
				return -1;
			}
		}

		if (count > 2)
		{
			if (!(serial->Path = _strdup(params[2])))
			{
				free(serial->Name);
				free(serial);
				return -1;
			}
		}

		if (count > 3)
		{
			if (!(serial->Driver = _strdup(params[3])))
			{
				free(serial->Path);
				free(serial->Name);
				free(serial);
				return -1;
			}
		}

		if (count > 4)
		{
			if (!(serial->Permissive = _strdup(params[4])))
			{
				free(serial->Driver);
				free(serial->Path);
				free(serial->Name);
				free(serial);
				return -1;
			}
		}

		if (!freerdp_device_collection_add(settings, (RDPDR_DEVICE*) serial))
		{
			free(serial->Permissive);
			free(serial->Driver);
			free(serial->Path);
			free(serial->Name);
			free(serial);
			return -1;
		}

		return 1;
	}
	else if (strcmp(params[0], "parallel") == 0)
	{
		RDPDR_PARALLEL* parallel;

		if (count < 1)
			return -1;

		settings->RedirectParallelPorts = true;
		settings->DeviceRedirection = true;

		parallel = (RDPDR_PARALLEL*) calloc(1, sizeof(RDPDR_PARALLEL));

		if (!parallel)
			return -1;

		parallel->Type = RDPDR_DTYP_PARALLEL;

		if (count > 1)
		{
			if (!(parallel->Name = _strdup(params[1])))
			{
				free(parallel);
				return -1;
			}
		}

		if (count > 2)
		{
			if (!(parallel->Path = _strdup(params[2])))
			{
				free(parallel->Name);
				free(parallel);
				return -1;
			}
		}

		if (!freerdp_device_collection_add(settings, (RDPDR_DEVICE*) parallel))
		{
			free(parallel->Path);
			free(parallel->Name);
			free(parallel);
			return -1;
		}

		return 1;
	}

	return 0;
}

BOOL freerdp_client_add_static_channel(rdpSettings* settings, int count, char** params)
{
	int index;
	ADDIN_ARGV* args;

	args = (ADDIN_ARGV*) calloc(1, sizeof(ADDIN_ARGV));
	if (!args)
		return -1;

	args->argc = count;
	args->argv = (char**) calloc(args->argc, sizeof(char*));
	if (!args->argv)
		goto error_argv;

	for (index = 0; index < args->argc; index++)
	{
		args->argv[index] = _strdup(params[index]);
		if (!args->argv[index])
		{
			for (--index; index >= 0; --index)
				free(args->argv[index]);

			goto error_argv_strdup;
		}
	}

	if (!freerdp_static_channel_collection_add(settings, args))
		goto error_argv_index;

	return 0;

error_argv_index:
	for (index = 0; index < args->argc; index++)
		free(args->argv[index]);
error_argv_strdup:
	free(args->argv);
error_argv:
	free(args);
	return -1;
}

BOOL freerdp_client_add_dynamic_channel(rdpSettings* settings, int count, char** params)
{
	int index;
	ADDIN_ARGV* args;

	args = (ADDIN_ARGV*) malloc(sizeof(ADDIN_ARGV));
	if (!args)
		return -1;

	args->argc = count;
	args->argv = (char**) calloc(args->argc, sizeof(char*));
	if (!args->argv)
		goto error_argv;

	for (index = 0; index < args->argc; index++)
	{
		args->argv[index] = _strdup(params[index]);
		if (!args->argv[index])
		{
			for (--index; index >= 0; --index)
				free(args->argv[index]);

			goto error_argv_strdup;
		}
	}

	if (!freerdp_dynamic_channel_collection_add(settings, args))
		goto error_argv_index;

	return 0;

error_argv_index:
	for (index = 0; index < args->argc; index++)
		free(args->argv[index]);
error_argv_strdup:
	free(args->argv);
error_argv:
	free(args);
	return -1;
}

static char** freerdp_command_line_parse_comma_separated_values(char* list, int* count)
{
	char** p;
	char* str;
	int nArgs;
	int index;
	int nCommas;

	nCommas = 0;

	assert(nullptr != count);

	*count = 0;
	if (!list)
		return nullptr;

	for (index = 0; list[index]; index++)
		nCommas += (list[index] == ',') ? 1 : 0;

	nArgs = nCommas + 1;
	p = (char**) calloc((nArgs + 1UL), sizeof(char*));
	if (!p)
		return nullptr;

	str = (char*) list;

	p[0] = str;

	for (index = 1; index < nArgs; index++)
	{
		p[index] = strchr(p[index - 1], ',');
		*p[index] = '\0';
		p[index]++;
	}

	p[index] = str + strlen(str);

	*count = nArgs;

	return p;
}

static char** freerdp_command_line_parse_comma_separated_values_offset(char* list, int* count)
{
	char** p;
	char** t;

	p = freerdp_command_line_parse_comma_separated_values(list, count);

	t = (char**) realloc(p, sizeof(char*) * (*count + 1));
	if (!t)
		return nullptr;
	p = t;
	if (count > 0)
		MoveMemory(&p[1], p, sizeof(char*) * *count);
	(*count)++;

	return p;
}

int freerdp_client_command_line_post_filter(void* context, COMMAND_LINE_ARGUMENT_A* arg)
{
	rdpSettings* settings = (rdpSettings*) context;
	int status = 0;

	CommandLineSwitchStart(arg)

	CommandLineSwitchCase(arg, "a")
	{
		char** p;
		int count;

		p = freerdp_command_line_parse_comma_separated_values(arg->Value, &count);

		if (freerdp_client_add_device_channel(settings, count, p) > 0)
		{
			settings->DeviceRedirection = true;
		}

		free(p);
	}
	CommandLineSwitchCase(arg, "vc")
	{
		char** p;
		int count;

		p = freerdp_command_line_parse_comma_separated_values(arg->Value, &count);

		status = freerdp_client_add_static_channel(settings, count, p);

		free(p);
	}
	CommandLineSwitchCase(arg, "dvc")
	{
		char** p;
		int count;

		p = freerdp_command_line_parse_comma_separated_values(arg->Value, &count);

		freerdp_client_add_dynamic_channel(settings, count, p);

		free(p);
	}
	CommandLineSwitchCase(arg, "drive")
	{
		char** p;
		int count;

		p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
		p[0] = "drive";

		freerdp_client_add_device_channel(settings, count, p);

		free(p);
	}
	CommandLineSwitchCase(arg, "serial")
	{
		char** p;
		int count;

		p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
		p[0] = "serial";

		freerdp_client_add_device_channel(settings, count, p);

		free(p);
	}
	CommandLineSwitchCase(arg, "parallel")
	{
		char** p;
		int count;

		p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
		p[0] = "parallel";

		freerdp_client_add_device_channel(settings, count, p);

		free(p);
	}
	CommandLineSwitchCase(arg, "smartcard")
	{
		char** p;
		int count;

		p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
		p[0] = "smartcard";

		freerdp_client_add_device_channel(settings, count, p);

		free(p);
	}
	CommandLineSwitchCase(arg, "printer")
	{
		if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
		{
			char** p;
			int count;

			p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
			p[0] = "printer";

			freerdp_client_add_device_channel(settings, count, p);

			free(p);
		}
		else
		{
			char* p[1];
			int count;

			count = 1;
			p[0] = "printer";

			freerdp_client_add_device_channel(settings, count, p);
		}
	}
	CommandLineSwitchCase(arg, "usb")
	{
		char** p;
		int count;

		p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
		p[0] = "urbdrc";

		freerdp_client_add_dynamic_channel(settings, count, p);

		free(p);
	}
	CommandLineSwitchCase(arg, "multitouch")
	{
		settings->MultiTouchInput = true;
	}
	CommandLineSwitchCase(arg, "gestures")
	{
		settings->MultiTouchGestures = true;
	}
	CommandLineSwitchCase(arg, "echo")
	{
		settings->SupportEchoChannel = true;
	}
	CommandLineSwitchCase(arg, "disp")
	{
		settings->SupportDisplayControl = true;
	}
	CommandLineSwitchCase(arg, "sound")
	{
		if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
		{
			char** p;
			int count;

			p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
			p[0] = "rdpsnd";

			status = freerdp_client_add_static_channel(settings, count, p);

			free(p);
		}
		else
		{
			char* p[1];
			int count;

			count = 1;
			p[0] = "rdpsnd";

			status = freerdp_client_add_static_channel(settings, count, p);
		}
	}
	CommandLineSwitchCase(arg, "microphone")
	{
		if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
		{
			char** p;
			int count;

			p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
			p[0] = "audin";

			freerdp_client_add_dynamic_channel(settings, count, p);

			free(p);
		}
		else
		{
			char* p[1];
			int count;

			count = 1;
			p[0] = "audin";

			freerdp_client_add_dynamic_channel(settings, count, p);
		}
	}
	CommandLineSwitchCase(arg, "multimedia")
	{
		if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
		{
			char** p;
			int count;

			p = freerdp_command_line_parse_comma_separated_values_offset(arg->Value, &count);
			p[0] = "tsmf";

			freerdp_client_add_dynamic_channel(settings, count, p);

			free(p);
		}
		else
		{
			char* p[1];
			int count;

			count = 1;
			p[0] = "tsmf";

			freerdp_client_add_dynamic_channel(settings, count, p);
		}
	}
	CommandLineSwitchCase(arg, "heartbeat")
	{
		settings->SupportHeartbeatPdu = true;
	}
	CommandLineSwitchCase(arg, "multitransport")
	{
		settings->SupportMultitransport = true;
		settings->MultitransportFlags = (TRANSPORT_TYPE_UDP_FECR | TRANSPORT_TYPE_UDP_FECL | TRANSPORT_TYPE_UDP_PREFERRED);
	}

	CommandLineSwitchEnd(arg)

	return status;
}

BOOL freerdp_parse_username(char* username, char** user, char** domain)
{
	char* p;
	int length = 0;

	p = strchr(username, '\\');

	*user = nullptr;
	*domain = nullptr;

	if (p)
	{
		length = (int) (p - username);
		*user = _strdup(&p[1]);
		if (!*user)
			return -1;

		*domain = (char*) calloc(length + 1UL, sizeof(char));
		if (!*domain)
		{
			free (*user);
			*user = nullptr;
			return -1;
		}

		strncpy(*domain, username, length);
		(*domain)[length] = '\0';
	}
	else if (username)
	{
		/* Do not break up the name for '@'; both credSSP and the
		 * ClientInfo PDU expect 'user@corp.net' to be transmitted
		 * as username 'user@corp.net', domain empty (not nullptr!).
		 */
		*user = _strdup(username);
		if (!*user)
			return -1;

		*domain = _strdup("\0");

		if (!*domain)
		{
			free(*user);
			*user = nullptr;
			return -1;
		}
	}
	else
			return -1;

	return 0;
}

BOOL freerdp_parse_hostname(char* hostname, char** host, int* port)
{
	char* p;
	int length;

	p = strrchr(hostname, ':');

	if (p)
	{
		length = (p - hostname);
		*host = (char*) calloc(length + 1UL, sizeof(char));

		if (!(*host))
			return -1;

		CopyMemory(*host, hostname, length);
		(*host)[length] = '\0';
		*port = atoi(p + 1);
	}
	else
	{
		*host = _strdup(hostname);

		if (!(*host))
			return -1;

		*port = -1;
	}

	return 0;
}

BOOL freerdp_set_connection_type(rdpSettings* settings, int type)
{
	settings->ConnectionType = type;

	if (type == CONNECTION_TYPE_MODEM)
	{
		settings->DisableWallpaper = true;
		settings->AllowFontSmoothing = false;
		settings->AllowDesktopComposition = false;
		settings->DisableFullWindowDrag = true;
		settings->DisableMenuAnims = true;
		settings->DisableThemes = true;
	}
	else if (type == CONNECTION_TYPE_BROADBAND_LOW)
	{
		settings->DisableWallpaper = true;
		settings->AllowFontSmoothing = false;
		settings->AllowDesktopComposition = false;
		settings->DisableFullWindowDrag = true;
		settings->DisableMenuAnims = true;
		settings->DisableThemes = false;
	}
	else if (type == CONNECTION_TYPE_SATELLITE)
	{
		settings->DisableWallpaper = true;
		settings->AllowFontSmoothing = false;
		settings->AllowDesktopComposition = true;
		settings->DisableFullWindowDrag = true;
		settings->DisableMenuAnims = true;
		settings->DisableThemes = false;
	}
	else if (type == CONNECTION_TYPE_BROADBAND_HIGH)
	{
		settings->DisableWallpaper = true;
		settings->AllowFontSmoothing = false;
		settings->AllowDesktopComposition = true;
		settings->DisableFullWindowDrag = true;
		settings->DisableMenuAnims = true;
		settings->DisableThemes = false;
	}
	else if (type == CONNECTION_TYPE_WAN)
	{
		settings->DisableWallpaper = false;
		settings->AllowFontSmoothing = true;
		settings->AllowDesktopComposition = true;
		settings->DisableFullWindowDrag = false;
		settings->DisableMenuAnims = false;
		settings->DisableThemes = false;
	}
	else if (type == CONNECTION_TYPE_LAN)
	{
		settings->DisableWallpaper = false;
		settings->AllowFontSmoothing = true;
		settings->AllowDesktopComposition = true;
		settings->DisableFullWindowDrag = false;
		settings->DisableMenuAnims = false;
		settings->DisableThemes = false;
	}
	else if (type == CONNECTION_TYPE_AUTODETECT)
	{
		settings->DisableWallpaper = false;
		settings->AllowFontSmoothing = true;
		settings->AllowDesktopComposition = true;
		settings->DisableFullWindowDrag = false;
		settings->DisableMenuAnims = false;
		settings->DisableThemes = false;

		settings->NetworkAutoDetect = true;
	}

	return 0;
}

int freerdp_map_keyboard_layout_name_to_id(char* name)
{
	int i;
	int atom = 0;
	RDP_KEYBOARD_LAYOUT* layouts;

	layouts = freerdp_keyboard_get_layouts(RDP_KEYBOARD_LAYOUT_TYPE_STANDARD);
	if (!layouts)
		return -1;

	for (i = 0; layouts[i].code; i++)
	{
		if (_stricmp(layouts[i].name, name) == 0)
			atom = layouts[i].code;
	}

	free(layouts);

	if (atom)
		return atom;

	layouts = freerdp_keyboard_get_layouts(RDP_KEYBOARD_LAYOUT_TYPE_VARIANT);
	if (!layouts)
		return -1;

	for (i = 0; layouts[i].code; i++)
	{
		if (_stricmp(layouts[i].name, name) == 0)
			atom = layouts[i].code;
	}

	free(layouts);

	if (atom)
		return atom;

	layouts = freerdp_keyboard_get_layouts(RDP_KEYBOARD_LAYOUT_TYPE_IME);
	if (!layouts)
		return -1;

	for (i = 0; layouts[i].code; i++)
	{
		if (_stricmp(layouts[i].name, name) == 0)
			atom = layouts[i].code;
	}

	free(layouts);

	if (atom)
		return atom;

	return 0;
}

int freerdp_detect_command_line_pre_filter(void* context, int index, int argc, const ::string &* argv)
{
	int length;

	if (index == 1)
	{
		length = (int) strlen(argv[index]);

		if (length > 4)
		{
			if (_stricmp(&(argv[index])[length - 4], ".rdp") == 0)
			{
				return 1;
			}
		}

		if (length > 13)
		{
			if (_stricmp(&(argv[index])[length - 13], ".msrcIncident") == 0)
			{
				return 1;
			}
		}
	}

	return 0;
}

int freerdp_detect_windows_style_command_line_syntax(int argc, char** argv,
	int* count, BOOL ignoreUnknown)
{
	int status;
	unsigned int flags;
	int detect_status;
	COMMAND_LINE_ARGUMENT_A* arg;

	flags = COMMAND_LINE_SEPARATOR_COLON;
	flags |= COMMAND_LINE_SIGIL_SLASH | COMMAND_LINE_SIGIL_PLUS_MINUS;

	if (ignoreUnknown)
	{
		flags |= COMMAND_LINE_IGN_UNKNOWN_KEYWORD;
	}

	*count = 0;
	detect_status = 0;
	CommandLineClearArgumentsA(args);

	status = CommandLineParseArgumentsA(argc, (const ::string &*) argv, args, flags,
			nullptr, freerdp_detect_command_line_pre_filter, nullptr);

	if (status < 0)
		return status;

	arg = args;

	do
	{
		if (!(arg->Flags & COMMAND_LINE_ARGUMENT_PRESENT))
			continue;

		(*count)++;
	}
	while ((arg = CommandLineFindNextArgumentA(arg)) != nullptr);

	if ((status <= COMMAND_LINE_ERROR) && (status >= COMMAND_LINE_ERROR_LAST))
		detect_status = -1;

	return detect_status;
}

int freerdp_detect_posix_style_command_line_syntax(int argc, char** argv,
	int* count, BOOL ignoreUnknown)
{
	int status;
	unsigned int flags;
	int detect_status;
	COMMAND_LINE_ARGUMENT_A* arg;

	flags = COMMAND_LINE_SEPARATOR_SPACE;
	flags |= COMMAND_LINE_SIGIL_DASH | COMMAND_LINE_SIGIL_DOUBLE_DASH;
	flags |= COMMAND_LINE_SIGIL_ENABLE_DISABLE;

	if (ignoreUnknown)
	{
		flags |= COMMAND_LINE_IGN_UNKNOWN_KEYWORD;
	}

	*count = 0;
	detect_status = 0;
	CommandLineClearArgumentsA(args);

	status = CommandLineParseArgumentsA(argc, (const ::string &*) argv, args, flags,
			nullptr, freerdp_detect_command_line_pre_filter, nullptr);

	if (status < 0)
		return status;

	arg = args;

	do
	{
		if (!(arg->Flags & COMMAND_LINE_ARGUMENT_PRESENT))
			continue;

		(*count)++;
	}
	while ((arg = CommandLineFindNextArgumentA(arg)) != nullptr);

	if ((status <= COMMAND_LINE_ERROR) && (status >= COMMAND_LINE_ERROR_LAST))
		detect_status = -1;

	return detect_status;
}

static BOOL freerdp_client_detect_command_line(int argc, char** argv,
	unsigned int* flags, BOOL ignoreUnknown)
{
	int old_cli_status;
	int old_cli_count;
	int posix_cli_status;
	int posix_cli_count;
	int windows_cli_status;
	int windows_cli_count;
	BOOL compatibility = false;

	windows_cli_status = freerdp_detect_windows_style_command_line_syntax(argc, argv, &windows_cli_count, ignoreUnknown);
	posix_cli_status = freerdp_detect_posix_style_command_line_syntax(argc, argv, &posix_cli_count, ignoreUnknown);
	old_cli_status = freerdp_detect_old_command_line_syntax(argc, argv, &old_cli_count);

	/* Default is POSIX syntax */
	*flags = COMMAND_LINE_SEPARATOR_SPACE;
	*flags |= COMMAND_LINE_SIGIL_DASH | COMMAND_LINE_SIGIL_DOUBLE_DASH;
	*flags |= COMMAND_LINE_SIGIL_ENABLE_DISABLE;

	if (posix_cli_status <= COMMAND_LINE_STATUS_PRINT)
		return compatibility;

	/* Check, if this may be windows style syntax... */
	if ((windows_cli_count && (windows_cli_count >= posix_cli_count)) || (windows_cli_status <= COMMAND_LINE_STATUS_PRINT))
	{
		windows_cli_count = 1;
		*flags = COMMAND_LINE_SEPARATOR_COLON;
		*flags |= COMMAND_LINE_SIGIL_SLASH | COMMAND_LINE_SIGIL_PLUS_MINUS;
	}
	else if (old_cli_status >= 0)
	{
		/* Ignore legacy parsing in case there is an error in the command line. */

		if ((old_cli_status == 1) || ((old_cli_count > posix_cli_count) && (old_cli_status != -1)))
		{
			*flags = COMMAND_LINE_SEPARATOR_SPACE;
			*flags |= COMMAND_LINE_SIGIL_DASH | COMMAND_LINE_SIGIL_DOUBLE_DASH;

			compatibility = true;
		}
	}

	WLog_DBG(TAG, "windows: %d/%d posix: %d/%d compat: %d/%d", windows_cli_status, windows_cli_count,
		posix_cli_status, posix_cli_count, old_cli_status, old_cli_count);

	return compatibility;
}

int freerdp_client_settings_command_line_status_print(rdpSettings* settings, int status, int argc, char** argv)
{
	COMMAND_LINE_ARGUMENT_A* arg;

	if (status == COMMAND_LINE_STATUS_PRINT_VERSION)
	{
		freerdp_client_print_version();
		return COMMAND_LINE_STATUS_PRINT_VERSION;
	}
	else if (status == COMMAND_LINE_STATUS_PRINT)
	{
		arg = CommandLineFindArgumentA(args, "kbd-list");

		if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
		{
			int i;
			RDP_KEYBOARD_LAYOUT* layouts;

			layouts = freerdp_keyboard_get_layouts(RDP_KEYBOARD_LAYOUT_TYPE_STANDARD);
			//if (!layouts) /* FIXME*/
			printf("\nKeyboard Layouts\n");
			for (i = 0; layouts[i].code; i++)
				printf("0x%08X\t%s\n", (int) layouts[i].code, layouts[i].name);
			free(layouts);

			layouts = freerdp_keyboard_get_layouts(RDP_KEYBOARD_LAYOUT_TYPE_VARIANT);
			//if (!layouts) /* FIXME*/
			printf("\nKeyboard Layout Variants\n");
			for (i = 0; layouts[i].code; i++)
				printf("0x%08X\t%s\n", (int) layouts[i].code, layouts[i].name);
			free(layouts);

			layouts = freerdp_keyboard_get_layouts(RDP_KEYBOARD_LAYOUT_TYPE_IME);
			//if (!layouts) /* FIXME*/
			printf("\nKeyboard Input Method Editors (IMEs)\n");
			for (i = 0; layouts[i].code; i++)
				printf("0x%08X\t%s\n", (int) layouts[i].code, layouts[i].name);
			free(layouts);

			printf("\n");
		}

		arg = CommandLineFindArgumentA(args, "monitor-list");

		if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
		{
			settings->ListMonitors = true;
		}

		return COMMAND_LINE_STATUS_PRINT;
	}
	else if (status < 0)
	{
		freerdp_client_print_command_line_help(argc, argv);
		return COMMAND_LINE_STATUS_PRINT_HELP;
	}

	return 0;
}

int freerdp_client_settings_parse_command_line_arguments(rdpSettings* settings,
	int argc, char** argv, BOOL allowUnknown)
{
	char* p;
	char* user = nullptr;
	char* gwUser = nullptr;
	char* str;
	int length;
	int status;
	unsigned int flags;
	BOOL compatibility;
	COMMAND_LINE_ARGUMENT_A* arg;

	compatibility = freerdp_client_detect_command_line(argc, argv, &flags, allowUnknown);

	if (compatibility)
	{
		WLog_WARN(TAG, "Using deprecated command-line interface!");
		return freerdp_client_parse_old_command_line_arguments(argc, argv, settings);
	}
	else
	{
		CommandLineClearArgumentsA(args);

		if (allowUnknown)
		{
			flags |= COMMAND_LINE_IGN_UNKNOWN_KEYWORD;
		}
		status = CommandLineParseArgumentsA(argc, (const ::string &*) argv, args, flags, settings,
				freerdp_client_command_line_pre_filter, freerdp_client_command_line_post_filter);

		if (status < 0)
			return status;
	}

	CommandLineFindArgumentA(args, "v");

	arg = args;

	do
	{
		if (!(arg->Flags & COMMAND_LINE_ARGUMENT_PRESENT))
			continue;

		CommandLineSwitchStart(arg)

		CommandLineSwitchCase(arg, "v")
		{
			p = strchr(arg->Value, '[');
			/* ipv4 */
			if (!p)
			{
				p = strchr(arg->Value, ':');
				if (p)
				{
					length = (int) (p - arg->Value);
					settings->ServerPort = atoi(&p[1]);
					if (!(settings->ServerHostname = (char*) calloc(length + 1UL, sizeof(char))))
						return COMMAND_LINE_ERROR_MEMORY;

					strncpy(settings->ServerHostname, arg->Value, length);
					settings->ServerHostname[length] = '\0';
				}
				else
				{
					if (!(settings->ServerHostname = _strdup(arg->Value)))
						return COMMAND_LINE_ERROR_MEMORY;
				}
			}
			else /* ipv6 */
			{
				char *p2 = strchr(arg->Value, ']');
				/* not a valid [] ipv6 addr found */
				if (!p2)
					continue;

				length = p2 - p;
				if (!(settings->ServerHostname = (char*) calloc(length, sizeof(char))))
					return COMMAND_LINE_ERROR;
				strncpy(settings->ServerHostname, p+1, length-1);
				if (*(p2 + 1) == ':')
				{
					settings->ServerPort = atoi(&p2[2]);
				}
				printf("hostname %s port %d\n", settings->ServerHostname, settings->ServerPort);
			}
		}
		CommandLineSwitchCase(arg, "spn-class")
		{
			if (!(settings->AuthenticationServiceClass = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;

		}
		CommandLineSwitchCase(arg, "credentials-delegation")
		{
			settings->DisableCredentialsDelegation = arg->Value ? false : true;
		}
		CommandLineSwitchCase(arg, "vmconnect")
		{
			settings->ServerPort = 2179;
			settings->NegotiateSecurityLayer = false;

			if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
			{
				settings->SendPreconnectionPdu = true;
				if (!(settings->PreconnectionBlob = _strdup(arg->Value)))
					return COMMAND_LINE_ERROR_MEMORY;
			}
		}
		CommandLineSwitchCase(arg, "w")
		{
			settings->DesktopWidth = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "h")
		{
			settings->DesktopHeight = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "int_size")
		{
			if (!(str = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;

			p = strchr(str, 'x');

			if (p)
			{
				*p = '\0';
				settings->DesktopWidth = atoi(str);
				settings->DesktopHeight = atoi(&p[1]);
			}
			else
			{
				p = strchr(str, '%');
				if(p)
				{
					settings->PercentScreen = atoi(str);
				}
			}

			free(str);
		}
		CommandLineSwitchCase(arg, "f")
		{
			settings->Fullscreen = true;
		}
		CommandLineSwitchCase(arg, "multimon")
		{
			settings->UseMultimon = true;

			if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
			{
				if (_stricmp(arg->Value, "force") == 0)
				{
					settings->ForceMultimon = true;
				}
			}
		}
		CommandLineSwitchCase(arg, "span")
		{
			settings->SpanMonitors = true;
		}
		CommandLineSwitchCase(arg, "workarea")
		{
			settings->Workarea = true;
		}
		CommandLineSwitchCase(arg, "monitors")
		{
			if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
			{
				unsigned int i;
				char** p;
				int count = 0;

				p = freerdp_command_line_parse_comma_separated_values(arg->Value, &count);
				if (!p)
					return COMMAND_LINE_ERROR_MEMORY;

				if (count > 16)
					count = 16;

				settings->NumMonitorIds = (unsigned int) count;

				for (i = 0; i < settings->NumMonitorIds; i++)
				{
					settings->MonitorIds[i] = atoi(p[i]);
				}

				free(p);
			}
		}
		CommandLineSwitchCase(arg, "monitor-list")
		{
			settings->ListMonitors = true;
		}
		CommandLineSwitchCase(arg, "t")
		{
			if (!(settings->WindowTitle = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "decorations")
		{
			settings->Decorations = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "smart-sizing")
		{
			settings->SmartSizing = true;

			if (arg->Value)
			{
				if (!(str = _strdup(arg->Value)))
					return COMMAND_LINE_ERROR_MEMORY;
				if ((p = strchr(str, 'x')))
				{
					*p = '\0';
					settings->SmartSizingWidth = atoi(str);
					settings->SmartSizingHeight = atoi(&p[1]);
				}
				free(str);
			}
		}
		CommandLineSwitchCase(arg, "bpp")
		{
			settings->ColorDepth = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "admin")
		{
			settings->ConsoleSession = true;
		}
		CommandLineSwitchCase(arg, "restricted-admin")
		{
			settings->ConsoleSession = true;
			settings->RestrictedAdminModeRequired = true;
		}
		CommandLineSwitchCase(arg, "pth")
		{
			settings->ConsoleSession = true;
			settings->RestrictedAdminModeRequired = true;
			if (!(settings->PasswordHash = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "client-hostname")
		{
			if (!(settings->ClientHostname = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "kbd")
		{
			unsigned long int atom;
			char* pEnd;

			atom = strtoul(arg->Value, &pEnd, 16);

			if (pEnd != (arg->Value + strlen(arg->Value)))
				atom = 0;

			if (atom == 0)
			{
				atom = (unsigned long int) freerdp_map_keyboard_layout_name_to_id(arg->Value);
				if (atom == -1)
					WLog_ERR(TAG, "A problem occured while mapping the on_layout name to atom");
				else if (atom == 0)
				{
					WLog_ERR(TAG, "Could not identify keyboard on_layout: %s", arg->Value);
					WLog_ERR(TAG, "Use /kbd-list to list available layouts");
				}
				if (atom <= 0)
					return COMMAND_LINE_STATUS_PRINT;
			}

			settings->KeyboardLayout = (unsigned int) atom;
		}
		CommandLineSwitchCase(arg, "kbd-type")
		{
			settings->KeyboardType = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "kbd-subtype")
		{
			settings->KeyboardSubType = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "kbd-fn-key")
		{
			settings->KeyboardFunctionKey = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "u")
		{
			user = _strdup(arg->Value);
		}
		CommandLineSwitchCase(arg, "d")
		{
			if (!(settings->Domain = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "p")
		{
			if (!(settings->Password = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "g")
		{
			if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
			{
				p = strchr(arg->Value, ':');

				if (p)
				{
					length = (int) (p - arg->Value);
					settings->GatewayPort = atoi(&p[1]);
					if (!(settings->GatewayHostname = (char*) calloc(length + 1UL, sizeof(char))))
						return COMMAND_LINE_ERROR_MEMORY;
					strncpy(settings->GatewayHostname, arg->Value, length);
					settings->GatewayHostname[length] = '\0';
				}
				else
				{
					if (!(settings->GatewayHostname = _strdup(arg->Value)))
						return COMMAND_LINE_ERROR_MEMORY;
				}
			}
			else
			{
				if (!(settings->GatewayHostname = _strdup(settings->ServerHostname)))
					return COMMAND_LINE_ERROR_MEMORY;
			}

			settings->GatewayEnabled = true;
			settings->GatewayUseSameCredentials = true;

			freerdp_set_gateway_usage_method(settings, TSC_PROXY_MODE_DIRECT);
		}
		CommandLineSwitchCase(arg, "gu")
		{
			if (!(gwUser = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;

			settings->GatewayUseSameCredentials = false;
		}
		CommandLineSwitchCase(arg, "gd")
		{
			if (!(settings->GatewayDomain = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			settings->GatewayUseSameCredentials = false;
		}
		CommandLineSwitchCase(arg, "gp")
		{
			if (!(settings->GatewayPassword = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			settings->GatewayUseSameCredentials = false;
		}
		CommandLineSwitchCase(arg, "gt")
		{
			if (_stricmp(arg->Value, "rpc") == 0)
			{
				settings->GatewayRpcTransport = true;
				settings->GatewayHttpTransport = false;
			}
			else if (_stricmp(arg->Value, "http") == 0)
			{
				settings->GatewayRpcTransport = false;
				settings->GatewayHttpTransport = true;
			}
			else if (_stricmp(arg->Value, "auto") == 0)
			{
				settings->GatewayRpcTransport = true;
				settings->GatewayHttpTransport = true;
			}
		}
		CommandLineSwitchCase(arg, "gateway-usage-method")
		{
			int type;
			char* pEnd;

			type = strtol(arg->Value, &pEnd, 10);

			if (type == 0)
			{
				if (_stricmp(arg->Value, "none") == 0)
					type = TSC_PROXY_MODE_NONE_DIRECT;
				else if (_stricmp(arg->Value, "direct") == 0)
					type = TSC_PROXY_MODE_DIRECT;
				else if (_stricmp(arg->Value, "detect") == 0)
					type = TSC_PROXY_MODE_DETECT;
				else if (_stricmp(arg->Value, "default") == 0)
					type = TSC_PROXY_MODE_DEFAULT;
			}

			freerdp_set_gateway_usage_method(settings, (unsigned int) type);
		}
		CommandLineSwitchCase(arg, "app")
		{
			if (!(settings->RemoteApplicationProgram = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;

			settings->RemoteApplicationMode = true;
			settings->RemoteAppLanguageBarSupported = true;
			settings->Workarea = true;
			settings->DisableWallpaper = true;
			settings->DisableFullWindowDrag = true;
		}
		CommandLineSwitchCase(arg, "load-balance-info")
		{
			if (!(settings->LoadBalanceInfo = (unsigned char*) _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			settings->LoadBalanceInfoLength = (unsigned int) strlen((char*) settings->LoadBalanceInfo);
		}
		CommandLineSwitchCase(arg, "app-name")
		{
			if (!(settings->RemoteApplicationName = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;

		}
		CommandLineSwitchCase(arg, "app-icon")
		{
			if (!(settings->RemoteApplicationIcon = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "app-cmd")
		{
			if (!(settings->RemoteApplicationCmdLine = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "app-file")
		{
			if (!(settings->RemoteApplicationFile = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "app-guid")
		{
			if (!(settings->RemoteApplicationGuid = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "compression")
		{
			settings->CompressionEnabled = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "compression-level")
		{
			settings->CompressionLevel = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "drives")
		{
			settings->RedirectDrives = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "home-drive")
		{
			settings->RedirectHomeDrive = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "clipboard")
		{
			settings->RedirectClipboard = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "shell")
		{
			if (!(settings->AlternateShell = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "shell-dir")
		{
			if (!(settings->ShellWorkingDirectory = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "audio-mode")
		{
			int mode;

			mode = atoi(arg->Value);

			if (mode == AUDIO_MODE_REDIRECT)
			{
				settings->AudioPlayback = true;
			}
			else if (mode == AUDIO_MODE_PLAY_ON_SERVER)
			{
				settings->RemoteConsoleAudio = true;
			}
			else if (mode == AUDIO_MODE_NONE)
			{
				settings->AudioPlayback = false;
				settings->RemoteConsoleAudio = false;
			}
		}
		CommandLineSwitchCase(arg, "network")
		{
			int type;
			char* pEnd;

			type = strtol(arg->Value, &pEnd, 10);

			if (type == 0)
			{
				if (_stricmp(arg->Value, "modem") == 0)
					type = CONNECTION_TYPE_MODEM;
				else if (_stricmp(arg->Value, "broadband") == 0)
					type = CONNECTION_TYPE_BROADBAND_HIGH;
				else if (_stricmp(arg->Value, "broadband-low") == 0)
					type = CONNECTION_TYPE_BROADBAND_LOW;
				else if (_stricmp(arg->Value, "broadband-high") == 0)
					type = CONNECTION_TYPE_BROADBAND_HIGH;
				else if (_stricmp(arg->Value, "wan") == 0)
					type = CONNECTION_TYPE_WAN;
				else if (_stricmp(arg->Value, "lan") == 0)
					type = CONNECTION_TYPE_LAN;
				else if ((_stricmp(arg->Value, "autodetect") == 0) ||
						(_stricmp(arg->Value, "auto") == 0) ||
						(_stricmp(arg->Value, "detect") == 0))
				{
					type = CONNECTION_TYPE_AUTODETECT;
				}
			}

			freerdp_set_connection_type(settings, type);
		}
		CommandLineSwitchCase(arg, "fonts")
		{
			settings->AllowFontSmoothing = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "wallpaper")
		{
			settings->DisableWallpaper = arg->Value ? false : true;
		}
		CommandLineSwitchCase(arg, "window-drag")
		{
			settings->DisableFullWindowDrag = arg->Value ? false : true;
		}
		CommandLineSwitchCase(arg, "menu-anims")
		{
			settings->DisableMenuAnims = arg->Value ? false : true;
		}
		CommandLineSwitchCase(arg, "themes")
		{
			settings->DisableThemes = arg->Value ? false : true;
		}
		CommandLineSwitchCase(arg, "aero")
		{
			settings->AllowDesktopComposition = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "gdi")
		{
			if (_stricmp(arg->Value, "sw") == 0)
				settings->SoftwareGdi = true;
			else if (_stricmp(arg->Value, "hw") == 0)
				settings->SoftwareGdi = false;
		}
		CommandLineSwitchCase(arg, "gfx")
		{
			settings->SupportGraphicsPipeline = true;
		}
		CommandLineSwitchCase(arg, "gfx-thin-client")
		{
			settings->GfxThinClient = arg->Value ? true : false;
			settings->SupportGraphicsPipeline = true;
		}
		CommandLineSwitchCase(arg, "gfx-small-cache")
		{
			settings->GfxSmallCache = arg->Value ? true : false;
			settings->SupportGraphicsPipeline = true;
		}
		CommandLineSwitchCase(arg, "gfx-progressive")
		{
			settings->GfxProgressive = arg->Value ? true : false;
			settings->GfxThinClient = settings->GfxProgressive ? false : true;
			settings->SupportGraphicsPipeline = true;
		}
		CommandLineSwitchCase(arg, "gfx-h264")
		{
			settings->GfxH264 = arg->Value ? true : false;
			settings->SupportGraphicsPipeline = true;
		}
		CommandLineSwitchCase(arg, "rfx")
		{
			settings->RemoteFxCodec = true;
			settings->FastPathOutput = true;
			settings->ColorDepth = 32;
			settings->LargePointerFlag = true;
			settings->FrameMarkerCommandEnabled = true;
		}
		CommandLineSwitchCase(arg, "rfx-mode")
		{
			if (strcmp(arg->Value, "video") == 0)
				settings->RemoteFxCodecMode = 0x00;
			else if (strcmp(arg->Value, "image") == 0)
				settings->RemoteFxCodecMode = 0x02;
		}
		CommandLineSwitchCase(arg, "frame-ack")
		{
			settings->FrameAcknowledge = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "nsc")
		{
			settings->NSCodec = true;
			settings->FastPathOutput = true;
			settings->ColorDepth = 32;
			settings->LargePointerFlag = true;
			settings->FrameMarkerCommandEnabled = true;
		}
		CommandLineSwitchCase(arg, "jpeg")
		{
			settings->JpegCodec = true;
			settings->JpegQuality = 75;
		}
		CommandLineSwitchCase(arg, "jpeg-quality")
		{
			settings->JpegQuality = atoi(arg->Value) % 100;
		}
		CommandLineSwitchCase(arg, "nego")
		{
			settings->NegotiateSecurityLayer = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "pcb")
		{
			settings->SendPreconnectionPdu = true;
			if (!(settings->PreconnectionBlob = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "pcid")
		{
			settings->SendPreconnectionPdu = true;
			settings->PreconnectionId = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "sec")
		{
			if (strcmp("rdp", arg->Value) == 0) /* Standard RDP */
			{
				settings->RdpSecurity = true;
				settings->TlsSecurity = false;
				settings->NlaSecurity = false;
				settings->ExtSecurity = false;
				settings->UseRdpSecurityLayer = true;
			}
			else if (strcmp("tls", arg->Value) == 0) /* TLS */
			{
				settings->RdpSecurity = false;
				settings->TlsSecurity = true;
				settings->NlaSecurity = false;
				settings->ExtSecurity = false;
			}
			else if (strcmp("nla", arg->Value) == 0) /* NLA */
			{
				settings->RdpSecurity = false;
				settings->TlsSecurity = false;
				settings->NlaSecurity = true;
				settings->ExtSecurity = false;
			}
			else if (strcmp("ext", arg->Value) == 0) /* NLA Extended */
			{
				settings->RdpSecurity = false;
				settings->TlsSecurity = false;
				settings->NlaSecurity = false;
				settings->ExtSecurity = true;
			}
			else
			{
				WLog_ERR(TAG, "unknown protocol security: %s", arg->Value);
			}
		}
		CommandLineSwitchCase(arg, "encryption-methods")
		{
			if (arg->Flags & COMMAND_LINE_VALUE_PRESENT)
			{
				int i;
				char** p;
				int count = 0;

				p = freerdp_command_line_parse_comma_separated_values(arg->Value, &count);

				for (i = 0; i < count; i++)
				{
					if (!strcmp(p[i], "40"))
						settings->EncryptionMethods |= ENCRYPTION_METHOD_40BIT;
					else if (!strcmp(p[i], "56"))
						settings->EncryptionMethods |= ENCRYPTION_METHOD_56BIT;
					else if (!strcmp(p[i], "128"))
						settings->EncryptionMethods |= ENCRYPTION_METHOD_128BIT;
					else if (!strcmp(p[i], "FIPS"))
						settings->EncryptionMethods |= ENCRYPTION_METHOD_FIPS;
					else
						WLog_ERR(TAG, "unknown encryption method '%s'", p[i]);
				}

				free(p);
			}
		}
		CommandLineSwitchCase(arg, "from-stdin")
		{
			settings->CredentialsFromStdin = true;
		}
		CommandLineSwitchCase(arg, "sec-rdp")
		{
			settings->RdpSecurity = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "sec-tls")
		{
			settings->TlsSecurity = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "sec-nla")
		{
			settings->NlaSecurity = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "sec-ext")
		{
			settings->ExtSecurity = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "tls-ciphers")
		{
			if (strcmp(arg->Value, "netmon") == 0)
			{
				if (!(settings->AllowedTlsCiphers = _strdup("ALL:!ECDH")))
					return COMMAND_LINE_ERROR_MEMORY;
			}
			else if (strcmp(arg->Value, "ma") == 0)
			{
				if (!(settings->AllowedTlsCiphers = _strdup("AES128-SHA")))
					return COMMAND_LINE_ERROR_MEMORY;
			}
			else
			{
				if (!(settings->AllowedTlsCiphers = _strdup(arg->Value)))
					return COMMAND_LINE_ERROR_MEMORY;
			}
		}
		CommandLineSwitchCase(arg, "cert-name")
		{
			if (!(settings->CertificateName = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "cert-ignore")
		{
			settings->IgnoreCertificate = true;
		}
		CommandLineSwitchCase(arg, "authentication")
		{
			settings->Authentication = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "encryption")
		{
			settings->UseRdpSecurityLayer = arg->Value ? false : true;
		}
		CommandLineSwitchCase(arg, "grab-keyboard")
		{
			settings->GrabKeyboard = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "toggle-fullscreen")
		{
			settings->ToggleFullscreen = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "mouse-motion")
		{
			settings->MouseMotion = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "parent-window")
		{
			settings->ParentWindowId = strtol(arg->Value, nullptr, 0);
		}
		CommandLineSwitchCase(arg, "bitmap-cache")
		{
			settings->BitmapCacheEnabled = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "offscreen-cache")
		{
			settings->OffscreenSupportLevel = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "glyph-cache")
		{
			settings->GlyphSupportLevel = arg->Value ? GLYPH_SUPPORT_FULL : GLYPH_SUPPORT_NONE;
		}
		CommandLineSwitchCase(arg, "codec-cache")
		{
			settings->BitmapCacheV3Enabled = true;

			if (strcmp(arg->Value, "rfx") == 0)
			{
				settings->RemoteFxCodec = true;
			}
			else if (strcmp(arg->Value, "nsc") == 0)
			{
				settings->NSCodec = true;
			}
			else if (strcmp(arg->Value, "jpeg") == 0)
			{
				settings->JpegCodec = true;

				if (settings->JpegQuality == 0)
					settings->JpegQuality = 75;
			}
		}
		CommandLineSwitchCase(arg, "fast-path")
		{
			settings->FastPathInput = arg->Value ? true : false;
			settings->FastPathOutput = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "maximum-fast-path-int_size")
		{
			settings->MultifragMaxRequestSize = atoi(arg->Value);
		}
		CommandLineSwitchCase(arg, "async-input")
		{
			settings->AsyncInput = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "async-update")
		{
			settings->AsyncUpdate = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "async-channels")
		{
			settings->AsyncChannels = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "async-transport")
		{
			settings->AsyncTransport = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "wm-class")
		{
			if (!(settings->WmClass = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "play-rfx")
		{
			if (!(settings->PlayRemoteFxFile = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			settings->PlayRemoteFx = true;
		}
		CommandLineSwitchCase(arg, "auth-only")
		{
			settings->AuthenticationOnly = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "auto-reconnect")
		{
			settings->AutoReconnectionEnabled = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "reconnect-cookie")
		{
			unsigned char *base64;
			int length;
			crypto_base64_decode((const ::string &) (arg->Value), (int) strlen(arg->Value),
								&base64, &length);
			if ((base64 != nullptr) && (length == sizeof(ARC_SC_PRIVATE_PACKET)))
			{
				::memory_copy(settings->ServerAutoReconnectCookie, base64, length);
				free(base64);
			}
			else
			{
				WLog_ERR(TAG, "reconnect-cookie:  invalid base64 '%s'", arg->Value);
			}
		}
		CommandLineSwitchCase(arg, "print-reconnect-cookie")
		{
			settings->PrintReconnectCookie = arg->Value ? true : false;
		}
		CommandLineSwitchCase(arg, "assistance")
		{
			settings->RemoteAssistanceMode = true;
			if (!(settings->RemoteAssistancePassword = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchDefault(arg)
		{
		}

		CommandLineSwitchEnd(arg)
	}
	while ((arg = CommandLineFindNextArgumentA(arg)) != nullptr);

	if (!settings->Domain && user)
	{
		int ret;
		ret = freerdp_parse_username(user, &settings->Username, &settings->Domain);
		free(user);
		if (ret != 0 )
			return COMMAND_LINE_ERROR;
	}
	else
		settings->Username = user;

	if (!settings->GatewayDomain && gwUser)
	{
		int ret;
		ret = freerdp_parse_username(gwUser, &settings->GatewayUsername,
				       &settings->GatewayDomain);
		free(gwUser);
		if (ret != 0)
			return COMMAND_LINE_ERROR;
	}
	else
		settings->GatewayUsername = gwUser;

	freerdp_performance_flags_make(settings);

	if (settings->SupportGraphicsPipeline)
	{
		settings->FastPathOutput = true;
		settings->ColorDepth = 32;
		settings->LargePointerFlag = true;
		settings->FrameMarkerCommandEnabled = true;
	}

	arg = CommandLineFindArgumentA(args, "port");

	if (arg->Flags & COMMAND_LINE_ARGUMENT_PRESENT)
	{
		settings->ServerPort = atoi(arg->Value);
	}

	arg = CommandLineFindArgumentA(args, "p");

	if (arg->Flags & COMMAND_LINE_ARGUMENT_PRESENT)
	{
		FillMemory(arg->Value, strlen(arg->Value), '*');
	}

	arg = CommandLineFindArgumentA(args, "gp");

	if (arg->Flags & COMMAND_LINE_ARGUMENT_PRESENT)
	{
		FillMemory(arg->Value, strlen(arg->Value), '*');
	}

	return status;
}

int freerdp_client_load_static_channel_addin(rdpChannels* channels, rdpSettings* settings, char* name, void* data)
{
   PVIRTUALCHANNELENTRY entry;

	entry = (PVIRTUALCHANNELENTRY) freerdp_load_channel_addin_entry(name, nullptr, nullptr, FREERDP_ADDIN_CHANNEL_STATIC);

	if (entry)
	{
		if (freerdp_channels_client_load(channels, settings, entry, data) == 0)
		{
			WLog_INFO(TAG, "loading channel %s", name);
			return 0;
		}
	}

	return -1;
}

BOOL freerdp_client_load_addins(rdpChannels* channels, rdpSettings* settings)
{
	unsigned int index;
	ADDIN_ARGV* args;

	if ((freerdp_static_channel_collection_find(settings, "rdpsnd")) ||
			(freerdp_dynamic_channel_collection_find(settings, "tsmf")))
	{
		settings->DeviceRedirection = true; /* rdpsnd requires rdpdr to be registered */
		settings->AudioPlayback = true; /* Both rdpsnd and tsmf require this flag to be set */
	}

	if (freerdp_dynamic_channel_collection_find(settings, "audin"))
	{
		settings->AudioCapture = true;
	}

	if (settings->NetworkAutoDetect ||
		settings->SupportHeartbeatPdu ||
		settings->SupportMultitransport)
	{
		settings->DeviceRedirection = true; /* these RDP8 features require rdpdr to be registered */
	}

	if (settings->RedirectDrives || settings->RedirectHomeDrive || settings->RedirectSerialPorts
			|| settings->RedirectSmartCards || settings->RedirectPrinters)
	{
		settings->DeviceRedirection = true; /* All of these features require rdpdr */
	}

	if (settings->RedirectDrives)
	{
		if (!freerdp_device_collection_find(settings, "drive"))
		{
			char* params[3];

			params[0] = "drive";
			params[1] = "media";
			params[2] = "*";

			freerdp_client_add_device_channel(settings, 3, (char**) params);
		}
	}

	if (settings->RedirectHomeDrive)
	{
		if (!freerdp_device_collection_find(settings, "drive"))
		{
			char* params[3];

			params[0] = "drive";
			params[1] = "home";
			params[2] = "%";

			freerdp_client_add_device_channel(settings, 3, (char**) params);
		}
	}

	if (settings->DeviceRedirection)
	{
		freerdp_client_load_static_channel_addin(channels, settings, "rdpdr", settings);

		if (!freerdp_static_channel_collection_find(settings, "rdpsnd"))
		{
			char* params[2];

			params[0] = "rdpsnd";
			params[1] = "sys:fake";

			freerdp_client_add_static_channel(settings, 2, (char**) params);
		}
	}

	if (settings->RedirectSmartCards)
	{
		RDPDR_SMARTCARD* smartcard;

		smartcard = (RDPDR_SMARTCARD*) calloc(1, sizeof(RDPDR_SMARTCARD));

		if (!smartcard)
			return -1;

		smartcard->Type = RDPDR_DTYP_SMARTCARD;
		freerdp_device_collection_add(settings, (RDPDR_DEVICE*) smartcard);
	}

	if (settings->RedirectPrinters)
	{
		RDPDR_PRINTER* printer;

		printer = (RDPDR_PRINTER*) calloc(1, sizeof(RDPDR_PRINTER));

		if (!printer)
			return -1;

		printer->Type = RDPDR_DTYP_PRINT;
		freerdp_device_collection_add(settings, (RDPDR_DEVICE*) printer);
	}

	if (settings->RedirectClipboard)
	{
		if (!freerdp_static_channel_collection_find(settings, "cliprdr"))
		{
			char* params[1];

			params[0] = "cliprdr";

			freerdp_client_add_static_channel(settings, 1, (char**) params);
		}
	}

	if (settings->LyncRdpMode)
	{
		settings->EncomspVirtualChannel = true;
		settings->RemdeskVirtualChannel = true;
		settings->CompressionEnabled = false;
	}

	if (settings->RemoteAssistanceMode)
	{
		settings->EncomspVirtualChannel = true;
		settings->RemdeskVirtualChannel = true;
	}

	if (settings->EncomspVirtualChannel)
		freerdp_client_load_static_channel_addin(channels, settings, "encomsp", settings);

	if (settings->RemdeskVirtualChannel)
		freerdp_client_load_static_channel_addin(channels, settings, "remdesk", settings);

	for (index = 0; index < settings->StaticChannelCount; index++)
	{
		args = settings->StaticChannelArray[index];
		freerdp_client_load_static_channel_addin(channels, settings, args->argv[0], args);
	}

	if (settings->RemoteApplicationMode)
	{
		freerdp_client_load_static_channel_addin(channels, settings, "rail", settings);
	}

	if (settings->MultiTouchInput)
	{
		char* p[1];
		int count;

		count = 1;
		p[0] = "rdpei";

		freerdp_client_add_dynamic_channel(settings, count, p);
	}

	if (settings->SupportGraphicsPipeline)
	{
		char* p[1];
		int count;

		count = 1;
		p[0] = "rdpgfx";

		freerdp_client_add_dynamic_channel(settings, count, p);
	}

	if (settings->SupportEchoChannel)
	{
		char* p[1];
		int count;

		count = 1;
		p[0] = "echo";

		freerdp_client_add_dynamic_channel(settings, count, p);
	}

	if (settings->SupportDisplayControl)
	{
		char* p[1];
		int count;

		count = 1;
		p[0] = "disp";

		freerdp_client_add_dynamic_channel(settings, count, p);
	}

	if (settings->DynamicChannelCount)
		settings->SupportDynamicChannels = true;

	if (settings->SupportDynamicChannels)
	{
		freerdp_client_load_static_channel_addin(channels, settings, "drdynvc", settings);
	}

	return 1;
}
