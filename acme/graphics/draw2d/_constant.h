#pragma once


enum enum_image_selection
{

   e_image_selection_default,
   e_image_selection_prefer_largest = e_image_selection_default,
   e_image_selection_prefer_at_least_2x_larger,
   e_image_selection_prefer_larger,
   e_image_selection_prefer_smaller,
   e_image_selection_prefer_at_least_2x_smaller,
   e_image_selection_prefer_at_least_4x_smaller,
   e_image_selection_prefer_at_least_8x_smaller,

};


enum enum_font
{

   e_font_none,

   e_font_default,

   e_font_with_family_name,

   e_font_sans,
   e_font_sans_ui,
   e_font_sans_ex,
   e_font_sans_fx,

   e_font_serif,
   e_font_serif_ui,
   e_font_serif_ex,
   e_font_serif_fx,

   e_font_monospace,
   e_font_monospace_ui,
   e_font_monospace_ex,
   e_font_monospace_fx,

};


enum enum_image
{

   e_image_none,
   e_image_grayscale,

};


enum enum_rotate_flip
{
   e_rotate_none_flip_none = 0,
   e_rotate_90_flip_none = 1,
   e_rotate_180_flip_none = 2,
   e_rotate_270_flip_none = 3,

   e_rotate_none_flip_x = 4,
   e_rotate_90_flip_x = 5,
   e_rotate_180_flip_x = 6,
   e_rotate_270_flip_x = 7,

   e_rotate_none_flip_y = e_rotate_180_flip_x,
   e_rotate_90_flip_y = e_rotate_270_flip_x,
   e_rotate_180_flip_y = e_rotate_none_flip_x,
   e_rotate_270_flip_y = e_rotate_90_flip_x,

   e_rotate_none_flip_xy = e_rotate_180_flip_none,
   e_rotate_90_flip_xy = e_rotate_270_flip_none,
   e_rotate_180_flip_xy = e_rotate_none_flip_none,
   e_rotate_270_flip_xy = e_rotate_90_flip_none
};

enum enum_stock_icon
{

   e_stock_icon_none,
   e_stock_icon_control_box_begin,
   e_stock_icon_close = e_stock_icon_control_box_begin, // button_close
   e_stock_icon_level_up, // button_up
   e_stock_icon_level_down, // button_down
   e_stock_icon_iconify, // button_minimize
   e_stock_icon_restore, // button_restore
   e_stock_icon_zoom, // button_maximize
   e_stock_icon_notify, // button_notify_icon
   e_stock_icon_transparent_frame, // button_transparent_frame
   e_stock_icon_dock, // button_dock
   e_stock_icon_control_box_end = e_stock_icon_dock

};


enum enum_plain_color
{

   e_plain_color_none,       // 0
   e_plain_color_red,        // 1
   e_plain_color_green,      // 2
   e_plain_color_blue,       // 3
   e_plain_color_yellow,     // 4
   e_plain_color_cyan,       // 5
   e_plain_color_magenta,    // 6
   e_plain_color_black,      // 7
   e_plain_color_white,      // 8
   e_plain_color_gray,       // 9

};


namespace draw2d
{

   enum enum_default_object
   {

      e_default_object = 0,

   };


   enum enum_item
   {

      e_item_none,
      e_item_line,
      e_item_rectangle,
      e_item_ellipse,
      e_item_arc,
      e_item_lines,
      e_item_polygon,
      e_item_poly_polygon,
      e_item_round_rect,
      e_item_combine,
      e_item_close_figure,
      e_item_begin_figure,
      e_item_end_figure,
      e_item_intersect_clip,

      e_item_text_out,
      e_item_draw_text,

   };


   enum enum_combine
   {

      e_combine_add,
      e_combine_exclude,
      e_combine_intersect,
      e_combine_xor,
      e_combine_copy,

   };


   enum enum_smooth_mode
   {
      e_smooth_mode_none,
      e_smooth_mode_high,
      e_smooth_mode_anti_alias_8x4,
      e_smooth_mode_anti_alias_8x8,
   };


   enum enum_interpolation_mode
   {

      e_interpolation_mode_none = 0,
      e_interpolation_mode_nearest_neighbor,
      e_interpolation_mode_low_quality,
      e_interpolation_mode_high_quality_bicubic,

   };


   enum enum_compositing_quality
   {
      e_compositing_quality_none,
      e_compositing_quality_high_speed,
      e_compositing_quality_high_quality,
   };

   enum enum_disposal
   {
      e_disposal_undefined = 0,
      e_disposal_none = 1,
      e_disposal_background = 2,
      e_disposal_previous = 3
   };


   enum enum_mipmap
   {

      e_mipmap_none,
      e_mipmap_isotropic, // 3x original size (a bit more or less if there are scan adjustments)
      e_mipmap_anisotropic, // 4x original size (a bit more or less if there are scan adjustments)

   };


   enum enum_format
   {
      e_format_none,
      e_format_png,
      e_format_bmp,
      e_format_gif,
      e_format_jpeg,
      e_format_tga,
   };


   enum enum_alpha_mode
   {

      e_alpha_mode_none,
      e_alpha_mode_set,
      e_alpha_mode_blend

   };


   enum enum_fill_mode
   {

      e_fill_mode_winding,
      e_fill_mode_alternate

   };





   enum enum_pen
   {

      e_pen_null,
      e_pen_solid,
      e_pen_dot,
      e_pen_brush,
      e_pen_dash

   };



   enum enum_brush
   {

      e_brush_null,
      e_brush_solid,
      e_brush_linear_gradient_point_color,
      e_brush_radial_gradient_color,
      e_brush_pattern,
      e_brush_box_gradient,

   };



   enum enum_line_cap
   {

      e_line_cap_flat,
      e_line_cap_round,
      e_line_cap_square,

   };


   enum enum_pen_align
   {

      e_pen_align_center,
      e_pen_align_inset,

   };


   enum enum_line_join
   {

      e_line_join_miter,
      e_line_join_bevel,
      e_line_join_round,
      e_line_join_miter_clipped

   };


} // namespace draw2d


namespace write_text
{


   enum enum_rendering
   {

      e_rendering_undefined,
      e_rendering_none,
      e_rendering_system_default,
      e_rendering_anti_alias,
      e_rendering_anti_alias_grid_fit,
      e_rendering_single_bit_per_pixel,
      e_rendering_single_bit_per_pixel_grid_fit,
      e_rendering_clear_type_grid_fit

   };


} // namespace write_text



enum enum_draw_text
{

   e_draw_text_none,
   e_draw_text_no_prefix,
   e_draw_text_word_break,
   e_draw_text_path_ellipsis,
   e_draw_text_end_ellipsis,
   e_draw_text_single_line,
   e_draw_text_expand_tabs,

};


DECLARE_ENUMERATION(e_draw_text, enum_draw_text);



