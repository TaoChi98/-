// Copyright 2007-2010 Baptiste Lepilleur and The JsonCpp Authors
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef LICENSETOOL_INCLUDE_JSON_AUTOLINK_H
#define LICENSETOOL_INCLUDE_JSON_AUTOLINK_H

#include "config.h"

#ifdef JSON_IN_CPPTL
#include <cpptl/cpptl_autolink.h>
#endif

#if !defined(JSON_NO_AUTOLINK) && !defined(JSON_DLL_BUILD) &&                  \
    !defined(JSON_IN_CPPTL)
const std::string CPPTL_AUTOLINK_NAME = "json";
#undef CPPTL_AUTOLINK_DLL
#ifdef JSON_DLL
#define CPPTL_AUTOLINK_DLL
#endif
#include "autolink.h"
#endif

#endif // JSON_AUTOLINK_H_INCLUDED
