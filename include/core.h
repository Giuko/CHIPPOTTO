// core.h
#ifndef __CORE_H
#define __CORE_H

#include "chippotto.h"

int fetch(chippotto *machine);
int decode_and_execute(chippotto *machine);
void step(chippotto *machine);

#endif
