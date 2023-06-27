
#ifndef CUBE

#ifdef UNIVERSAL_WINDOWS
[MTAThread]
#endif
int_bool WINAPI DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID pReserved)

{

   //UNREFERENCED_PARAMETER(hModule);
   //UNREFERENCED_PARAMETER(pReserved);


   //switch (ul_reason_for_call)
   //{
   //case DLL_PROCESS_ATTACH:
   //{
   //   ::information("hash_sha1.dll DLL_PROCESS_ATTACH");
   //}
   //break;
   //case DLL_THREAD_ATTACH:
   //{
   //   ::information("hash_sha1.dll DLL_THREAD_ATTACH");
   //}
   //break;
   //case DLL_THREAD_DETACH:
   //{
   //   ::information("hash_sha1.dll DLL_THREAD_DETACH");
   //}
   //break;
   //case DLL_PROCESS_DETACH:
   //{
   //   ::information("hash_sha1.dll DLL_PROCESS_DETACH");
   //}
   //break;
   //}

   return _001DefaultDllMain(hInstance, dwReason, pReserved);


}



#endif
