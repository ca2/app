#pragma once


#include "aura/graphics/image/meta.h"

#include "aura/graphics/image/drawer.h"

#include "aura/graphics/image/source.h"

#include "acme/handler/item.h"

#include "acme/graphics/image/_configuration.h"

#include "acme/prototype/prototype/memory.h"

#include <atomic>


namespace draw2d
{


   class graphics_lease;


} // namespace draw2d


#define IMAGE_IMAGE_TRANSFER(a) \
::image::image(::transfer(a)), \
::property_object(::transfer(a)), \
::image::image_drawer(::transfer(a)), \
::image::image_source_interface(::transfer(a)), \
::item(::transfer(a)), \
::matter(::transfer(a)), \
IMAGE_IMAGE_META_TRANSFER(a)


namespace image
{


   /// <summary>
   /// ::image::image *-> ::image::image_source_pointer concept
   /// </summary>
   class CLASS_DECL_AURA image :
      virtual public ::image::image_meta,
      virtual public ::property_object,
      virtual public ::image::image_drawer,
      virtual public ::image::image_source_interface,
      virtual public ::item
   {
   public:


      ::i32_rectangle                           m_rectangleTag;
      mutable ::std::atomic_bool                m_bDestinationGraphicsLeaseActive{false};
      ::pointer < ::acme::user::interaction >   m_pacmeuserinteractionAffinity;
      //::pointer < ::user::interaction >         m_puserinteraction;
      //::draw2d::graphics_lease *          m_pgraphicsleaseOwned;

      image();
      image(image&& image);
      ~image() override;


      void on_initialize_particle() override;


      //using image_meta::clear;
      //using object::clear;

      virtual void create_as_descriptor(const ::i32_size &size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG,
                          ::i32 iGoodStride = -1);

      virtual void create_bitmap(
         ::acme::user::interaction * pacmeuserinteractionAffinity = nullptr, ::draw2d::graphics * pgraphics = nullptr);


      virtual ::image::image * get_source_image();
      //   virtual void defer_update_all_frames();


      //void defer_create_owned_graphics_lease();
      //void defer_destroy_owned_graphics_lease();


      //virtual void set_owned_graphics();

      virtual ::function < void(::image::image_frame_array *) >  image_frame_array_loaded_callback();


      virtual ::pointer < ::image::load_image > create_load_image(::image::image_context* pimagecontext);

      virtual ::pointer<::image::image>get_image(const ::i32_size & size);
      virtual ::pointer<::image::image>get_image(::i32 cx, ::i32 cy);


      bool _is_set() const override;
      bool _is_ok() const override;
      inline bool is_ok() const { return ::is_set(this) && _is_ok(); }
      inline bool nok() const { return !is_ok(); }
      inline bool is_null() const { return ::is_null(this); }
      inline bool is_set() const { return !is_null() && _is_set(); }


      //virtual ::draw2d::graphics_pointer owned_graphics() const; // is semantically const (besides may not be implementationly constant)
      virtual ::draw2d::graphics_lease acquire_graphics(const ::f64_size &sizeHint);
      ::draw2d::graphics_lease acquire_graphics(
         //::draw2d::host * pdraw2dhost = nullptr,
         ::acme::user::interaction * pacmeuserinteractionAffinityExplicit = nullptr);
      ::draw2d::graphics_lease _acquire_graphics(
         //::draw2d::host * pdraw2dhost,
         ::acme::user::interaction * pacmeuserinteractionAffinity);
      bool try_begin_destination_graphics_lease() const;
      void end_destination_graphics_lease() const;
      bool has_active_destination_graphics_lease() const;
      //virtual ::draw2d::graphics * _get_graphics() const; // is semantically const (besides may not be implementationly constant)
      virtual ::draw2d::bitmap_pointer get_bitmap(::draw2d::graphics * pdraw2dgraphics = nullptr) const; // is semantically const (besides may not be implementationly constant)
      virtual ::draw2d::bitmap_pointer detach_bitmap();

      virtual void create_owned_graphics();

      virtual ::collection::count get_image_count() const;
      virtual ::image::image_pointer get_image(::collection::index i);


      virtual void set_mipmap(::image::enum_mipmap emipmap);
      virtual void _set_mipmap(::image::enum_mipmap emipmap);


      virtual void create_isotropic(::image::image *pimage);
      virtual void create_isotropic(f64_array & daRate, ::enum_priority epriority);


      virtual void set_origin(const ::i32_point & point);
      //virtual void set_alpha_mode(::draw2d::enum_alpha_mode enum_alpha_mode);

      virtual void set_size_scaler(::f64 dSizeScaler);
      
      
      virtual void create_helper_map();
      virtual void _create_helper_map();


      virtual void on_load_image();
      virtual void on_exif_orientation();
      virtual void fast_copy(::image32_t * pcolor32FullImage);


      virtual void on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan);
      virtual void on_load_image(::pixmap * ppixmap);
      virtual void on_load_image_frame_array(::image::image_frame_array * pimageframearray);

      //inline ::i32_size get_size() const;

      ::i32_size get_image_drawer_size() const override;


      ::image::image_pointer image_source_image(const ::i32_size &) override;


      // inline concrete < ::i32_size > i32_size(const ::f64_size &, const ::f64_size &, enum_image_selection) const { return get_size(); }
      ::i32_size image_source_size(const ::f64_size &, enum_image_selection) const override;
      ::i32_size image_source_size() const override;
      //using image_meta::size;

      //inline ::i32_rectangle rectangle(const ::i32_point & point = {});
      //inline ::i32_rectangle rectangle(const ::i32_point & point = {}) const;


      //inline ::u64 area() const;
      //inline ::i32 width() const;
      //inline ::i32 height() const;


      //inline ::i32 scan_size() const;

      virtual void create_frame(::image::image_frame * pframeSource, ::image::image_frame_array * pframea);
      //virtual void create_frame(::image::image_frame * pframe, ::image::image_frame * pframeSource, const ::image::image_drawing & imagedrawing, ::image::image_frame_array * pframea);
      //void create_frame(::image::image_frame * pframeSource, const ::pixmap * ppixmap, ::image::image_frame_array * pframea)
      virtual ::image::image_pointer frame_image(::image::image_frame * pframe);
      virtual ::image::image_pointer calc_current_frame(image_dynamic & dynamic);
      virtual void update(::image::image *pimageHost, ::image::image_frame_array * pframea, const ::image::image_drawing & imagedrawing);



      // virtual void rate_rgb(::i32 iMul, ::i32 iDiv);
      // virtual void dc_select(bool bSelect = true);
      //
      // virtual ::color::color GetAverageColor();
      // virtual ::color::color GetAverageOpaqueColor();
      // virtual void blend(::image::image *pimage, ::image::image *imageRate);
      // virtual void Blend(::image::image *pimage, ::image::image *imageA, ::i32 A);
      // virtual void Blend(::image::image *pimage, ::image::image *imageA);
      // virtual void blend(const ::i32_point & pointDst, ::image::image *imageSrc, const ::i32_point & pointSrc, ::image::image *imageAlf, const ::i32_point & pointDstAlf, const ::i32_size & size);
      // virtual void precision_blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size);
      // virtual void precision_blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
      // virtual void blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size);
      // virtual void blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
      // virtual void blend2(const ::i32_point & pointDst, ::image::image *imageSrc, const ::i32_point & pointSrc, const ::i32_size & size, ::u8 bA);
      // virtual void fork_blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size);
      // virtual void fork_blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
      // //virtual void bitmap_blend(::draw2d::graphics* pgraphics, const ::i32_rectangle & rectangle);
      //
      // virtual void color_blend(::color::color color, ::u8 bAlpha);
      // virtual void BitBlt(::image::image *pimage, ::i32 op);
      // virtual void BitBlt(::i32 cxParam, ::i32 cyParam, ::image::image *pimage, ::i32 op);
      //virtual ::i32 cos(::i32 i, ::i32 iAngle);
      //virtual ::i32 sin(::i32 i, ::i32 iAngle);
      //virtual ::i32 cos10(::i32 i, ::i32 iAngle);
      //virtual ::i32 sin10(::i32 i, ::i32 iAngle);

      virtual void hue_offset(::f64 dRate);

      //::pixmap_lease map(bool bApplyAlphaTransform = true) const override; // some implementations may requrire to map_base to m_pcolorref before manipulate it
      //void unmap() const override; // some implementations may require to unmap from m_pcolorref to update *os* bitmap

      virtual void _draw_raw(const ::i32_rectangle& rectangleDstParam, ::image::image* pimageSrc, const ::i32_point& pointSrcParam);

      virtual void blend(const ::i32_rectangle& rectangleDstParam, ::image::image* pimageSrc, const ::i32_point& pointSrcParam, ::u8 bA);
      //virtual void blend2(const ::i32_point& pointDstParam, ::image::image* pimageSrc, const ::i32_point& pointSrcParam, const ::i32_size& sizeParam, ::u8 bA);

      virtual void set_mapped();


      virtual void create_thumbnail(const ::scoped_string & scopedstrPath);

      //virtual void create_from_data(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false);
      virtual void create_from_data(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan,
                                    ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, 
                                    bool bPreserve = false);
      virtual void create_from_graphics(::draw2d::graphics* pgraphics);
      virtual void create_as_top_draw2d_target(const ::i32_size & size, ::user::interaction * puserinteraction, ::draw2d::graphics * pdraw2dgraphics, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false);
      virtual void create_as_render_target(const ::i32_size & size, ::user::interaction * puserinteraction, ::draw2d::graphics * pdraw2dgraphicsOwning = nullptr, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false, bool bTopDraw2dTarget = false);
      using ::particle::initialize;
      //virtual void initialize(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG);
      virtual void preserve(const ::i32_size &size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG);
      //virtual void     create(::i32 iWidth, ::i32 iHeight, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, ::i32 iGoodStride = -1, void bPreserve = false);


      //virtual bool host(::pixmap_t * ppixmap, ::windowing::window * pwindow);
      virtual bool host(::windowing::window_buffer * pwindowbuffer, ::windowing::window *pwindow, const ::i32_size & sizeRaw);
      virtual bool on_host_read_pixels(::pixmap_t * ppixmapHost) const;
      void destroy() override;
      void destroy_os_data() override;
      //virtual void detach(::image::image *pimage);

      // realization is semantically const
      // image keeps an image and image will be the same,
      // besides the way the Device Context associated with the image (m_spgraphics)
      // interprets or deals with it, may machine
      virtual void realize(::draw2d::graphics* pgraphics) const;
      virtual void unrealize() const;
      virtual bool is_realized() const;
      virtual void defer_realize(::draw2d::graphics* pgraphics) const;



      //using image_drawer::stretch;
      virtual void stretch_image(::image::image *pimage, ::draw2d::enum_interpolation_mode einterpolationmode = draw2d::e_interpolation_mode_none);


      //virtual void stretch(::draw2d::graphics * pgraphics);
      //virtual void to(::image::image *piml) const;
      //virtual void copy(const ::image::image *pimage, enum_flag eflagCreate = e_flag_success);
      //virtual void stretch(const ::image::image *pimage);
      //virtual void draw_image(::draw2d::graphics* pgraphics);
      //virtual void draw_image(::draw2d::graphics* pgraphics, const ::i32_size & size);
      //virtual void from(const ::i32_point & pointDst, ::draw2d::graphics* pgraphics, const ::i32_point & pointSrc, const ::i32_size & size);
      //using image_drawer::draw;
      // virtual void _draw_raw(const ::i32_rectangle & rectangleTarget, ::image::image *pimage, const ::i32_point & pointSrc = ::i32_point());
      // virtual void blend(const ::i32_rectangle & rectangleTarget, ::image::image *pimage, const ::i32_point & pointSrc, ::u8 bA);
      // //virtual void blend(const ::i32_point & pointDst, ::image::image *piml, const ::i32_point & pointSrc, const ::i32_size & size);
      // virtual void draw_ignore_alpha(const ::i32_point & pointDst, ::image::image *pimage, const ::i32_rectangle & rectangleSource);

      //virtual void to(::draw2d::graphics* pgraphics);
      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_point & point);
      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_size & size);
      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_point & point, const ::i32_size & size);
      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_rectangle & rectangle);

      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_point & point, const ::i32_size & size, const ::i32_point & pointSrc);

      

      //virtual void     create_image(::i32 cx, ::i32 cy, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, ::i32 iGoodStride = -1);
      //virtual void     create_image(const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, ::i32 iGoodStride = -1);





      //::f64 pi() const;

      //static void static_initialize();




      //::stream & write(::stream & stream) const override;
      //::stream & read(::stream & stream) override;


      //::subparticle_pointer clone() override;


      //inline ::i32 line(::i32 line);


      //virtual ::draw2d::graphics * owned_graphics() const;
      //virtual ::draw2d::graphics * owned_graphics(const ::f64_size &sizeHint);
      inline ::f64_size origin() const { return ::f64_size(); }

      //inline ::color::color pixel(::i32 x, ::i32 y) const;


      //inline void is_set() const;


      //inline void is_null() const;


      //inline void is_empty() const;


      //inline ::image32_t * get_data();


      //inline const ::image32_t * get_data() const;


      //inline ::image32_t * image32();


      //inline const ::image32_t* image32() const;


      //inline operator ::image32_t* ();


      //inline operator const ::image32_t* () const;


      //inline ::pixmap * pixmap();


      //inline const ::pixmap * pixmap() const;


      //inline operator ::pixmap *();


      //inline operator const ::pixmap *() const;


      //::image_extension * extension();


      ::image::image_extension * get_extension();


      //inline const ::image_extension * extension() const;


      //inline operator ::image_extension * ();


      //inline operator const ::image_extension * () const;




      //inline ::draw2d::graphics* g() const
      //{

        // return get_graphics2();

      //}



      inline ::image::image_extension * extension()
      {

         return m_pextension;

      }


      inline const ::image::image_extension * extension() const
      {

         return m_pextension;

      }


      inline operator image_extension* ()
      {

         return m_pextension;

      }


      inline operator const image_extension* () const
      {

         return m_pextension;

      }


      //virtual ::image::image_extension * get_extension();


      //inline ::image32_t * data()
      //{

      //   return m_pimage32;

      //}

      //::image32_t * line_data(::i32 iLine);

      //inline ::image32_t * begin()
      //{

      //   return this->data();

      //}

      //inline const ::image32_t * data() const
      //{

      //   return m_pimage32;

      //}


      //inline const ::image32_t * begin() const
      //{

      //   return this->data();

      //}

      //virtual const ::image32_t *get_data() const;

      //virtual ::image32_t *get_data();
         
      //inline ::image::image & operator = (const ::image::image & image);
      //inline void operator == (const ::image::image & image) const;
      //inline void operator != (const ::image::image & image) const;

      void draw(const ::image::image_drawing & imagedrawing) override;
      bool _draw_blend(const ::image::image_drawing & imagedrawing) override;
      void _draw_raw(const ::image::image_drawing & imagedrawing) override;


      virtual void copy_from_no_create(::pixmap * ppixmap, const ::i32_point & point);
      virtual void copy_from_no_create(::pixmap * ppixmap);
      virtual void copy_from(::pixmap * ppixmap, const ::i32_point & point, enum_flag eflagCreate = e_flag_success);
      virtual void copy_from(::pixmap * ppixmap, enum_flag eflagCreate);
      virtual void copy_from(::image::image * pimage);

      //
      // inline image& operator = (const image& image)
      // {
      //
      //    copy_from((::image::image*) & image);
      //
      //    return *this;
      //
      // }


      //inline ::image::image *image::frame(iptr i) const
      //{
      //
      //   auto frames = this->frames();
      //
      //   if (::is_null(frames) || frames->is_empty())
      //   {
      //
      //      if (i == 0)
      //      {
      //
      //         return m_pimpl;
      //
      //      }
      //
      //      return nullptr;
      //
      //   }
      //
      //   auto pointer = frames->ptr_at(i);
      //
      //   return ::is_null(pointer) ? nullptr : pointer->m_pimpl;
      //
      //}
      //

      inline bool operator == (const image& image) const
      {

         return m_ppixmapOwned && image.m_ppixmapOwned && m_ppixmapOwned->m_pimage32Raw == image.m_ppixmapOwned->m_pimage32Raw;

      }
      virtual void SetIconMask(::image::icon * picon, ::i32 cx, ::i32 cy);

      // inline bool operator != (const image& image) const
      // {
      //
      //    return !operator ==(image);
      //
      // }



      //inline ::i32_size image::size() const
      //{
      //
      //   return m_size;
      //
      //}


      inline ::i32_rectangle rectangle(const ::i32_point & point = {})
      {

         return ::i32_rectangle(point, get_size() - point);

      }


      inline ::i32_rectangle rectangle(const ::i32_point & point = {}) const
      {

         return ::i32_rectangle(point, get_size() - point);

      }



      inline ::i32_size get_size() const { return size(); }

      virtual ::image::image_pointer get_resized_image(const ::i32_size & size);

      virtual ::pixmap_lease map(const ::i32_rectangle & rectangle ={}, bool bApplyAlphaTransform = true);

      protected:


         virtual ::pixmap_lease _map(const ::i32_rectangle & rectangle, bool bApplyAlphaTransform = true);
         virtual void _unmap(bool bDoUnmap = false);



   };


} // namespace image

////
////
//// Compose, Construct, Create and Add_Reference Porngraphs
////
//// createø      // return ::pointer<BASE_TYPE>// _id atom // _new TYPE
//// constructø     // ::pointer<BASE_TYPE>&    // _id atom // _new TYPE // SOURCE psource
//// constructø   // ::pointer<BASE_TYPE>&      // _id atom // _new TYPE // SOURCE psource
//// add_reference // ::pointer<BASE_TYPE>& SOURCE psource
////
//// >>
////
////
//
//
//inline ::image::image_pointer __create_image()
//{
//
//   return ::createø<::image::image>();
//
//}
//
//// template < typename COMPOSER >
//// void constructø(COMPOSER && pcomposer, __ & pimage);
// //
// template < typename COMPOSER >
// inline void constructø(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, ::image::image *pimageSource);
// //
// //
// template < typename COMPOSER >
// inline void constructø(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::i32_size & size, ::enum_flag eflagCreate = OK, ::i32 iGoodStride = -1, void bPreserve = false);
// //
// //
// template < typename COMPOSER >
// inline void __preserve(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::i32_size & size, ::enum_flag eflagCreate = OK, ::i32 iGoodStride = -1);
// //
//
//void constructø(::image::image_pointer & pimage);

inline void __call__construct(::image::image_pointer & pimage, ::image::image *pimageSource);
//
//
inline void __call__construct(::image::image_pointer & pimage, const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false);
//
//
inline void __preserve(::image::image_pointer & pimage, const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1);
//
//
//


//template < >
//inline bool is_ok(const ::image::image *pimage)
//{
//
//   if (::is_null(pimage))
//   {
//
//      return false;
//
//   }
//
//   return pimage->is_ok();
//
//}
//
//
//template < typename TYPE >
//inline bool not_ok(const TYPE * p) { return is_null(p); }


//inline bool not_ok(const ::image::image *pimage)
//{
//
//   return !is_ok(pimage);
//
//}


#include "_image_impl.h"



