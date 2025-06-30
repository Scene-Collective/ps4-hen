#include <stddef.h>
#include <stdint.h>

#include "offsets.h"
#include "sections.h"

// clang-format off

// #include "offsets/474.h"
// #include "offsets/500.h"
// #include "offsets/501.h"
// #include "offsets/503.h"
#include "offsets/505.h"
// #include "offsets/507.h"
// #include "offsets/550.h"
// #include "offsets/553.h"
// #include "offsets/555.h"
// #include "offsets/556.h"
// #include "offsets/600.h"
// #include "offsets/602.h"
// #include "offsets/620.h"
// #include "offsets/650.h"
// #include "offsets/651.h"
// #include "offsets/670.h"
// #include "offsets/671.h"
#include "offsets/1000.h"
#include "offsets/1001.h"
#include "offsets/1050.h"
#include "offsets/1070.h"
#include "offsets/1071.h"
#include "offsets/1100.h"
#include "offsets/1102.h"
#include "offsets/1150.h"
#include "offsets/1152.h"
#include "offsets/1200.h"
#include "offsets/1202.h"
#include "offsets/672.h"
#include "offsets/700.h"
#include "offsets/701.h"
#include "offsets/702.h"
#include "offsets/750.h"
#include "offsets/751.h"
#include "offsets/755.h"
#include "offsets/800.h"
#include "offsets/801.h"
#include "offsets/803.h"
#include "offsets/850.h"
#include "offsets/852.h"
#include "offsets/900.h"
#include "offsets/903.h"
#include "offsets/904.h"
#include "offsets/950.h"
#include "offsets/951.h"
#include "offsets/960.h"
// #include "offsets/1250.h"

// clang-format on

PAYLOAD_CODE const struct kpayload_offsets *get_offsets_for_fw(uint16_t fw_version) {
  switch (fw_version) {
  case 505:
    return &offsets_505;
  case 672:
    return &offsets_672;
  case 700:
    return &offsets_700;
  case 701:
    return &offsets_701;
  case 702:
    return &offsets_702;
  case 750:
    return &offsets_750;
  case 751:
    return &offsets_751;
  case 755:
    return &offsets_755;
  case 800:
    return &offsets_800;
  case 801:
    return &offsets_801;
  case 803:
    return &offsets_803;
  case 850:
    return &offsets_850;
  case 852:
    return &offsets_852;
  case 900:
    return &offsets_900;
  case 903:
    return &offsets_903;
  case 904:
    return &offsets_904;
  case 950:
    return &offsets_950;
  case 951:
    return &offsets_951;
  case 960:
    return &offsets_960;
  case 1000:
    return &offsets_1000;
  case 1001:
    return &offsets_1001;
  case 1050:
    return &offsets_1050;
  case 1070:
    return &offsets_1070;
  case 1071:
    return &offsets_1071;
  case 1100:
    return &offsets_1100;
  case 1102:
    return &offsets_1102;
  case 1150:
    return &offsets_1150;
  case 1152:
    return &offsets_1152;
  case 1200:
    return &offsets_1200;
  case 1202:
    return &offsets_1202;
  default:
    return NULL;
  }
}
