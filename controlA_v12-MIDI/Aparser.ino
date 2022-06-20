void parseSerialA()
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

    if (SL1 == 0x40 && SL2 == 0xB4 && SL3 == 0x51 && SL4 == 0x83)
    { 
      
      noses[0] = AD1;
      mouths[0] = AD2;
    }
  if (SL1 == 0x40 && SL2 == 0xAB && SL3 == 0xB7 && SL4 == 0xA4)
    {
      noses[1] = AD1;
      mouths[1] = AD2;
    }
 if (SL1 == 0x40 && SL2 == 0xC8 && SL3 == 0xB4 && SL4 == 0x77)
    {
      noses[2] = AD1;
      mouths[2] = AD2;
    }
 
    
 
//#ifdef DEBUG
//#endif
}
