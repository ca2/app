#pragma once


namespace windows
{

	class CLASS_DECL_AQUA media_foundation :
		virtual public ::matter
	{
	public:

		// CoInitialize(NULL);

		media_foundation();
		virtual ~media_foundation();

		//if (FAILED(hr))
		//{

		//	debug_print_out * pdebugprintout = &debug_print_out::get_instance();

		//	pdebugprintout->print_out(L"MEDIA FOUNDATION: It cannot be created!!!\n");

		//}

	};


} // namespace windows



