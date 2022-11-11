#pragma once



BEGIN_EXTERN_C


CLASS_DECL_APEX int lockf(int fd, int cmd, off_t ignored_len);

CLASS_DECL_APEX void swab(const void *from, void*to, ssize_t n);
CLASS_DECL_APEX void* lfind( const void * key, const void * apex, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) );



END_EXTERN_C




