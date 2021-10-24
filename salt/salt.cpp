#include "StdAfx.h"
#include "ca2/radix/cafxdllx.h"

#define sclip1(v, c) \
{ \
   int value = v + 1; \
   if(value < c) \
   { \
      value = c; \
   } \
   v = value; \
} 
   
#define sclip2(v, c) \
{ \
   int value = v * 2 + 1; \
   if(value < c) \
   { \
      value = c; \
   } \
   v = value; \
} 

#define M1(l, s1, s2, s5, s8) \
   { \
   int v1 = s1; \
   int v2 = s2; \
   int v5 = s5; \
   int v8 = s8; \
   sclip1(v1, 1); \
   sclip1(v2, 2); \
   sclip1(v5, 5); \
   sclip1(v8, 8); \
   strSalt += pszSourceSalt[(l + v1 + v2 + v5 + v8) % strlen(pszSourceSalt)]; \
   }



#define BOOLM1(b, s1, s2, s5, s8) M1((((b) != 0) ? s1 - 1 : 0), s1, s2, s5, s8)
#define INTM1(i, s1, s2, s5, s8) M1(i, s1, s2, s5, s8)

#define INTM2(s1, s2, s5, s8) \
   {\
      string strHash = straHash.implode(";"); \
      int iMod = stunCalculateFingerprint(strHash, strHash.get_length()); \
      int v1 = s1 * 2 + 1; \
      int v2 = s2 * 2 + 1; \
      int v5 = s5 * 2 + 1; \
      int v8 = s8 * 2 + 1; \
      sclip2(v1, 1); \
      sclip2(v2, 2); \
      sclip2(v5, 5); \
      sclip2(v8, 8); \
      strSalt += pszSourceSalt[(iMod + v1 + v2 + v5 + v8) % strlen(pszSourceSalt)]; \
   }

#define M00(s1, s2, s5, s8) BOOLM1(::IsDebuggerPresent(), s1, s2, s5, s8)
#define M01(s1, s2, s5, s8) INTM2(s1, s2, s5, s8)


string salt(::ca::application * papp, const ::string & pszSourceSalt, string_array & straSourceSalt)
{
   string_array straSourceHash; 
   straSourceHash.explode(";", pszSourceSalt); 
   string_array straHash; 
   if(straSourceHash.get_count() == 1)
   {
      straHash.add(pszSourceSalt);
   }
   else if(straSourceHash.get_count() > 1)
   {
      for(int i = 0; i < straSourceSalt.get_size(); i++) 
      { 
         ::LoadLibrary(straSourceSalt[i]); 
      } 
      ::u32 dwNeeded = 0;
      if(!EnumProcessModules(::GetCurrentProcess(),  nullptr,  0,  &dwNeeded)) 
      { 
         return ""; 
      } 
      ::u32 dwAlloc = (dwNeeded + sizeof(HMODULE)) * 2;
      HMODULE * pmodulea = new HMODULE[dwAlloc / sizeof(HMODULE)]; 
      if(pmodulea == nullptr) 
         return ""; 
      if(!EnumProcessModules(::GetCurrentProcess(),  pmodulea,  dwAlloc,  &dwNeeded)) 
      { 
         delete pmodulea; 
         return ""; 
      } 
      string strModule; 
      ex1::file_system_pointer fs(pobject);
      string strModuleFolder(papp->m_psystem->get_ca2_module_folder());
      fs->FullPath(strModuleFolder, strModuleFolder);
      for(::u32 dw = 0; dw < (dwNeeded / sizeof(HMODULE)); dw++)
      { 
         strModule.Empty();
         GetModuleFileName(pmodulea[dw], strModule.get_string_buffer(4096), 4096); 
         strModule.ReleaseBuffer(); 
         fs->FullPath(strModule, strModule);
         if(gen::str::begins_ci(strModule, strModuleFolder)) 
         { 
            if(!straSourceSalt.contains_ci(strModule)) 
            {
                return ""; 
            }
            string strHash = papp->m_psystem->file36().md5(strModule); 
            if(!straSourceHash.contains(strHash)) 
            {
                return "";
            }
            straHash.add(strHash);
         }
      }
      straHash.QuickSort();
      delete pmodulea;
   }
   string strSalt;
   #include "../../../time/salt.inl"
   return papp->m_psystem->crypt().md5(strSalt);
}





static AFX_EXTENSION_MODULE VmscdadecDLL = { nullptr, nullptr };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID lpReserved)
{
   // Remove this if you use lpReserved
   __UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::output_debug_string("salt.DLL Initializing!\n");
      
      // Extension DLL one-time initialization
      if (!AfxInitExtensionModule(VmscdadecDLL, hInstance))
         return 0;

      // Insert this DLL into the resource chain
      // NOTE: If this Extension DLL is being implicitly linked to by
      //  an ca2 API Regular DLL (such as an ActiveX control)
      //  instead of an ca2 API application, then you will want to
      //  erase this line from DllMain and put it in a separate
      //  function exported from this Extension DLL.  The Regular DLL
      //  that uses this Extension DLL should then explicitly call that
      //  function to initialize this Extension DLL.  Otherwise,
      //  the CDynLinkLibrary object will not be attached to the
      //  Regular DLL's resource chain, and serious problems will
      //  result.

      new CDynLinkLibrary(VmscdadecDLL);
   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      ::output_debug_string("salt.DLL Terminating!\n");
      // Terminate the library before destructors are called
      AfxTermExtensionModule(VmscdadecDLL);
   }
   return 1;   // ok
}

