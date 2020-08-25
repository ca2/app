#pragma once


//  UTILITY MACROS
//
// @author Gurmeet S. Kochar


/*
  
  SAFE_POINTER_DELETE
  Deletes the specified pointer, if non-nullptr, and sets 
  it to nullptr after deletion.
 
  @lparam ::point pointer to delete
 
  @since Mar 08, 2004
  @author Gurmeet S. Kochar

 */

#define SAFE_DELETE_POINTER(_P) \
(void)(_P != nullptr ? delete _P, _P = nullptr : 0) \

