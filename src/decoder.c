

void decode(int instr){
	// Data extraction from instr received
	int highest_nibble = (instr >> 12) & 0xf;       // 0xABCD -> 0xA
	int lowest_nibble  = instr & 0xf;               // 0xABCD -> 0xD
	int high_nibble    = (instr >> 8) & 0xf;        // 0xABCD -> 0xB
	int low_byte       = instr & 0xff;              // 0xABCD -> 0xCD
	int addr           = instr & 0xfff;             // 0xABCD -> 0xCBD
	
	int raddr_1        = (instr >> 8) & 0xf;        // 0xABCD -> 0xB
	int raddr_2        = (instr >> 4) & 0xf;        // 0xABCD -> 0xC
	int data           = instr & 0xff;              // 0xABCD -> 0xCD
	
	int res;
	
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

		case 0x6:	// 6xkk
			// Set Vx = kk
			break;

		case 0x7:	// 7xkk
			// Set Vx += kk
			break;

		case 0x8:	// 8xy?
			switch (lowest_nibble) {
				case 0x0:
					// Set Vx = Vy
					break;
				case 0x1:
					// Set Vx = Vx | Vy
					break;
				case 0x2:
					// Set Vx = Vx & Vy
					break;
				case 0x3:
					// Set Vx = Vx ^ Vy
					break;
				case 0x4:
					// Set Vx = Vx + Vy, VF carry
					break;
				case 0x5:
					// Set Vx = Vx - Vy, VF not borrow
					break;
				case 0x6:
					// Shift right Vx, VF borrow
					break;
				case 0x7:
					// Set Vx = Vy - Vx, VF not borrow
					break;
				case 0xe:
					// Shict left Vx, VF borrow 
					break;

				default:
					break;
			}	
			
			break;

		case 0x9:	// 9xy0
			// Skip next instr if Vx != Vy
			break;

		case 0xA:	// Annn
			// Set value of I to nnn
			break;

		case 0xB:	// Bnnn
			// Jump location to nnn + V0
			break;

		case 0xC:	// Cxkk
			// Set Vx = rand & kk
			break;

		case 0xD: 	// Dxyn
			// Display n-byte sprite starting at mem I at (Vx, Vy), set VF = collision 
			break;

		case 0xE:	// Ex??
			switch (low_byte) {
				case 0x9e:
					// Skip next instr if KEY=Vx is pressed
					break;
				case 0xA1:
					// Skip next instr if KEY=Vx is not pressed
					break;
				default:
					break;
			}
			break;

		case 0xF:	// Fx??
			switch (low_byte) {
				case 0x07:
					// Set Vx = delay timer
					break;
				case 0x0a:
					// wait for a key press, store the value of the key in Vx
					break;
				case 0x15:
					// Set delay timer = Vx
					break;
				case 0x18:
					// Set sound timer = Vx
					break;
				case 0x1e:
					// Set I = I + Vx
					break;
				case 0x29:
					// Set I = location of sprite for digit Vx
					break;
				case 0x33:
					// Store BCD repr of Vx in I, I+1 and I+2
					break;
				case 0x55:
					// Store reg V0 through Vx in memory starting at I
					break;
				case 0x65:
					// Read reg V0 through Vx in memory starting at I
					break;
				default:
					break;
			}
			break;
		default:
			break;

	}
}
