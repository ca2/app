#pragma once

/* GLOBAL.H - RSAREF types and constants
 */

/* PROTOTYPES should be set to one if and only if the compiler supports
  function argument prototyping.
The following makes PROTOTYPES default to 0 if it has not already

  been defined with C compiler flags.
 */
#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif

/* POINTER defines a matter pointer type */
typedef ::u8 * POINTER;

/* ::u16 defines a two ::u8 ::u16 */
typedef ::u16 ush;

/* ::u32 defines a four ::u8 ::u16 */
typedef ::u32 ui;

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above.
If using PROTOTYPES, then PROTO_LIST returns the list_base, otherwise it
  returns an is_empty list_base.
 */
#if PROTOTYPES
#define PROTO_LIST(list_base) list_base
#else
#define PROTO_LIST(list_base) ()
#endif

