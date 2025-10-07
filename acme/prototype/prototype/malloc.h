//
//  malloc.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 02/06/19.
//


#define MALLOC_NEW(p, type) \
p = (type *) ::malloc(sizeof(type)); \
øallocate<  >(p) type;

#define MALLOC_DEL(p, type) \
if(::is_set(p)) { \
p->~type(); \
::free(p); }



