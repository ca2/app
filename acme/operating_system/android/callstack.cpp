// From stackoflw by camilo on 2022-04-30 00:02 <3ThomasBorregaardSorensen!!
// https://stackoverflow.com/questions/8115192/android-ndk-getting-the-backtrace
#include "framework.h"
#include "acme/platform/node.h"
//#include <iostream>
//#include <iomanip>

#include <unwind.h>
#include <dlfcn.h>
#include <cxxabi.h>

namespace
{

   struct BacktraceState
   {
      void ** current;
      void ** end;
   };

   static _Unwind_Reason_Code unwindCallback(struct _Unwind_Context * context, void * arg)
   {
      BacktraceState * state = static_cast<BacktraceState *>(arg);
      uintptr_t pc = _Unwind_GetIP(context);
      if (pc) {
         if (state->current == state->end) {
            return _URC_END_OF_STACK;
         }
         else {
            *state->current++ = reinterpret_cast<void *>(pc);
         }
      }
      return _URC_NO_REASON;
   }

}


void captureBacktrace(void ** buffer, int & framecount)
{

   BacktraceState state = { buffer, buffer + framecount };

   _Unwind_Backtrace(unwindCallback, &state);

   framecount = state.current - buffer;

}


void dumpBacktrace(string & str, void ** buffer, int count)
{

   for (size_t idx = 0; idx < count; ++idx)
   {

      const void * addr = buffer[idx];

      const char * symbol = "";

      Dl_info info;

      if (dladdr(addr, &info) && info.dli_sname)
      {

         symbol = info.dli_sname;

      }

      int status = 0;

      char *demangled = nullptr;

      if(symbol)
      {

         demangled = __cxxabiv1::__cxa_demangle(symbol, 0, 0, &status);

      }

      string strLine;

      strLine.formatf("#02%d: 0x%" PRIXPTR " %s\n", idx, addr, (demangled && status == 0) ? demangled : symbol);

      str += strLine;

      if (::is_set(demangled))
      {

         free(demangled);

      }

      // os << "  #" << std::setw(2) << idx << ": " << addr << "  " << symbol << "\n";

   }

}


namespace platform
{


    void node::get_call_stack_frames(void ** stack, int & frame_count)
    {

       const int iMaximumFramesToCapture = 96;

       frame_count = minimum(frame_count, iMaximumFramesToCapture);

       ::captureBacktrace(stack, frame_count);

    }

//
//    void node::defer_update_callstack()
//   {
//
//   }

   
//   string node::get_callstack(const ::scoped_string & scopedstrFormat, int iSkip, void * /* caller_address */, int iCount)
//   {
//
//      string strCallStack;
//
//
//      const size_t max = 128;
//      void* buffer[max];
//
//      dumpBacktrace(strCallStack, buffer, captureBacktrace(buffer, max));
//
//
//      return strCallStack;
//
//   }
//

    string node::_get_call_stack_trace(const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
    {

      string strCallStack;

      int len = 128;

      ::array < void * > buffer;

      buffer.set_size(len);

      captureBacktrace(buffer.data(), len);

      dumpBacktrace(strCallStack, buffer.data(), len);

      return strCallStack;

    }



} // namespace node



