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


} // namespace acme


