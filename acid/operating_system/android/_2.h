#pragma once


BEGIN_EXTERN_C


CLASS_DECL_ACID int lockf(int fd, int cmd, off_t ignored_len);

CLASS_DECL_ACID void swab(const void *from, void*to, ssize_t n);
CLASS_DECL_ACID void* lfind( const void * key, const void * acid, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) );



END_EXTERN_C


