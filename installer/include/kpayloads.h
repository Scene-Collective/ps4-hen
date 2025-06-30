#ifndef KPAYLOADS_H_
#define KPAYLOADS_H_

#include "config_struct.h"

int install_patches();
int install_payload(struct configuration *config);
int exploit_fixes();

#endif
