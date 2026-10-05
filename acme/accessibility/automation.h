#pragma once

// Backend-neutral accessibility automation. No window-system headers.
#include "acme/_start.h"
#include "acme/_.h"
#include "acme/exception/exception.h"
#include "acme/prototype/collection/pointer_array.h"
#include "acme/prototype/prototype/function.h"

namespace accessibility::automation
{
   enum class role { other, application, window, menu_bar, menu, menu_item,
      radio_menu_item, tab_list, tab, terminal };

   class element;
   using element_pointer = ::pointer<element>;
   using element_array = ::pointer_array<element>;

   class element : virtual public ::particle
   {
   public:
      ~element() override = default;
      virtual ::string name() = 0;
      virtual role type() = 0;
      virtual unsigned int process_id() = 0;
      // Optional verified executable identity supplied by the platform backend.
      virtual ::string executable_name() { return {}; }
      virtual element_array children() = 0;
      virtual element_pointer parent() = 0;
      virtual ::string_array_base actions() = 0;
      virtual bool perform_action(int index) = 0;
      virtual bool select_child(int index) = 0;
      virtual bool selected() = 0;
      virtual bool checked() = 0;
   };

   class traversal : virtual public ::particle
   {
   public:
      element_array m_elements;
      ::function<bool(element &)> m_matches;
      int m_remaining = 4096;
      class ::time m_timeStart;

      explicit traversal(const ::function<bool(element &)> &matches) :
         m_matches(matches), m_timeStart(::time::now()) {}

      void visit(const element_pointer &item, int depth = 0)
      {
         if (!item) return;
         if (m_timeStart.elapsed() > 5_s)
            throw ::exception(error_failed, "Accessibility traversal timed out");
         if (--m_remaining < 0 || depth > 24)
            throw ::exception(error_failed, "Accessibility traversal limit exceeded");
         if (m_matches(*item)) m_elements.add(item);
         if (item->type() == role::terminal) return;
         for (auto &child : item->children()) visit(child, depth + 1);
      }
   };

   // Bound traversal: terminal text, hostile trees and stale applications
   // must not make automation walk indefinitely.
   inline element_array find_all(const element_pointer &root,
      const ::function<bool(element &)> &predicate)
   {
      ::pointer<traversal> search = allocateø traversal(predicate);
      search->visit(root);
      return search->m_elements;
   }
}
