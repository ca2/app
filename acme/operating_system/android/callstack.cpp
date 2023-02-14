// From stackoflw by camilo on 2022-04-30 00:02 <3ThomasBorregaardS�rensen!!
// https://stackoverflow.com/questions/8115192/android-ndk-getting-the-backtrace
#include "framework.h"
#include "acme/platform/node.h"
//#include <iostream>
//#include <iomanip>

#include <unwind.h>
#include <dlfcn.h>

namespace {

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

size_t captureBacktrace(void ** buffer, size_t max)
{
   BacktraceState state = { buffer, buffer + max };
   _Unwind_Backtrace(unwindCallback, &state);

   return state.current - buffer;
}

void dumpBacktrace(string & str, void ** buffer, size_t count)
{
   for (size_t idx = 0; idx < count; ++idx) {
      const void * addr = buffer[idx];
      const char * symbol = "";

      Dl_info info;
      if (dladdr(addr, &info) && info.dli_sname) {
         symbol = info.dli_sname;
      }

      string strLine;
      strLine.format("#02%d: 0x%" PRIXPTR " %s\n", idx, addr, symbol);
      str += strLine;

      // os << "  #" << std::setw(2) << idx << ": " << addr << "  " << symbol << "\n";
   }
}


namespace acme
{

   
   void node::defer_update_callstack()
   {

   }

   
   string node::get_callstack(const ::scoped_string & scopedstrFormat, i32 iSkip, void * /* caller_address */, int iCount)
   {

      string strCallStack;


      const size_t max = 128;
      void* buffer[max];

      dumpBacktrace(strCallStack, buffer, captureBacktrace(buffer, max));


      return strCallStack;

   }


} // namespace node



