void parseSerialB()
{
  uint8_t length_MSB  = inDataB[0];  // typical 0x00
  uint8_t length_LSB  = inDataB[1];  // length of frame
  uint8_t frame       = inDataB[2];  // typical 0x92 data sample
  uint8_t SH1         = inDataB[3];  // typical 0x00 xbee address MSB
  uint8_t SH2         = inDataB[4];  // typical 0x13 xbee address
  uint8_t SH3         = inDataB[5];  // typical 0xA2 xbee address
  uint8_t SH4         = inDataB[6];  // typical 0x00 xbee address LSB
  uint8_t SL1         = inDataB[7];  // source xbee address MSB
  uint8_t SL2         = inDataB[8];  // source xbee address
  uint8_t SL3         = inDataB[9];  // source xbee address
  uint8_t SL4         = inDataB[10]; // source xbee address LSB
  uint8_t MY1         = inDataB[11]; // source network address MSB
  uint8_t MY2         = inDataB[12]; // source network address LSB
  uint8_t recv_opt    = inDataB[13]; // receive options
  uint8_t samples     = inDataB[14]; // samplesets - defaults always to 01
  uint8_t D_mask1     = inDataB[15]; // digital channel mask MSB
  uint8_t D_mask2     = inDataB[16]; // digital channel mask LSB
  uint8_t A_mask      = inDataB[17]; // analog channel mask
  uint8_t AD1_MSB     = inDataB[18]; // data sample MSB from AD1
  uint8_t AD1_LSB     = inDataB[19]; // data sample LSB from AD1
  uint8_t AD2_MSB     = inDataB[20]; // data sample MSB from AD2
  uint8_t AD2_LSB     = inDataB[21]; // data sample LSB from AD2
  
  // assigning sample values to corresponding sources in arrays 'noses' and 'mouths' 
  AD1 = AD1_LSB + (AD1_MSB * 256); 
  AD2 = AD2_LSB + (AD2_MSB * 256);
  /*
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
   */

   if (SL1 == 0x40 && SL2 == 0xAD && SL3 == 0xD0 && SL4 == 0x91)
    {
      noses[3] = AD1;
      mouths[3] = AD2;
    }
  if (SL1 == 0x40 && SL2 == 0xAB && SL3 == 0xB9 && SL4 == 0x48)
    {
      noses[4] = AD1;
      mouths[4] = AD2;
    }



   
  /*
  if (SL1 == 0x40 && SL2 == 0xAF && SL3 == 0x69 && SL4 == 0x11)
    {
      noses[0] = AD1;
      mouths[0] = AD2;
    }
  if (SL1 == 0x40 && SL2 == 0xAB && SL3 == 0xB9 && SL4 == 0xE2)
    {
      noses[1] = AD1;
      mouths[1] = AD2;
    }
  if (SL1 == 0x40 && SL2 == 0xAB && SL3 == 0xBA && SL4 == 0x2D)
    { 
     //Serial.println(AD1);
      noses[2] = AD1;
       //noses[7] = AD1;
      mouths[2] = AD2;
    }
    
  if (SL1 == 0x40 && SL2 == 0xAD && SL3 == 0xD0 && SL4 == 0x91)
    {
      noses[3] = AD1;
      mouths[3] = AD2;
    }
  if (SL1 == 0x40 && SL2 == 0xAB && SL3 == 0xB9 && SL4 == 0x48)
    {
      noses[4] = AD1;
      mouths[4] = AD2;
    }
   
   /*
  if (SL1 == 0x40 && SL2 == 0xAD && SL3 == 0x58 && SL4 == 0x52)
    {
      noses[10] = AD1;
      mouths[10] = AD2;
    }
  if (SL1 == 0x40 && SL2 == 0xB4 && SL3 == 0x51 && SL4 == 0x6C)
    {
      noses[11] = AD1;
      mouths[11] = AD2;
    }
  if (SL1 == 0x40 && SL2 == 0x69 && SL3 == 0x6F && SL4 == 0x04)
    {
      noses[12] = AD1;
      mouths[12] = AD2;
    }
    */
 
//#ifdef DEBUG
//#endif
}
