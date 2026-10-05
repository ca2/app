#pragma once
#include "automation.h"


namespace accessibility::automation
{
   using predicate = ::function<bool(element &)>;
   using settle_function = ::procedure;

   // Application/window enumeration is deliberately distinct from recursive
   // control search, so a window title cannot masquerade as an application.
   inline element_array applications(const element_pointer &desktop,
      const predicate &matches)
   {
      element_array result;
      for (auto &item : desktop->children())
         if (item->type() == role::application && matches(*item)) result.add(item);
      return result;
   }

   inline element_array windows(const element_pointer &application,
      const predicate &matches = [](element &) { return true; })
   {
      element_array result;
      for (auto &item : application->children())
         if (item->type() == role::window && matches(*item)) result.add(item);
      return result;
   }

   class session : virtual public ::particle
   {
   public:
      element_pointer m_desktop;
      explicit session(const element_pointer &desktop) : m_desktop(desktop)
      {
         if (!m_desktop) throw ::exception(error_failed, "No accessibility desktop for this session");
      }
      element_array applications(const predicate &matches)
      { return ::accessibility::automation::applications(m_desktop, matches); }
      element_array windows(const element_pointer &application,
         const predicate &matches = [](element &) { return true; })
      { return ::accessibility::automation::windows(application, matches); }
   };

   inline void invoke(const element_pointer &item)
   {
      auto actions = item->actions();
      int index = -1;
      for (int i = 0; i < static_cast<int>(actions.get_count()); ++i)
         if (actions[i] == "click" || actions[i] == "activate") { index = i; break; }
      if (index < 0 && actions.get_count() == 1) index = 0;
      if (index < 0 || !item->perform_action(index))
         throw ::exception(error_failed, "Cannot activate accessible item: " + item->name());
   }

   inline element_pointer menu_item(const element_pointer &window, const predicate &matches)
   {
      auto bars = find_all(window, [](element &e) { return e.type() == role::menu_bar; });
      element_array items;
      for (auto &bar : bars)
      {
         auto found = find_all(bar, [&](element &e)
         {
            auto type = e.type();
            return (type == role::menu_item || type == role::radio_menu_item
               || type == role::radio_button || type == role::check_menu_item
               || type == role::check_box) && matches(e);
         });
         items.append(found);
      }
      if (items.get_count() != 1)
         throw ::exception(error_failed, "Expected one accessible menu item, found "
            + ::as_string(items.get_count()) + "; ensure the menubar is visible");
      return items.first();
   }

   inline void select_menu_item(const element_pointer &window, const predicate &matches,
      const settle_function &settle, bool verify_checked = false)
   {
      auto item = menu_item(window, matches);
      if (verify_checked && item->checked()) return;
      element_array ancestors;
      auto parent = item->parent();
      bool reached_bar = false;
      for (int depth = 0; parent && depth < 24; ++depth)
      {
         auto type = parent->type();
         if (type == role::menu_bar) { reached_bar = true; break; }
         if ((type == role::menu || type == role::menu_item) && !parent->actions().is_empty())
            ancestors.add(parent);
         parent = parent->parent();
      }
      if (!reached_bar) throw ::exception(error_failed, "Cannot find the accessible menu ancestry");
      for (::collection::index i = ancestors.get_count(); i > 0; --i)
      { invoke(ancestors[i - 1]); settle(); }
      invoke(menu_item(window, matches)); // GTK can rebuild opened menus.
      settle();
      if (verify_checked && !menu_item(window, matches)->checked())
         throw ::exception(error_failed, "Accessible menu selection was not applied");
   }

   // Run a caller-defined operation in each tab, preserving the selection.
   // A window without a tab list is treated as a single view.
   inline int for_each_tab(const element_pointer &window,
      const ::procedure &operation, const settle_function &settle)
   {
      auto notebooks = find_all(window, [](element &e) { return e.type() == role::tab_list; });
      if (notebooks.is_empty()) { operation(); return 1; }
      if (notebooks.get_count() != 1) throw ::exception(error_failed, "Ambiguous accessible tab list");
      auto notebook = notebooks.first();
      auto pages = notebook->children();
      int original = -1;
      for (int i = 0; i < static_cast<int>(pages.get_count()); ++i)
         if (pages[i]->type() == role::tab && pages[i]->selected()) original = i;
      if (original < 0) throw ::exception(error_failed, "Cannot determine the selected tab");
      auto restore = [&]
      {
         if (!notebook->select_child(original))
            throw ::exception(error_failed, "Cannot restore the original tab");
         settle();
         if (!pages[original]->selected())
            throw ::exception(error_failed, "Original tab selection was not restored");
      };
      int applied = 0;
      try
      {
         for (int i = 0; i < static_cast<int>(pages.get_count()); ++i)
         {
            if (pages[i]->type() != role::tab) continue;
            if (!notebook->select_child(i)) throw ::exception(error_failed, "Cannot select accessible tab");
            settle();
            if (!pages[i]->selected()) throw ::exception(error_failed, "Tab selection was not applied");
            operation(); ++applied;
         }
      }
      catch (...)
      {
         restore(); throw;
      }
      restore(); return applied;
   }
}
