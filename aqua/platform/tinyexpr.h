/*
 * TINYEXPR - Tiny recursive descent parser and evaluation engine in C
 *
 * Copyright (c) 2015-2018 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no happening will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once


//#ifdef __cplusplus
//extern "C" {
//#endif
namespace tinyexpr
{

union te_function{
   ::f64 (*m_fn0)();
   ::f64 (*m_fn1)(::f64 d);
   ::f64 (*m_fn2)(::f64 d, ::f64 d2);
   ::f64 (*m_fn3)(::f64 d, ::f64 d2, ::f64 d3);
   ::f64 (*m_fn4)(::f64 d, ::f64 d2, ::f64 d3, ::f64 d4);
   ::f64 (*m_fn5)(::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5);
   ::f64 (*m_fn6)(::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5, ::f64 d6);
   ::f64 (*m_fn7)(::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5, ::f64 d6, ::f64 d7);
   ::f64 (*m_clj0)(void *);
   ::f64 (*m_clj1)(void *, ::f64 d);
   ::f64 (*m_clj2)(void *, ::f64 d, ::f64 d2);
   ::f64 (*m_clj3)(void *, ::f64 d, ::f64 d2, ::f64 d3);
   ::f64 (*m_clj4)(void *, ::f64 d, ::f64 d2, ::f64 d3, ::f64 d4);
   ::f64 (*m_clj5)(void *, ::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5);
   ::f64 (*m_clj6)(void *, ::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5, ::f64 d6);
   ::f64 (*m_clj7)(void *, ::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5, ::f64 d6, ::f64 d7);
   te_function(nullptr_t){m_fn1= nullptr;}
   te_function(::f64 (*fn0)()):m_fn0(fn0){}
   te_function(::f64 (*fn1)(::f64 d)):m_fn1(fn1){}
   te_function(::f64 (*fn2)(::f64 d, ::f64 d2)):m_fn2(fn2){}
   te_function(::f64 (*fn3)(::f64 d, ::f64 d2, ::f64 d3)):m_fn3(fn3){}
   te_function(::f64 (*fn4)(::f64 d, ::f64 d2, ::f64 d3, ::f64 d4)):m_fn4(fn4){}
   te_function(::f64 (*fn5)(::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5)):m_fn5(fn5){}
   te_function(::f64 (*fn6)(::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5, ::f64 d6)):m_fn6(fn6){}
   te_function(::f64 (*fn7)(::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5, ::f64 d6, ::f64 d7)):m_fn7(fn7){}
   te_function(::f64 (*clj0)(void *)):m_clj0(clj0){}
   te_function(::f64 (*clj1)(void *, ::f64 d)):m_clj1(clj1){}
   te_function(::f64 (*clj2)(void *, ::f64 d, ::f64 d2)):m_clj2(clj2){}
   te_function(::f64 (*clj3)(void *, ::f64 d, ::f64 d2, ::f64 d3)):m_clj3(clj3){}
   te_function(::f64 (*clj4)(void *, ::f64 d, ::f64 d2, ::f64 d3, ::f64 d4)):m_clj4(clj4){}
   te_function(::f64 (*clj5)(void *, ::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5)):m_clj5(clj5){}
   te_function(::f64 (*clj6)(void *, ::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5, ::f64 d6)):m_clj6(clj6){}
   te_function(::f64 (*clj7)(void *, ::f64 d, ::f64 d2, ::f64 d3, ::f64 d4, ::f64 d5, ::f64 d6, ::f64 d7)):m_clj7(clj7){}
};

typedef struct te_expr {
   ::i32 type;
   union {::f64 value; const ::f64 * bound; te_function function;};
   te_expr * parameters[1];
} te_expr;


enum {
   TE_VARIABLE = 0,
   
   TE_FUNCTION0 = 8, TE_FUNCTION1, TE_FUNCTION2, TE_FUNCTION3,
   TE_FUNCTION4, TE_FUNCTION5, TE_FUNCTION6, TE_FUNCTION7,
   
   TE_CLOSURE0 = 16, TE_CLOSURE1, TE_CLOSURE2, TE_CLOSURE3,
   TE_CLOSURE4, TE_CLOSURE5, TE_CLOSURE6, TE_CLOSURE7,
   
   TE_FLAG_PURE = 32
};
union bound_or_function{
   const ::f64 * bound;
   te_function function;
   
   bound_or_function(nullptr_t){bound= nullptr;}
   bound_or_function(const ::f64 * p):bound(p){}
   bound_or_function(::f64 (*fn0)()):function(fn0){}
   bound_or_function(::f64 (*fn1)(::f64 d)):function(fn1){}
   bound_or_function(::f64 (*fn2)(::f64 d, ::f64 d2)):function(fn2){}
};

typedef struct te_variable {
   const_char_pointer pszName;
   bound_or_function address;
   ::i32 type;
   te_expr *context;
} te_variable;



/* Parses the input expression, evaluates it, and frees it. */
/* Returns NaN on error. */
::f64 CLASS_DECL_AQUA  te_interp(const_char_pointer expression, ::i32 *error);

/* Parses the input expression and binds variables. */
/* Returns NULL on error. */
CLASS_DECL_AQUA te_expr * te_compile(const_char_pointer expression, const te_variable *variables, ::i32 var_count, ::i32 *error);

/* Evaluates the expression. */
::f64 CLASS_DECL_AQUA te_eval(const te_expr *n);

/* Prints debugging information on the syntax tree. */
void CLASS_DECL_AQUA te_print(const te_expr *n);

/* Frees the expression. */
/* This is safe to call on NULL pointers. */
void CLASS_DECL_AQUA te_free(te_expr *n);

//
//#ifdef __cplusplus
//}
//#endif

} // namespace tinyexpr




