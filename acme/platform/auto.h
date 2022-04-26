#pragma once

// arthur o'dwyer and stefanus du toit => AUTO Macro -> also may be a good idea to use proper case for template typename parameters
// for not to be confused with MACROs
// https://github.com/CppCon/CppCon2014/blob/master/Presentations/C%2B%2B11%20in%20the%20Wild%20-%20Techniques%20from%20a%20Real%20Codebase/auto.h

template < class Lambda > class at_scope_exit
{

   Lambda & m_lambdaAtScopeExit;

public:

   at_scope_exit(Lambda & action_at_scope_exit): m_lambdaAtScopeExit(action_at_scope_exit)
   {
   }
   ~at_scope_exit()
   {
      m_lambdaAtScopeExit();
   }
};

#define TOKEN_CONCAT_PHASE1(x, y) x ## y

#define TOKEN_CONCATENATE(x, y) TOKEN_CONCAT_PHASE1(x, y)

#define AUTO_INTERNAL1(lambda_function_name, at_scope_exit_var_name, ...)                                                                                                     \
                                                                                                                                                                              \
auto lambda_function_name = [&]() { __VA_ARGS__; };                                                                                                                           \
                                                                                                                                                                              \
at_scope_exit < decltype(lambda_function_name) > at_scope_exit_var_name(lambda_function_name);


#define AUTO_INTERNAL2(counter, ...) AUTO_INTERNAL1(TOKEN_CONCATENATE(auto_lambda_function_, counter), TOKEN_CONCATENATE(auto_lambda_instance_, counter), __VA_ARGS__)


// put a function/member call even with args... this will be called on exit, regardless premature returns/exceptions
// e.g.: AUTO(m_readdb.reopen(this, m_strPath, false, false));
#define AUTO(...) AUTO_INTERNAL2(__COUNTER__, __VA_ARGS__) // at_scope_exit instantiator




