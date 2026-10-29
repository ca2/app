#pragma once

namespace freedesktop
{
   // The Wayland app_id must match the installed .desktop basename.
   inline ::string desktop_application_id(const ::scoped_string & appId)
   {
      ::string id(appId);
      id.find_replace("/", ".");
      return id;
   }
}
