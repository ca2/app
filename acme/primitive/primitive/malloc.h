//
//  malloc.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/06/19.
//


#define MALLOC_NEW(p, type) \
p = (type *) ::malloc(sizeof(type)); \
memory_new(p) type;

#define MALLOC_DEL(p, type) \
if(::is_set(p)) { \
p->~type(); \
::free(p); }



