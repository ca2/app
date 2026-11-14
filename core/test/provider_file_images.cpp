#include "core/platform.h"
#include "aura/user/user/shell.h"
#include "aura/graphics/image/context.h"
#include "apex/filesystem/fs/set.h"
#include "acme/filesystem/file/folder.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"

namespace
{
   class image_provider : public ::fs::data, public ::folder, public ::file::image_info_provider
   {
   public:
      bool enumerate(::file::listing_base &) override { return false; }
      ::file::image_info m_info;
      int m_iCalls = 0;
      bool get_file_image_info(const ::file::path &, ::file::image_info & info) override
      {
         ++m_iCalls;
         info = m_info;
         return true;
      }
   };

   class ordinary_provider : public ::fs::data
   {
   public:
      int m_iListCalls = 0;
      bool list_base(::string_array_base &, const ::scoped_string &, ::file::e_flag) override
      {
         ++m_iListCalls;
         return true;
      }
   };

   class image_decoder : public ::image::image_context
   {
   public:
      ::file::path m_pathDecoded;
      bool m_bThrow = false;
      ::image::image_pointer load_image(const ::payload & file, const ::image::load_options &) override
      {
         m_pathDecoded = file.as_file_path();
         if (m_bThrow) throw ::exception(error_failed);
         return {}; // Simulate an unavailable/corrupt cached image: generic icon must still work.
      }
   };

   class image_shell : public ::user::shell
   {
   public:
      using ::user::shell::get_file_image;
      image_key m_key;
      int m_iGenericRequests = 0;
      int m_iOsThumbnailRequests = 0;
      void disable_atlas_for_reservation_test() { m_iaSize.erase_all(); }
      ::i32 get_file_image(const image_key & key) override { m_key = key; return 17; }
      bool get_image_by_file_extension(_get_file_image_ & request) override
      {
         ++m_iGenericRequests;
         request.m_iImage = 17;
         return true;
      }
      bool defer_set_thumbnail(_get_file_image_ &) override { ++m_iOsThumbnailRequests; return false; }
   };
}

int main()
{
   ::platform::system testSystem;
   ::exception::s_bEnableCallStackBackTrace = false;
   ::pointer < ::platform::application > app(allocate_t{});
   app->m_papplication = app;
   ::pointer < image_decoder > decoder(allocate_t{});
   app->m_pimagecontext = decoder;
   ::pointer < image_provider > provider(allocate_t{});
   ::pointer < ::fs::set > router(allocate_t{});
   router->m_papplication = app;
   router->fsmap()["test://"] = provider;
   ::pointer < image_shell > shell(allocate_t{});
   shell->m_papplication = app;
   provider->m_info.m_strName = "photo.webp";
   shell->get_file_image("test://opaque-id", ::user::shell::e_file_attribute_normal,
      ::user::shell::e_icon_normal, router);
   if (provider->m_iCalls != 1 || !shell->m_key.m_bProviderImage || shell->m_key.m_strExtension != "webp") return 1;
   auto original = shell->m_key;
   ::user::shell::_get_file_image_ request;
   request.m_imagekey = original;
   if (!shell->defer_get_provider_image(request) || shell->m_iGenericRequests != 1) return 2;

   provider->m_info.m_bFolder = true;
   ::folder & folderInterface = *provider;
   shell->get_file_image("test://folder-id", ::user::shell::e_file_attribute_normal,
      ::user::shell::e_icon_open, &folderInterface);
   if (shell->m_key.m_eattribute != ::user::shell::e_file_attribute_directory) return 3;

   provider->m_info.m_bFolder = false;
   provider->m_info.m_strLocalThumbnailPath = "C:/cache/opaque-id/42";
   shell->get_file_image("test://opaque-id", ::user::shell::e_file_attribute_normal,
      ::user::shell::e_icon_normal, router);
   if (original == shell->m_key) return 4; // A newly available cached thumbnail invalidates the generic icon.
   ::user::shell::image_key copied(shell->m_key);
   if (!(copied == shell->m_key)) return 5;
   request.m_imagekey = copied;
   if (!shell->defer_get_provider_image(request)) return 6;
   if (decoder->m_pathDecoded != "C:/cache/opaque-id/42" || shell->m_iOsThumbnailRequests != 0
      || shell->m_iGenericRequests != 2) return 7;

   decoder->m_bThrow = true;
   request.m_imagekey = copied;
   if (!shell->defer_get_provider_image(request) || shell->m_iGenericRequests != 3) return 9;

   ::pointer < ordinary_provider > ordinary(allocate_t{});
   router->fsmap()["ordinary://"] = ordinary;
   ::file::image_info ordinaryInfo;
   if (router->get_file_image_info("ordinary://entry", ordinaryInfo) || ordinary->m_iListCalls != 0) return 12;
   shell->get_file_image("native.png", ::user::shell::e_file_attribute_normal,
      ::user::shell::e_icon_normal, ordinary);
   request.m_imagekey = shell->m_key;
   if (request.m_imagekey.m_bProviderImage || shell->defer_get_provider_image(request)) return 8;
   shell->disable_atlas_for_reservation_test();
   request.m_imagekey = original;
   shell->m_imagemap[original] = (::i32)0x80000001;
   if (!shell->reserve_image(request)) return 10; // Queued requests still need a real slot.
   shell->m_imagemap[original] = 17;
   if (shell->reserve_image(request) || request.m_iImage != 17) return 11;
   return 0;
}
