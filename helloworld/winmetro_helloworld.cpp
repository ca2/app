//#include "aura/_.h"

#undef CoreApplication

[MTAThread]
::i32 main(Array<String^>^)
{

   return app_core_main("m_app.exe : app=app-core/helloworld experience=rootkiller client_only");

}


#include "include/applink.cpp"


/*[MTAThread]
::i32 main(Array<String^>^)
{
   
   // No Depends
   
   return 0;

}
*/
