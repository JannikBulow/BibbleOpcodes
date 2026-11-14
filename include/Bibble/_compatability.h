// Copyright 2026 Jannik Laugmand Bülow

#ifndef BIBBLEOPCODES__COMPATABILITY_H
#define BIBBLEOPCODES__COMPATABILITY_H

#if defined(__GNUC__) || defined(__clang__)
#   define BIBBLE_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
#   define BIBBLE_UNREACHABLE() __assume(false)
#else
#   define BIBBLE_UNREACHABLE() std::abort()
#endif

#endif //BIBBLEOPCODES__COMPATABILITY_H
