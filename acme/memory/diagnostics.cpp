// Bounded, allocation-independent Windows allocator diagnostics. No framework calls.
// Legacy _snprintf uses I64 on both XP MSVCRT and current Windows CRTs.
#if defined(MEMORY_DIAGNOSTICS) && defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include "diagnostics.h"

namespace {
constexpr unsigned slots = 1u << 17, groups = 8192, frames = 20;
struct allocation { void *pointer; size_t size; unsigned group; };
struct site {
   void *stack[frames]; unsigned depth;
   unsigned long long bytes, count, previous;
   char annotation[64];
};
allocation *table;
site *sites;
unsigned site_count = 1;
unsigned site_index[groups*2];
bool initialized;
volatile LONG gate;
thread_local bool inside;
HANDLE output = INVALID_HANDLE_VALUE;
DWORD last_report, last_sites;
unsigned long long live_bytes, live_count, allocations, frees, reallocations;
unsigned long long dropped, unmatched, sequence;
unsigned long long written;
typedef USHORT (WINAPI *capture_function)(ULONG, ULONG, PVOID *, PULONG);
capture_function capture;

void write(const char *s) {
   if (output != INVALID_HANDLE_VALUE && written < 64u*1024*1024) {
      DWORD done=0; WriteFile(output, s, (DWORD)lstrlenA(s), &done, nullptr);
      written+=done;
   }
}
void initialize() {
   table = (allocation *)VirtualAlloc(nullptr, sizeof(allocation)*slots,
      MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
   sites = (site *)VirtualAlloc(nullptr, sizeof(site)*groups,
      MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
   capture = (capture_function)GetProcAddress(GetModuleHandleA("kernel32.dll"),
      "RtlCaptureStackBackTrace");
   char path[MAX_PATH], suffix[64];
   DWORD n = GetEnvironmentVariableA("CA2_MEMORY_DIAGNOSTICS_LOG", path, MAX_PATH);
   if (!n || n >= MAX_PATH) {
      n = GetModuleFileNameA(nullptr, path, MAX_PATH);
      if (!n || n >= MAX_PATH) { path[0] = 0; n = 0; }
      while (n && path[n-1] != '\\' && path[n-1] != '/') --n;
      path[n] = 0;
      _snprintf(suffix, sizeof(suffix), "ca2-memory-%lu.log", GetCurrentProcessId());
      if (n + lstrlenA(suffix) < MAX_PATH) lstrcatA(path, suffix);
   }
   output = CreateFileA(path, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
      nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
   write("MEMORY_DIAGNOSTICS: live Windows allocator block bytes, not per-object or process committed memory. Small stacks sampled 1/32; >=16KiB stacks all captured. Log limit 64MiB.\r\n");
   char line[160];
   _snprintf(line, sizeof(line), "tracker_storage=%I64u capacity=%u groups=%u stack_capture=%u\r\n",
      (unsigned long long)(sizeof(allocation)*slots+sizeof(site)*groups), slots, groups, capture != nullptr);
   write(line);
   last_report = last_sites = GetTickCount();
   initialized=true;
}
struct guard {
   DWORD error; bool entered;
   guard() : error(GetLastError()), entered(!inside) {
      if (!entered) return;
      inside = true;
      while (InterlockedCompareExchange(&gate, 1, 0)) Sleep(0);
      if (!initialized) initialize();
   }
   ~guard() {
      if (entered) { InterlockedExchange(&gate, 0); inside = false; }
      SetLastError(error);
   }
};
unsigned hash_pointer(void *p) { return (unsigned)(((uintptr_t)p >> 4)*2654435761u)&(slots-1); }
unsigned find_site(size_t size, const char *annotation) {
   if ((++sequence & 31) && size < 16384) return 0;
   void *stack[frames] = {};
   unsigned depth = capture ? capture(3, frames, stack, nullptr) : 0;
   if (!depth) return 0;
   unsigned hash=2166136261u;
   for (unsigned j=0;j<depth;++j) hash=(hash^(unsigned)(uintptr_t)stack[j])*16777619u;
   unsigned bucket=hash&(groups*2-1);
   for (unsigned n=0;n<groups*2;++n, bucket=(bucket+1)&(groups*2-1)) {
      unsigned i=site_index[bucket];
      if (!i) break;
      if (sites[i].depth != depth) continue;
      unsigned j=0; while (j<depth && sites[i].stack[j]==stack[j]) ++j;
      if (j==depth) return i;
   }
   if (site_count == groups) { ++dropped; return 0; }
   unsigned i = site_count++;
   site_index[bucket]=i;
   sites[i].depth = depth;
   for (unsigned j=0; j<depth; ++j) sites[i].stack[j]=stack[j];
   if (annotation) {
      unsigned j=0; for (; j<63 && annotation[j]; ++j) {
         char c=annotation[j]; sites[i].annotation[j]=(c=='\r'||c=='\n')?' ':c;
      }
      sites[i].annotation[j]=0;
   }
   return i;
}
void add(void *p, size_t size, const char *annotation) {
   if (!p || !table || !sites) return;
   unsigned start=hash_pointer(p), vacant=slots;
   for (unsigned j=0; j<slots; ++j) {
      unsigned i=(start+j)&(slots-1);
      if (table[i].pointer == (void *)1) { vacant=i; break; }
      if (!table[i].pointer) { if (vacant==slots) vacant=i; break; }
   }
   if (vacant==slots) { ++dropped; return; }
   unsigned group=find_site(size, annotation);
   table[vacant]={p,size,group};
   live_bytes+=size; ++live_count;
   sites[group].bytes+=size; ++sites[group].count;
}
void remove(void *p) {
   if (!p || !table || !sites) return;
   unsigned start=hash_pointer(p);
   for (unsigned j=0; j<slots; ++j) {
      allocation &a=table[(start+j)&(slots-1)];
      if (!a.pointer) break;
      if (a.pointer != p) continue;
      live_bytes-=a.size; --live_count;
      sites[a.group].bytes-=a.size; --sites[a.group].count;
      a.pointer=(void *)1; return;
   }
   ++unmatched;
}
void report(bool force) {
   if (!sites) return;
   DWORD now=GetTickCount();
   if (!force && (DWORD)(now-last_report)<1000) return;
   last_report=now;
   char line[512];
   _snprintf(line,sizeof(line),
      "tick=%lu live_bytes=%I64u live_count=%I64u alloc=%I64u free=%I64u realloc=%I64u dropped=%I64u unmatched_free=%I64u\r\n",
      now,live_bytes,live_count,allocations,frees,reallocations,dropped,unmatched);
   write(line);
   if (!force && (DWORD)(now-last_sites)<5000) return;
   last_sites=now;
   unsigned best[12]={};
   for (unsigned i=1; i<site_count; ++i) {
      for (unsigned j=0; j<12; ++j) {
         long long delta=(long long)sites[i].bytes-(long long)sites[i].previous;
         long long other=(long long)sites[best[j]].bytes-(long long)sites[best[j]].previous;
         if (!best[j] || delta>other) {
            for (unsigned k=11; k>j; --k) best[k]=best[k-1];
            best[j]=i; break;
         }
      }
   }
   for (unsigned k=0; k<12 && best[k]; ++k) {
      unsigned i=best[k]; site &s=sites[i];
      _snprintf(line,sizeof(line),"site=%u live_bytes=%I64u live_count=%I64u delta=%I64d stack=",
         i,s.bytes,s.count,(long long)s.bytes-(long long)s.previous);
      write(line);
      for (unsigned j=0;j<s.depth;++j) {
         _snprintf(line,sizeof(line),"%p ",s.stack[j]); write(line);
      }
      write("\r\n");
      if (s.annotation[0]) { write("annotation="); write(s.annotation); write("\r\n"); }
   }
   for (unsigned i=1;i<site_count;++i) sites[i].previous=sites[i].bytes;
}
}
extern "C" void ca2_memory_diagnostics_allocate(void *p, size_t size, const char *annotation) {
   guard g; if (!g.entered) return;
   if (p) { ++allocations; add(p,size,annotation); } report(false);
}
extern "C" void ca2_memory_diagnostics_free(void *p) {
   guard g; if (!g.entered) return;
   if (p) { ++frees; remove(p); } report(false);
}
extern "C" void ca2_memory_diagnostics_reallocate(void *old_p, void *new_p, size_t size, const char *annotation) {
   guard g; if (!g.entered) return;
   ++reallocations;
   // A failed nonzero realloc leaves the old allocation live.
   if (new_p) { remove(old_p); add(new_p,size,annotation); }
   report(false);
}
extern "C" __declspec(dllexport) void ca2_memory_diagnostics_snapshot() {
   // A debugger may call this with every other thread stopped; never wait for
   // a lock held by a stopped allocator thread.
   DWORD error=GetLastError();
   if (!inside && !InterlockedCompareExchange(&gate,1,0)) {
      inside=true;
      if (initialized) report(true);
      inside=false; InterlockedExchange(&gate,0);
   }
   SetLastError(error);
}
#endif
