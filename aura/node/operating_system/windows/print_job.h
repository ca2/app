#pragma once


namespace windows
{


	class CLASS_DECL_AURA print_task :
	   virtual public ::user::print_task
	{
	public:


	   print_task(__pointer(base_application) papp);
	   virtual ~print_task();


	   virtual i32 run();

	};


} // namespace windows




