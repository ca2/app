#include "framework.h"
#include "media_foundation.h"
#undef Context
#include "apex/operating_system.h"
#include <mfapi.h>


namespace windows
{


	media_foundation::media_foundation()
	{

		HRESULT hr = MFStartup(MF_VERSION);

		if (FAILED(hr))
		{

			infomration("MEDIA FOUNDATION: Resources couldn't be started\n");

		}

	}


	media_foundation::~media_foundation()
	{

		HRESULT hr = MFShutdown();

		if (FAILED(hr))
		{

			infomration("MEDIA FOUNDATION: Resources couldn't be released\n");

		}

	}


} // namespace windows



