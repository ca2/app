// Created by camilo on 2026-08-29 09:16 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "interaction.h"


namespace user
{


   interaction_metrics::interaction_metrics()
   {

      m_fLineHeight2 = 0.;

   }


   interaction_metrics::interaction_metrics(const ::f64_size & size, ::f64 fLineHeight) :
      m_sizeText(size),
      m_fLineHeight2(fLineHeight)
   {


   }


   ::f64 interaction_metrics::width() const
   {

      return m_sizeText.cx;

   }


   ::f64 interaction_metrics::height() const
   {

      return ::maximum(m_sizeText.cy, m_fLineHeight2);

   }


   ::f64 interaction_metrics::line_height() const
   {

      return ::maximum(m_sizeText.cy, m_fLineHeight2);

   }


   ::i32 interaction_metrics::i32_width() const
   {

      return (::i32) ::ceil(this->width());

   }


   ::i32 interaction_metrics::i32_height() const
   {

      return (::i32) ::ceil(this->height());

   }


   ::i32 interaction_metrics::i32_line_height() const
   {

      return (::i32) ::ceil(this->line_height());

   }


   ::i32_size interaction_metrics::i32_size() const
   {

      return { this->i32_width(), this->i32_height() };

   }


} // namespace user


