//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PCP_SITE_H
#define PCP_SITE_H

#include "pxr/usd/pcp/layerStackIdentifier.h"
#include "pxr/usd/sdf/path.h"
#include "pxr/usd/sdf/types.h"
#include "pxr/base/tf/declarePtrs.h"

#include <boost/operators.hpp>
#include <iosfwd>

TF_DECLARE_WEAK_PTRS(PcpLayerStack);
class PcpLayerStackSite;

/// A site specifies a path in a layer stack of scene description.
struct PcpSite : boost::totally_ordered<PcpSite> {
public:
    PcpLayerStackIdentifier layerStackIdentifier;
    SdfPath path;

    PcpSite();

    PcpSite( const PcpLayerStackIdentifier &, const SdfPath & path );
    PcpSite( const PcpLayerStackPtr &, const SdfPath & path );
    PcpSite( const SdfLayerHandle &, const SdfPath & path );
    explicit PcpSite( const PcpLayerStackSite & );

    bool operator==(const PcpSite &rhs) const;
    
    bool operator<(const PcpSite &rhs) const;

    struct Hash {
        size_t operator()(const PcpSite &) const;
    };
};

/// A site specifies a path in a layer stack of scene description.
struct PcpLayerStackSite : boost::totally_ordered<PcpLayerStackSite> {
public:
    PcpLayerStackPtr layerStack;
    SdfPath path;

    PcpLayerStackSite();

    PcpLayerStackSite( const PcpLayerStackPtr &, const SdfPath & path );

    bool operator==(const PcpLayerStackSite &rhs) const;
    
    bool operator<(const PcpLayerStackSite &rhs) const;

    struct Hash {
        size_t operator()(const PcpLayerStackSite &) const;
    };
};

std::ostream& operator<<(std::ostream&, const PcpSite&);
std::ostream& operator<<(std::ostream&, const PcpLayerStackSite&);

static inline
size_t
hash_value(const PcpSite& site)
{
    return PcpSite::Hash()(site);
}

static inline
size_t
hash_value(const PcpLayerStackSite& site)
{
    return PcpLayerStackSite::Hash()(site);
}

#endif
