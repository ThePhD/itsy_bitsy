// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef ITSY_BITSY_DETAIL_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED
