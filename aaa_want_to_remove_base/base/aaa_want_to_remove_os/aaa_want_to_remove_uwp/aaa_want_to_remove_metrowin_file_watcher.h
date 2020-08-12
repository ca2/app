/**
	Implementation for Windows. Uses ReadDirectoryChangesW to watch for
	file system changes.

	@author James Wynn
	@date 4/15/2009

	Copyright (c) 2009 James Wynn (james@jameswynn.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/
#pragma once


namespace file_watcher
{


	/// Implementation for Win Merde based on StorageFolder::CreateFileQueryWithOptions.
	/// @class os_file_watcher
	class os_file_watcher :
      public file_watcher_impl
	{
   public:


      /// type for a map from id to watch_struct pointer
      typedef map < id, id, watch_holder, watch_holder > watch_map;


	private:


		/// Map of id to watch_struct pointers
		watch_map m_watchmap;
		/// The last watchid
		id m_idLast;


	public:


		os_file_watcher();
		virtual ~os_file_watcher();


		/// Add a directory watch
		/// @exception file_not_found_exception Thrown when the requested directory does not exist
		id add_watch(const string & directory, file_watch_listener * watcher, bool bRecursive);

		/// Remove a directory watch. This is a brute force lazy search O(nlogn).
		void remove_watch(const string & directory);

		/// Remove a directory watch. This is a map lookup O(logn).
		void remove_watch(id watchid);

      /// Return the directory name for a watch id
      string watch_path(id watchid);

		/// Updates the watcher. Must be called often.
		void update();

		/// Handles the action
		void handle_action(action * paction);


	}; // end os_file_watcher


} // namespace file_watcher






