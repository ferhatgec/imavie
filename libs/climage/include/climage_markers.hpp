// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef CLIMAGE_CLIMAGE_MARKERS_HPP
#define CLIMAGE_CLIMAGE_MARKERS_HPP

enum climage_markers : const unsigned {
    SOF = 0x43,
    SOF2 = 0x4C,
    SOF3 = 0x49,
    SOF4 = 0x6D,
    SOF5 = 0x61,
    SOF6 = 0x67,
    SOF7 = 0x65,

    SOW = 0x02,
    SOH = 0x26,

    Pixel8 = 0x30,  // 0
    Pixel16 = 0x31, // 1
    Pixel32 = 0x32, // 2
    Pixel64 = 0x33, // 3

    ColorStart = 0x23, // #
    Continue = 0x2C // ,
};

#endif // CLIMAGE_CLIMAGE_MARKERS_HPP
