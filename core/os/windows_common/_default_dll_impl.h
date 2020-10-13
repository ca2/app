
#ifndef CUBE

#ifdef _UWP
[MTAThread]
#endif
int_bool WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID pReserved)

{

   //UNREFERENCED_PARAMETER(hModule);
   //UNREFERENCED_PARAMETER(pReserved);


   //switch (ul_reason_for_call)
   //{
   //case DLL_PROCESS_ATTACH:
   //{
   //   ::output_debug_string("hash_sha1.dll DLL_PROCESS_ATTACH");
   //}
   //break;
   //case DLL_THREAD_ATTACH:
   //{
   //   ::output_debug_string("hash_sha1.dll DLL_THREAD_ATTACH");
   //}
   //break;
   //case DLL_THREAD_DETACH:
   //{
   //   ::output_debug_string("hash_sha1.dll DLL_THREAD_DETACH");
   //}
   //break;
   //case DLL_PROCESS_DETACH:
   //{
   //   ::output_debug_string("hash_sha1.dll DLL_PROCESS_DETACH");
   //}
   //break;
   //}

   return _001DefaultDllMain(hInstance, dwReason, pReserved);


}



#endif