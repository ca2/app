#pragma once

namespace file
{
   // Optional provider capability; keeps remote protocols out of File Manager.
   // Called on a worker. Each displayed folder owns its opaque cursor.
   class folder_change_poller : virtual public ::particle
   {
   public:
      // An empty cursor starts monitoring. Return true to refresh the listing.
      // Throw on transient failure without advancing the cursor.
      virtual bool poll_folder_changes(const ::file::path & path, ::string & cursor) = 0;
   };
}
