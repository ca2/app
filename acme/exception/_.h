#pragma once





CLASS_DECL_ACME bool should_avoid_parsing_exception();
CLASS_DECL_ACME bool throw_parsing_exception(const ::scoped_string & scopedstrMessage);




CLASS_DECL_ACME bool throw_network_payload_parsing_exception(const ::scoped_string & scopedstrMessage);






#if defined(NNDEBUG) && !defined(___NO_DEBUG_CRT)



#define __output_debug_string TRACE

// turn on/off tracking for a i16 while
CLASS_DECL_ACME bool __enable_memory_tracking(bool bTrack);

// Turn on/off the global flag gen_MemoryLeakOverride. if bEnable is true
// then further calls to __enable_memory_tracking() wont machine the current
// memory tracking state, until __enable_memory_leak_override(bool bEnable)
// is called again with bEnable == false.
CLASS_DECL_ACME bool __enable_memory_leak_override(bool bEnable);




#else

// non-DEBUG_ALLOC version that assume everything is OK
#define __enable_memory_tracking(bTrack) false
#define __enable_memory_leak_override(bEnable) true
#define __output_debug_string(psz) ::output_debug_string(psz)



#endif // NNDEBUG




#ifdef NNDEBUG


#define DEBUG_NOTE __FILE__


#define THREAD_NOTE __get_thread_note()
#define SET_THREAD_NOTE(x) __set_thread_note(x);


#else //NNDEBUG


#define SET_THREAD_NOTE(x)


#endif //NNDEBUG


#define ENSURE_THROW(cond, exception)   \
   do { i32 _gen__condVal=!!(cond); ASSERT(_gen__condVal); if (!(_gen__condVal)){exception;} } while (false)
#define ENSURE(cond)      ENSURE_THROW(cond, throw_exception(error_bad_argument))
#define ENSURE_ARG(cond)   ENSURE_THROW(cond, throw_exception(error_bad_argument))

// Debug ASSERT_VALIDs then throws. Retail throws if pOb is nullptr
#define ENSURE_VALID_THROW(pOb, exception)   \
   do { ASSERT_VALID(pOb); if (!(pOb)){exception;} } while (false)
#define ENSURE_VALID(pOb)   ENSURE_VALID_THROW(pOb, throw_exception(error_bad_argument))

#define ASSERT_POINTER(p, type) \
   ASSERT(((p) != nullptr) && is_memory_segment_ok((p), sizeof(type), false))

#define ASSERT_NULL_OR_POINTER(p, type) \
   ASSERT(((p) == nullptr) || is_memory_segment_ok((p), sizeof(type), false))


CLASS_DECL_ACME errno_t c_runtime_error_check(errno_t error);
CLASS_DECL_ACME void __cdecl __clearerr_s(FILE *stream);



CLASS_DECL_ACME bool __assert_failed_line(const ::ansi_character * pszFileName, int nLine);

CLASS_DECL_ACME void __assert_particle_ok(const ::particle * pparticle, const ::ansi_character * pszFileName, i32 nLine);

CLASS_DECL_ACME void __dump(const ::particle * pparticle);



