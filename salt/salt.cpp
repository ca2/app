#include "framework.h"
#include "ca2/radix/c::windows_definition::dllx.h"

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
   strSalt += pszSourceSalt[(l + v1 + v2 + v5 + v8) % strlen(scopedstrSourceSalt)]; \
   }



#define BOOLM1(b, s1, s2, s5, s8) M1((((b) != 0) ? s1 - 1 : 0), s1, s2, s5, s8)
#define INTM1(i, s1, s2, s5, s8) M1(i, s1, s2, s5, s8)

#define INTM2(s1, s2, s5, s8) \
   {\
      string strHash = straHash.implode(";"); \
      int iMod = stunCalculateFingerprint(strHash, strHash.length()); \
      int v1 = s1 * 2 + 1; \
      int v2 = s2 * 2 + 1; \
      int v5 = s5 * 2 + 1; \
      int v8 = s8 * 2 + 1; \
      sclip2(v1, 1); \
      sclip2(v2, 2); \
      sclip2(v5, 5); \
      sclip2(v8, 8); \
      strSalt += pszSourceSalt[(iMod + v1 + v2 + v5 + v8) % strlen(scopedstrSourceSalt)]; \
   }

#define M00(s1, s2, s5, s8) BOOLM1(::IsDebuggerPresent(), s1, s2, s5, s8)
#define M01(s1, s2, s5, s8) INTM2(s1, s2, s5, s8)


string salt(::ca::application * papp, const ::scoped_string & scopedstrSourceSalt, string_array & straSourceSalt)
{
   string_array straSourceHash; 
   straSourceHash.explode(";", pszSourceSalt); 
   string_array straHash; 
   if(straSourceHash.get_count() == 1)
   {
      straHash.add(scopedstrSourceSalt);
   }
   else if(straSourceHash.get_count() > 1)
   {
      for(int i = 0; i < straSourceSalt.get_size(); i++) 
      { 
         ::LoadLibrary(straSourceSalt[i]); 
      } 
      unsigned int dwNeeded = 0;
      if(!EnumProcessModules(::GetCurrentProcess(),  nullptr,  0,  &dwNeeded)) 
      { 
         return ""; 
      } 
      unsigned int dwAlloc = (dwNeeded + sizeof(HMODULE)) * 2;
      HMODULE * pmodulea = __allocate< HMODULE[dwAlloc / sizeof >(HMODULE)]; 
      if(pmodulea == nullptr) 
         return ""; 
      if(!EnumProcessModules(::GetCurrentProcess(),  pmodulea,  dwAlloc,  &dwNeeded)) 
      { 
         delete pmodulea; 
         return ""; 
      } 
      string strModule; 
      ex1::file_system_pointer fs(pparticle);
      string strModuleFolder(papp->system()->get_ca2_module_folder());
      fs->FullPath(strModuleFolder, strModuleFolder);
      for(unsigned int dw = 0; dw < (dwNeeded / sizeof(HMODULE)); dw++)
      { 
         strModule.empty();
         GetModuleFileName(pmodulea[dw], strModule.get_buffer(4096), 4096); 
         strModule.ReleaseBuffer(); 
         fs->FullPath(strModule, strModule);
         if(case_insensitive_genstring_begins(strModule, strModuleFolder))
         { 
            if(!straSourceSalt.case_insensitive_contains(strModule)) 
            {
                return ""; 
            }
            string strHash = papp->system()->file36().md5(strModule); 
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
   return papp->system()->crypt().md5(strSalt);
}





static WINDOWS_DEFINITION_EXTENSION_MODULE VmscdadecDLL = { nullptr, nullptr };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, unsigned int dwReason, LPVOID lpReserved)
{
   // Remove this if you use lpReserved
   __UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      informationf("salt.DLL Initializing!\n");
      
      // Extension DLL one-time initialization
      if (!::windows_definition::InitExtensionModule(VmscdadecDLL, hInstance))
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

      ___new CDynLinkLibrary(VmscdadecDLL);
   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      informationf("salt.DLL Terminating!\n");
      // Terminate the library before destructors are called
      ::windows_definition::TermExtensionModule(VmscdadecDLL);
   }
   return 1;   // ok
}

