void actionA()
{
  for (int i = 0; i < 4; i++)
  {

//Serial.println(calib_nose_times[7]);
//noses
     if ( calib_nose_times[i] != 1 ) {
      //Serial.print("check if serial 3 is available  ");
     
     if ( i < 3 ) {
     if (Serial3.available()) {

        //Serial.print("    Serial 3 available");
      //if ( calib_noses[7] == 0 )
         { if ( noses[i] > 50 ) { 
          //delay(100);
          calib_noses[i] = noses[i]; 
          //print noses
          
          Serial.print("calib nose  ");
          Serial.println(i);
          Serial.print(" : ");
          Serial.println(calib_noses[i]);
          Serial.print("    ");
          
          calib_nose_times[i] = 1;
           
         } 
        }
    }
     }
     
     
     if ( i > 2 ) {
     {
       if (Serial2.available()) {

        //Serial.print("    Serial 3 available");
      //if ( calib_noses[7] == 0 )
         { if ( noses[i] > 50 ) { 
          //delay(100);
          calib_noses[i] = noses[i]; 
          //print noses
          
          Serial.print("calib nose  ");
          Serial.println(i);
          Serial.print(" : ");
          Serial.println(calib_noses[i]);
          Serial.print("    ");
          
          calib_nose_times[i] = 1;
           
         } 
        }
    }

      

      
     }
     }


     
     }
     

if ( calib_nose_times[i] == 1 ) {
store_noses[i] = (noses[i] - calib_noses[i])+500;

//Serial.println(store_noses[i]);

if ( store_noses[i] < maxi && store_noses[i] > mini )
   {
    if ( nose_switches[i] != 1 ) {

    
     
     if ( scramble_check[i][0] == 1 ) { 
     //Serial.println(store_noses[i]);
     MIDImessage(noteOFF, controlA[i][0], velocity);
     //digitalWrite(controlA[i][0],HIGH);
     scramble_check[i][0] = 0;
     }

     if ( scramble_check[i][1] == 1 ) { 
     MIDImessage(noteOFF, controlA[i][1], velocity);
     //digitalWrite(controlA[i][1],HIGH);
     scramble_check[i][1] = 0;
     }
     
     //digitalWrite(10,LOW);
     //Serial.print("up");
    Serial.print(" nose :");
     Serial.println(i);
    Serial.print("  midden");
    nose_switches[i] = 1;
    }
     
   }
   else
   {

   
      if ( store_noses[i] > (maxi-1) ) {

    if ( nose_switches[i] != 2 ) {

      if ( scramble_check[i][0] == 0 ) { 
      MIDImessage(noteON, controlA[i][0], velocity);
      //digitalWrite(controlA[i][0],LOW);
      scramble_check[i][0] = 1;
      }

      if ( scramble_check[i][1] == 1 ) { 
      MIDImessage(noteOFF, controlA[i][1], velocity);
      //digitalWrite(controlA[i][1],HIGH);
      scramble_check[i][1] = 0;
      }
       
     //digitalWrite(10,HIGH); 
    Serial.print(" nose :");
     Serial.println(i);
    Serial.print("  hoog");
    nose_switches[i] = 2;
    }
     }

     //zuigen
     if ( store_noses[i] < (mini+1) ) {

    if ( nose_switches[i] != 3 ) {


    if ( scramble_check[i][1] == 0 ) {
    MIDImessage(noteON, controlA[i][1], velocity);
    //digitalWrite(controlA[i][1],LOW);
    scramble_check[i][1] = 1;
    }

    if ( scramble_check[i][0] == 1 ) { 
    MIDImessage(noteOFF, controlA[i][1], velocity);
    //digitalWrite(controlA[i][0],HIGH);
    scramble_check[i][0] = 0;
    }
     
     Serial.print(" nose :");
     Serial.println(i);
    Serial.print("  laag");
     //digitalWrite(10,HIGH); 
    nose_switches[i] = 3;
    }
     
     }
    }   
 } 
 
  //mouth
      if ( calib_mouth_times[i] != 1 ) {
        
        
         
       if ( i < 3 ) {
     if (Serial3.available()) {

    
      //if ( calib_noses[7] == 0 )
         { if ( mouths[i] > 50 ) { 
          //delay(100);
          calib_mouths[i] = mouths[i];
          //print mouths
          
          Serial.print("calib mouth  ");
          Serial.println(i);
          Serial.print(" : ");
          Serial.println(calib_mouths[i]);
          Serial.print("    ");
          
          calib_mouth_times[i] = 1;
           
         } 
        }
    }
       }
       
       
       if ( i > 2 )
       {
          if (Serial2.available()) {

    
      //if ( calib_noses[7] == 0 )
         { if ( mouths[i] > 50 ) { 
          //delay(100);
          calib_mouths[i] = mouths[i];
          //print mouths
          
          Serial.print("calib mouth  ");
          Serial.println(i);
          Serial.print(" : ");
          Serial.println(calib_mouths[i]);
          Serial.print("    ");
          
          calib_mouth_times[i] = 1;
           
         } 
        }
    }
        
       }

       
     }

if ( calib_mouth_times[i] == 1 ) {
store_mouths[i] = (mouths[i] - calib_mouths[i])+500;

//Serial.println(store_mouths[i]);

if ( store_mouths[i] < maxi && store_mouths[i] > mini)
   {

    if ( mouth_switches[i] != 1 ) {

     if ( scramble_check[i][2] == 1 ) {
     MIDImessage(noteOFF, controlA[i][2], velocity);
     //digitalWrite(controlA[i][2],HIGH);
     scramble_check[i][2] = 0;
     }
     if ( scramble_check[i][3] == 1 ) {
     MIDImessage(noteOFF, controlA[i][3], velocity);
     //digitalWrite(controlA[i][3],HIGH);
     scramble_check[i][3] = 0;
     }
     
     Serial.print(" mouth :");
     Serial.println(i);
    Serial.print("  midden");
     //digitalWrite(10,LOW);
     //Serial.print("up");
    mouth_switches[i] = 1;
    }
   }
else
   {

   
      if ( store_mouths[i] > (maxi-1) ) {

      if ( mouth_switches[i] != 2 ) {

      if ( scramble_check[i][2] == 0 ) {
      MIDImessage(noteON, controlA[i][2], velocity);
      //digitalWrite(controlA[i][2],LOW);
      scramble_check[i][2] = 1;
      }
      
      if ( scramble_check[i][3] == 1 ) {
      MIDImessage(noteOFF, controlA[i][3], velocity);
      //digitalWrite(controlA[i][3],HIGH);
      scramble_check[i][3] = 0;
      }

      Serial.print(" mouth :");
     Serial.println(i);
    Serial.print("  hoog");
     //digitalWrite(10,HIGH); 
      mouth_switches[i] = 2;
      }
     }

     //zuigen
     if ( store_mouths[i] < (mini+1) ) {
      if ( mouth_switches[i] != 3 ) {

     if ( scramble_check[i][2] == 1 ) {
     MIDImessage(noteOFF, controlA[i][2], velocity);
     //digitalWrite(controlA[i][2],HIGH);
     scramble_check[i][2] = 0;
     }
     
     if ( scramble_check[i][3] == 0 ) {
      MIDImessage(noteON, controlA[i][3], velocity);
      //digitalWrite(controlA[i][3],LOW);
      scramble_check[i][3] = 1;
     }
      
      Serial.print(" mouth :");
     Serial.println(i);
    Serial.print("  laag");
     
     //digitalWrite(10,HIGH); 
      mouth_switches[i] = 3;
      }
     }
    }   
 } 


 }
}
