#pragma once


namespace html
{


   enum enum_position
   {

      PositionRelative,

   };


   enum e_flag
   {
      // the width can be expanded
      FlagWidthExpandable,
      // the height can be expanded
      FlagHeightExpandable,
      // the width is fixed but can grow to make space to a single long u16
      FlagWidthFixedTable,
      // the width is fixed
      FlagWidthFixed,
      // the height is fixed
      FlagHeightFixed,
      // width in percent
      FlagWidthPercent,
      // width in pixel
      FlagWidthPixel,
      FlagWidth,
   };


   enum e_tag
   {

      tag_none,
      tag_unknown,
      tag_new,
      tag_initial,
      tag_html,
      tag_head,
      tag_title,
      tag_meta,
      tag_link,
      tag_style,
      tag_script,
      tag_body,
      tag_span,
      tag_h1,
      tag_h2,
      tag_h3,
      tag_h4,
      tag_h5,
      tag_p,
      tag_table,
      tag_tbody,
      tag_tr,
      tag_td,
      tag_div,
      tag_br,
      tag_form,
      tag_input,
      tag_select,
      tag_option,
      tag_img,
      tag_font,
      tag_li,
      tag_a,
      tag_strong,

   };


   enum edisplay
   {

      e_display_none,
      display_block,
      display_table,
      display_table_cell,
      display_table_row,
      display_inline,

   };


} // namespace html






