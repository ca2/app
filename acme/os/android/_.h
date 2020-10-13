#pragma once



//
//#include "_stdint.h"
//#include <asm/byteorder.h>

BEGIN_EXTERN_C


// The lockf() function is not available on Android; we translate to flock().
//#define F_LOCK LOCK_EX
//#define F_ULOCK LOCK_UN
CLASS_DECL_ACME int lockf(int fd, int cmd, off_t ignored_len);

CLASS_DECL_ACME void swab(const void *from, void*to, ssize_t n);
CLASS_DECL_ACME void* lfind( const void * key, const void * acme, size_t * num, size_t width, int (*fncomparison)(const void *, const void * ) );



END_EXTERN_C




oswindow get_capture();
oswindow set_capture(oswindow window);
int_bool release_capture();
oswindow set_focus(oswindow window);
oswindow get_focus();
oswindow get_window(oswindow window, int iParentHood);
oswindow get_active_window();
oswindow set_active_window(oswindow window);
int_bool destroy_window(oswindow window);
oswindow get_desktop_window();



