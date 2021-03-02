#include "framework.h"
#include "acme/operating_system.h"

/*
 * Copyright (c) 2014 Craig Lilley <cralilley@gmail.com>
 * This software is made available under the terms of the MIT licence.
 * A copy of the licence can be obtained from:
 * http://opensource.org/licenses/MIT
 */

#include <tchar.h>
#include <setupapi.h>
#include <initguid.h>
#include <devguid.h>
#include <cstring>

//using serial::port_info;

static const DWORD port_name_max_length = 256;
static const DWORD friendly_name_max_length = 256;
static const DWORD hardware_id_max_length = 256;

// Convert a wide Unicode string to an UTF8 string
string utf8_encode(const wstring &wstr)
{
	return wstr;
}


namespace serial
{

	array <port_info> list_ports()
	{
		array<port_info> devices_found;

		HDEVINFO device_info_set = SetupDiGetClassDevs(
			(const GUID*)&GUID_DEVCLASS_PORTS,
			nullptr,
			nullptr,
			DIGCF_PRESENT);

		unsigned int device_info_set_index = 0;
		SP_DEVINFO_DATA device_info_data = {};

		device_info_data.cbSize = sizeof(SP_DEVINFO_DATA);

		while (SetupDiEnumDeviceInfo(device_info_set, device_info_set_index, &device_info_data))
		{
			device_info_set_index++;

			// Get port name

			HKEY hkey = SetupDiOpenDevRegKey(
				device_info_set,
				&device_info_data,
				DICS_FLAG_GLOBAL,
				0,
				DIREG_DEV,
				KEY_READ);

			TCHAR port_name[port_name_max_length];
			DWORD port_name_length = port_name_max_length;

			::i32 return_code = RegQueryValueEx(
				hkey,
				_T("PortName"),
				nullptr,
				nullptr,
				(byte*)port_name,
				&port_name_length);

			RegCloseKey(hkey);

			if (return_code != EXIT_SUCCESS)
				continue;

			if (port_name_length > 0 && port_name_length <= port_name_max_length)
				port_name[port_name_length - 1] = '\0';
			else
				port_name[0] = '\0';

			// Ignore parallel ports

			if (_tcsstr(port_name, _T("LPT")) != nullptr)
				continue;

			// Get port friendly name

			TCHAR friendly_name[friendly_name_max_length];
			DWORD friendly_name_actual_length = 0;

			BOOL got_friendly_name = SetupDiGetDeviceRegistryProperty(
				device_info_set,
				&device_info_data,
				SPDRP_FRIENDLYNAME,
				nullptr,
				(PBYTE)friendly_name,
				friendly_name_max_length,
				&friendly_name_actual_length);

			if (got_friendly_name && friendly_name_actual_length > 0)
				friendly_name[friendly_name_actual_length - 1] = '\0';
			else
				friendly_name[0] = '\0';

			// Get hardware ID

			TCHAR hardware_id[hardware_id_max_length];
			DWORD hardware_id_actual_length = 0;

			BOOL got_hardware_id = SetupDiGetDeviceRegistryProperty(
				device_info_set,
				&device_info_data,
				SPDRP_HARDWAREID,
				nullptr,
				(PBYTE)hardware_id,
				hardware_id_max_length,
				&hardware_id_actual_length);

			if (got_hardware_id && hardware_id_actual_length > 0)
				hardware_id[hardware_id_actual_length - 1] = '\0';
			else
				hardware_id[0] = '\0';

#ifdef UNICODE
			string portName = utf8_encode(port_name);
			string friendlyName = utf8_encode(friendly_name);
			string hardwareId = utf8_encode(hardware_id);
#else
			string portName = port_name;
			string friendlyName = friendly_name;
			string hardwareId = hardware_id;
#endif

			port_info port_entry;
			port_entry.port = portName;
			port_entry.description = friendlyName;
			port_entry.hardware_id = hardwareId;

			devices_found.push_back(port_entry);
		}

		SetupDiDestroyDeviceInfoList(device_info_set);

		return devices_found;
	}



} // namespace serial



