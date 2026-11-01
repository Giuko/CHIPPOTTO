

void decode(int instr){
	// Data extraction from instr received
	int highest_nibble = (instr >> 12) & 0xf;       // 0xABCD -> 0xA
	int high_nibble    = (instr >> 8) & 0xf;        // 0xABCD -> 0xB
	int low_byte       = instr & 0xff;              // 0xABCD -> 0xCD
	int addr           = instr & 0xfff;             // 0xABCD -> 0xCBD
	
	int raddr_1        = (instr >> 8) & 0xf;        // 0xABCD -> 0xB
	int raddr_2        = (instr >> 4) & 0xf;        // 0xABCD -> 0xC
	
	switch (highest_nibble) {
		case 0x0:
			if(low_byte == 0xE0){
				// CLS

			}else if(low_byte == 0xEE){
				// RET

			}
			break;

		case 0x1:	// 1nnn
			// JP addr
			break;

		case 0x2:	// 2nnn
			// CALL addr
			break;

		case 0x3:	// 3xkk
			// Skip next instr if Vx == kk
			break;

		case 0x4:	// 4xkk
			// Skip next instr if Vx != kk
			break;

		case 0x5:	// 5xy0
			// Skip next instr if Vx == Vy
			break;

		case 0x6:
			break;
		case 0x7:
			break;

		case 0x8:
			break;

		case 0x9:
			break;

		case 0xA:
			break;

		case 0xB:
			break;

		case 0xC:
			break;

		case 0xD:
			break;

		case 0xE:
			break;

		case 0xF:
			break;

	}
}
