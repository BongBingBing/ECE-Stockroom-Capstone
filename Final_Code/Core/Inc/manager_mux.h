/*
 * muxManager.h
 *
 *  Created on: Nov 18, 2024
 *      Author: andyb
 */

#include <stdbool.h>
#include "stdio.h"
#include "gpio.h"

#ifndef INC_MUXMANAGER_H_
#define INC_MUXMANAGER_H_

struct MuxCombo {
  unsigned char C;
  unsigned char B;
  unsigned char A;
};

extern const struct MuxCombo MuxCombosRows[];
extern const struct MuxCombo MuxCombosDrawers[];

void muxSET(uint16_t A, uint16_t B, uint16_t C, bool control);

#endif /* INC_MUXMANAGER_H_ */
