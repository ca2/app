#include "folder_google_drive/platform.h"
#include "folder_google_drive/folder.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"
#include <stdexcept>
#include <vector>

class mock_drive : public ::folder_google_drive::folder
{
public:
   struct reply { const char * json; int status = 200; };
   std::vector<reply> replies;
   std::vector<::string> urls;
   ::payload poll_request(const ::scoped_string & url, ::property_set & options) override
   {
      urls.emplace_back(url);
      if (replies.empty()) throw std::runtime_error("unexpected request");
      auto reply = replies.front(); replies.erase(replies.begin());
      options["http_status_code"] = reply.status;
      if (reply.status != 200) throw std::runtime_error("mock HTTP failure");
      ::payload result; result.parse_network_payload(reply.json); return result;
   }
};

void require(bool value) { if (!value) throw std::runtime_error("polling assertion failed"); }

int main()
{
   ::acme::acme runtime;
   ::platform::system testSystem;
   ::exception::s_bEnableCallStackBackTrace = false;
   mock_drive drive;
   ::fs::data * provider = &drive;
   auto capability = dynamic_cast<::file::folder_change_poller *>(provider);
   require(capability != nullptr);
   ::string cursor;
   drive.replies = {{R"({"startPageToken":"initial"})"}};
   require(capability->poll_folder_changes("google-drive://", cursor));
   require(cursor == "initial");
   drive.replies = {{R"({"changes":[],"newStartPageToken":"idle"})"}};
   require(!drive.poll_folder_changes("google-drive://", cursor)); require(cursor == "idle");
   drive.replies = {{R"({"changes":[{"fileId":"new"}],"nextPageToken":"page2"})"},
      {R"({"changes":[{"fileId":"gone","removed":true}],"newStartPageToken":"done"})"}};
   require(drive.poll_folder_changes("google-drive://", cursor)); require(cursor == "done");
   drive.replies = {{R"({"changes":[{"fileId":"new"}],"nextPageToken":"page2"})"}, {"{}",503}};
   bool failed = false;
   try { drive.poll_folder_changes("google-drive://", cursor); }
   catch (...) { failed = true; }
   require(failed && cursor == "done"); // No advancement after partial failure.
   drive.replies = {{"{}",410}};
   require(drive.poll_folder_changes("google-drive://", cursor)); require(cursor.is_empty());
   drive.replies = {{"{}"}};
   failed = false;
   try { drive.poll_folder_changes("google-drive://", cursor); }
   catch (...) { failed = true; }
   require(failed && cursor.is_empty());
   cursor = "same";
   drive.replies = {{R"({"changes":[],"nextPageToken":"same"})"}};
   failed = false;
   try { drive.poll_folder_changes("google-drive://", cursor); } catch (...) { failed = true; }
   require(failed && cursor == "same");
}
