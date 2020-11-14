#pragma once




//CLASS_DECL_AURA ::u32 get_last_error();
//CLASS_DECL_AURA void set_last_error(::u32 dw);




/// Class with static functions to get information about an error.
class CLASS_DECL_AURA c_error
{
public:

   inline static ::u32 get_last_error()
   {

      return errno;

   }

   inline static string GetErrorDescription(int iErrorCode = get_last_error())
   {

      return strerror(iErrorCode);

   }

};


#ifdef __WIN32
/// Class with static functions to get information about an error.
class CLASS_DECL_AURA sys_error
{
public:

   static ::u32 get_last_error() { return ::get_last_error(); }

   static string GetErrorDescription(int iErrorCode = get_last_error())
   {
      LPVOID pMsgBuf = nullptr;

      format_message(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    nullptr, iErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                    reinterpret_cast<char *>(&pMsgBuf), 0, nullptr);

      string strErrorDescription;
      if (pMsgBuf)

      {
         strErrorDescription = reinterpret_cast<char *>(pMsgBuf);

         LocalFree(pMsgBuf);

      }
      return strErrorDescription;
   }
};
#else

class CLASS_DECL_AURA sys_error : public c_error
{
public:

};

#endif


