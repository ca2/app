#include "platform.h"
#include "acme/graphics/image/pixmap.h"

#include <array>
#include <cstddef>
#include <cstring>
#include <vector>


namespace
{


   constexpr std::size_t g_guardSize = 16;


   bool bytes_equal(
      const unsigned char *pdata,
      std::size_t size,
      unsigned char value)
   {

      for (std::size_t i = 0; i < size; ++i)
      {

         if (pdata[i] != value)
         {

            return false;

         }

      }

      return true;

   }


   template <std::size_t HEIGHT>
   bool padded_vertical_swap_matches(
      int width,
      int stride,
      const std::array<unsigned char, HEIGHT> &rowValues,
      const std::array<unsigned char, HEIGHT> &expectedRowValues,
      const std::array<unsigned char, HEIGHT> &paddingValues)
   {

      auto iRowBytes = width * (int)sizeof(::image32_t);
      auto pixelBytes = (std::size_t)stride * HEIGHT;
      auto totalBytes = g_guardSize + pixelBytes + g_guardSize;

      std::vector<::image32_t> storage(
         totalBytes / sizeof(::image32_t));

      auto pstorage = reinterpret_cast<unsigned char *>(storage.data());

      std::memset(pstorage, 0xe1, g_guardSize);
      std::memset(
         pstorage + g_guardSize + pixelBytes,
         0xe2,
         g_guardSize);

      auto pdata = pstorage + g_guardSize;

      for (std::size_t y = 0; y < HEIGHT; ++y)
      {

         auto prow = pdata + y * stride;

         std::memset(prow, rowValues[y], iRowBytes);
         std::memset(
            prow + iRowBytes,
            paddingValues[y],
            stride - iRowBytes);

      }

      ::pixmap_t pixmap;
      pixmap.initialize_pixmap(
         {width, (int)HEIGHT},
         reinterpret_cast<::image32_t *>(pdata),
         stride);

      pixmap.vertical_swap();

      for (std::size_t y = 0; y < HEIGHT; ++y)
      {

         auto prow = pdata + y * stride;

         if (!bytes_equal(
               prow,
               iRowBytes,
               expectedRowValues[y]))
         {

            return false;

         }

         if (!bytes_equal(
               prow + iRowBytes,
               stride - iRowBytes,
               paddingValues[y]))
         {

            return false;

         }

      }

      return
         bytes_equal(pstorage, g_guardSize, 0xe1) &&
         bytes_equal(
            pstorage + g_guardSize + pixelBytes,
            g_guardSize,
            0xe2);

   }


   bool malformed_overflowing_width_does_not_mutate()
   {

      alignas(::image32_t)
         std::array<unsigned char, 24> storage{};

      std::memset(storage.data(), 0x11, 8);
      std::memset(storage.data() + 8, 0x22, 8);
      std::memset(storage.data() + 16, 0x33, 8);

      auto expected = storage;

      ::pixmap_t pixmap;
      pixmap.initialize_pixmap(
         {0x40000001, 2},
         reinterpret_cast<::image32_t *>(storage.data()),
         8);

      pixmap.vertical_swap();

      return storage == expected;

   }


   bool mapping_external_storage_preserves_its_address()
   {

      std::array<::image32_t, 4> storage{};

      ::pixmap pixmap;
      pixmap.initialize_pixmap(
         {2, 2},
         storage.data(),
         2 * (int)sizeof(::image32_t));

      {

         auto map = pixmap.map();

         if (ppixmap.m_pimage32Raw != storage->data()
            || map.m_pimage32 != storage.data())
         {

            return false;

         }

      }

      return
         pixmap.m_pimage32Raw == storage.data()
         && pixmap.m_pimage32 == storage.data();

   }


} // namespace


int main()
{

   if (!padded_vertical_swap_matches<3>(
         5,
         24,
         {0x11, 0x22, 0x33},
         {0x33, 0x22, 0x11},
         {0xa1, 0xa2, 0xa3}))
   {

      return 1;

   }

   if (!padded_vertical_swap_matches<4>(
         3,
         20,
         {0x41, 0x42, 0x43, 0x44},
         {0x44, 0x43, 0x42, 0x41},
         {0xb1, 0xb2, 0xb3, 0xb4}))
   {

      return 2;

   }

   if (!malformed_overflowing_width_does_not_mutate())
   {

      return 3;

   }

   if (!mapping_external_storage_preserves_its_address())
   {

      return 4;

   }

   return 0;

}
