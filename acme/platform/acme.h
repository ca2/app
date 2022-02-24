//
//  base_static_start.h
//  acme
//
//
//
#pragma once



namespace acme
{


   CLASS_DECL_ACME critical_section * get_global_critical_section();
   CLASS_DECL_ACME bool should_output_debug_string();
   CLASS_DECL_ACME bool add_matter(::matter * pmatter);

#ifdef WINDOWS
   CLASS_DECL_ACME _locale_t get_c_locale();
#else
   CLASS_DECL_ACME locale_t get_c_locale();
#endif


} // namespace acme


