// Copyright (c) 2009-2022 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOINLUMINARY_CLIENTVERSION_H
#define BITCOINLUMINARY_CLIENTVERSION_H

#include <util/macros.h>

#if defined(HAVE_CONFIG_H)
#include <config/bitcoinluminary-config.h>
#endif //HAVE_CONFIG_H

// Check that required client information is defined
#if !defined(CLIENT_VERSION_MAJOR) || !defined(CLIENT_VERSION_MINOR) || !defined(CLIENT_VERSION_BUILD) || !defined(CLIENT_VERSION_IS_RELEASE) || !defined(COPYRIGHT_YEAR)
#error Client version information missing: version is not defined by bitcoinluminary-config.h or in any other way
#endif

//! Copyright string used in Windows .rc files
#define COPYRIGHT_STR STRINGIZE(COPYRIGHT_YEAR) " " COPYRIGHT_HOLDERS_FINAL

/**
 * bitcoinluminaryd-res.rc includes this file, but it cannot cope with real c++ code.
 * WINDRES_PREPROC is defined to indicate that its pre-processor is running.
 * Anything other than a define should be guarded below.
 */

#if !defined(WINDRES_PREPROC)

#include <string>
#include <vector>

static const int CLIENT_VERSION =
                             10000 * CLIENT_VERSION_MAJOR
                         +     100 * CLIENT_VERSION_MINOR
                         +       1 * CLIENT_VERSION_BUILD;

extern const std::string CLIENT_NAME;


std::string FormatFullVersion();
std::string FormatSubVersion(const std::string& name, int nClientVersion, const std::vector<std::string>& comments);

std::string CopyrightHolders(const std::string& strPrefix);

/** Returns licensing information (for -version) */
std::string LicenseInfo();

#endif // WINDRES_PREPROC

#endif // BITCOINLUMINARY_CLIENTVERSION_H
