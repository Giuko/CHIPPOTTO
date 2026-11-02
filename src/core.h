#ifndef __CORE_H
#define __CORE_H

#include "chippotto.h"

int fetch(chippotto *machine, int *instr);
int decode_and_execute(chippotto *machine, int instr);
void step(chippotto *machine);

#endif
