/*
    nanoui/object.h -- Object base class with support for reference counting

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */

#pragma once

#include "common.h"
#include <atomic>

namespace nanoui
{


/**
 * \class Object object.h nanoui/object.h
 *
 * \brief Reference counted object base class.
 */
   class CLASS_DECL_NANOUI Object :
      virtual public ::particle
   {
   public:
      /// Default constructor
      Object() { }

      /// Copy constructor
      //Object(const Object &) : m_ref_count(0) {}
      Object(const Object &) {}

      /// Return the current reference count
      ::count ref_count() const { return m_countReference; };
      //int ref_count() const { return 1; };

      /// Increase the object's reference count by one
      void inc_ref();

      /** \brief Decrease the reference count of
       * the object and possibly deallocate it.
       *
       * The object will automatically be deallocated once
       * the reference count reaches zero.
       */
      void dec_ref(bool dealloc = true);
   protected:
      /** \brief Virtual protected deconstructor.
       * (Will only be called by \::pointer ::pointer)
       */
      virtual ~Object();
   //private:
     //mutable std::atomic<int> m_ref_count{ 0 };
};

///**
// * \class ::pointer object.h nanoui/object.h
// *
// * \brief Reference counting helper.
// *
// * The \a ::pointer template is a simple wrapper to store a pointer to an object. It
// * takes care of increasing and decreasing the object's reference count as
// * needed. When the last reference goes out of scope, the associated object
// * will be deallocated.
// *
// * The advantage over C++ solutions such as ``::pointer`` is that
// * the reference count is very compactly integrated into the base object
// * itself.
// */
//template <typename T> class ::pointer {
//public:
//   /// Create a ``nullptr``-valued reference
//   ::pointer() { }
//
//   /// Construct a reference from a pointer
//   ::pointer(T * ptr) : m_ptr(ptr) {
//      if (m_ptr)
//         ((Object *)m_ptr)->inc_ref();
//   }
//
//   /// Copy constructor
//   ::pointer(const ::pointer & r) : m_ptr(r.m_ptr) {
//      if (m_ptr)
//         ((Object *)m_ptr)->inc_ref();
//   }
//
//   /// Move constructor
//   ::pointer(::pointer && r) noexcept : m_ptr(r.m_ptr) {
//      r.m_ptr = nullptr;
//   }
//
//   /// Destroy this reference
//   ~::pointer() {
//      if (m_ptr)
//         ((Object *)m_ptr)->dec_ref();
//   }
//
//   /// Move another reference into the current one
//   ::pointer & operator=(::pointer && r) noexcept {
//      if (&r != this) {
//         if (m_ptr)
//            ((Object *)m_ptr)->dec_ref();
//         m_ptr = r.m_ptr;
//         r.m_ptr = nullptr;
//      }
//      return *this;
//   }
//
//   /// Overwrite this reference with another reference
//   ::pointer & operator=(const ::pointer & r) noexcept {
//      if (m_ptr != r.m_ptr) {
//         if (r.m_ptr)
//            ((Object *)r.m_ptr)->inc_ref();
//         if (m_ptr)
//            ((Object *)m_ptr)->dec_ref();
//         m_ptr = r.m_ptr;
//      }
//      return *this;
//   }
//
//   /// Overwrite this reference with a pointer to another object
//   ::pointer & operator=(T * ptr) noexcept {
//      if (m_ptr != ptr) {
//         if (ptr)
//            ((Object *)ptr)->inc_ref();
//         if (m_ptr)
//            ((Object *)m_ptr)->dec_ref();
//         m_ptr = ptr;
//      }
//      return *this;
//   }
//
//   /// Compare this reference with another reference
//   bool operator==(const ::pointer & r) const { return m_ptr == r.m_ptr; }
//
//   /// Compare this reference with another reference
//   bool operator!=(const ::pointer & r) const { return m_ptr != r.m_ptr; }
//
//   /// Compare this reference with a pointer
//   bool operator==(const T * ptr) const { return m_ptr == ptr; }
//
//   /// Compare this reference with a pointer
//   bool operator!=(const T * ptr) const { return m_ptr != ptr; }
//
//   /// Access the object referenced by this reference
//   T * operator->() { return m_ptr; }
//
//   /// Access the object referenced by this reference
//   const T * operator->() const { return m_ptr; }
//
//   /// Return a C++ reference to the referenced object
//   T & operator*() { return *m_ptr; }
//
//   /// Return a const C++ reference to the referenced object
//   const T & operator*() const { return *m_ptr; }
//
//   /// Return a pointer to the referenced object
//   operator T * () { return m_ptr; }
//
//   /// Return a const pointer to the referenced object
//   T * get() { return m_ptr; }
//
//   /// Return a pointer to the referenced object
//   const T * get() const { return m_ptr; }
//
//   /// Check if the object is defined
//   operator bool() const { return m_ptr != nullptr; }
//private:
//   T * m_ptr = nullptr;
//};
//


} // namespace nanoui


