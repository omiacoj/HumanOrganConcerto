void parseSerialB()
{
  uint8_t length_MSB  = inDataA[0];  // typical 0x00
  uint8_t length_LSB  = inDataA[1];  // length of frame
  uint8_t frame       = inDataA[2];  // typical 0x92 data sample
  uint8_t SH1         = inDataA[3];  // typical 0x00 xbee address MSB
  uint8_t SH2         = inDataA[4];  // typical 0x13 xbee address
  uint8_t SH3         = inDataA[5];  // typical 0xA2 xbee address
  uint8_t SH4         = inDataA[6];  // typical 0x00 xbee address LSB
  uint8_t SL1         = inDataA[7];  // source xbee address MSB
  uint8_t SL2         = inDataA[8];  // source xbee address
  uint8_t SL3         = inDataA[9];  // source xbee address
  uint8_t SL4         = inDataA[10]; // source xbee address LSB
  uint8_t MY1         = inDataA[11]; // source network address MSB
  uint8_t MY2         = inDataA[12]; // source network address LSB
  uint8_t recv_opt    = inDataA[13]; // receive options
  uint8_t samples     = inDataA[14]; // samplesets - defaults always to 01
  uint8_t D_mask1     = inDataA[15]; // digital channel mask MSB
  uint8_t D_mask2     = inDataA[16]; // digital channel mask LSB
  uint8_t A_mask      = inDataA[17]; // analog channel mask
  uint8_t AD1_MSB     = inDataA[18]; // data sample MSB from AD1
  uint8_t AD1_LSB     = inDataA[19]; // data sample LSB from AD1
  uint8_t AD2_MSB     = inDataA[20]; // data sample MSB from AD2
  uint8_t AD2_LSB     = inDataA[21]; // data sample LSB from AD2
  
  // assigning sample values to corresponding sources in arrays 'noses' and 'mouths' 
  AD1 = AD1_LSB + (AD1_MSB * 256); 
  AD2 = AD2_LSB + (AD2_MSB * 256);

  if (SL1==0x42 && SL2==0x2C && SL3==0x6B && SL4==0xFB)
    {
      noses[3] = AD1;
      mouths[3] = AD2;
    }
    
   // … unpack AD1, AD2, SL1–SL4 …
  int idx = addr_to_index(SL1, SL2, SL3, SL4);
  if (idx >= 0 && idx < NUM_SENSORS) {
    noses[idx] = AD1;
    mouths[idx] = AD2;
  }
  
}
  int addr_to_index(uint8_t SL1, uint8_t SL2, uint8_t SL3, uint8_t SL4) {
  // return sensor index 0–10, or -1 if unknown
  if (SL1==0x42 && SL2==0x2C && SL3==0x6B && SL4==0xFB) return  0;  // (#11)
  if (SL1==0x42 && SL2==0x2C && SL3==0x6D && SL4==0x6A) return  1;  // (#12)
  if (SL1==0x42 && SL2==0x2C && SL3==0x6D && SL4==0x1C) return  2;  // (#13)
  if (SL1==0x42 && SL2==0x2C && SL3==0x6D && SL4==0x53) return  3;  // (#14)
  if (SL1==0x42 && SL2==0x2C && SL3==0x69 && SL4==0xEF) return  4;  // (#15)
  if (SL1==0x42 && SL2==0x2C && SL3==0x69 && SL4==0x2C) return  5;  // (#16)
  if (SL1==0x42 && SL2==0x2C && SL3==0x69 && SL4==0x12) return  6;  // (#17)
  if (SL1==0x42 && SL2==0x2C && SL3==0x6C && SL4==0x08) return  7;  // (#18)
  if (SL1==0x42 && SL2==0x2C && SL3==0x6C && SL4==0xF2) return  8;  // (#19)
  if (SL1==0x42 && SL2==0x2C && SL3==0x69 && SL4==0x1A) return  9;  // (#20)
  if (SL1==0x40 && SL2==0x86 && SL3==0xB9 && SL4==0x33) return 10;  // (#21)
  return -1;
}

 
//#ifdef DEBUG
//#endif


