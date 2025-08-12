void actionA() {

  for (int i = 0; i < NUM_SENSORS; i++) {
    // --- CALIBRATION FOR NOSE ---
    if (calib_nose_times[i] != 1) {
      if (noses[i] > 50) {
        calib_noses[i]      = noses[i];
        calib_nose_times[i] = 1;
        DPRINT("calib nose  "); DPRINT(i);
        DPRINT(" : ");           DPRINTLN(calib_noses[i]);
      }
    }

    // --- CALIBRATION FOR MOUTH ---
    if (calib_mouth_times[i] != 1) {
      if (mouths[i] > 50) {
        calib_mouths[i]      = mouths[i];
        calib_mouth_times[i] = 1;
        DPRINT("calib mouth "); DPRINT(i);
        DPRINT(" : ");            DPRINTLN(calib_mouths[i]);
      }
    }

    // --- PROCESS NOSE LEVEL ---
    if (calib_nose_times[i] == 1) {
      // normalize around 500
      store_noses[i] = (int)noses[i] - (int)calib_noses[i] + 500;

      if (store_noses[i] > maxi - 1) {
        // high
        if (nose_switches[i] != 2) {
          MIDImessage(noteON,  controlA[i][0], velocity);
          MIDImessage(noteOFF, controlA[i][1], velocity);
          DPRINT("nose :"); DPRINT(i);
          DPRINTLN("  hoog");
          nose_switches[i] = 2;
        }
      }
      else if (store_noses[i] < mini + 1) {
        // low
        if (nose_switches[i] != 3) {
          MIDImessage(noteON,  controlA[i][1], velocity);
          MIDImessage(noteOFF, controlA[i][0], velocity);
          DPRINT("nose :"); DPRINT(i);
          DPRINTLN("  laag");
          nose_switches[i] = 3;
        }
      }
      else {
        // middle
        if (nose_switches[i] != 1) {
          MIDImessage(noteOFF, controlA[i][0], velocity);
          MIDImessage(noteOFF, controlA[i][1], velocity);
          DPRINT("nose :"); DPRINT(i);
          DPRINTLN("  midden");
          nose_switches[i] = 1;
        }
      }
    }

    // --- PROCESS MOUTH LEVEL ---
    if (calib_mouth_times[i] == 1) {
      store_mouths[i] = (int)mouths[i] - (int)calib_mouths[i] + 500;

      if (store_mouths[i] > maxi - 1) {
        // high
        if (mouth_switches[i] != 2) {
          MIDImessage(noteON,  controlA[i][2], velocity);
          MIDImessage(noteOFF, controlA[i][3], velocity);
          DPRINT("mouth :"); DPRINT(i);
          DPRINTLN("  hoog");
          mouth_switches[i] = 2;
        }
      }
      else if (store_mouths[i] < mini + 1) {
        // low
        if (mouth_switches[i] != 3) {
          MIDImessage(noteON,  controlA[i][3], velocity);
          MIDImessage(noteOFF, controlA[i][2], velocity);
          DPRINT("mouth :"); DPRINT(i);
          DPRINTLN("  laag");
          mouth_switches[i] = 3;
        }
      }
      else {
        // middle
        if (mouth_switches[i] != 1) {
          MIDImessage(noteOFF, controlA[i][2], velocity);
          MIDImessage(noteOFF, controlA[i][3], velocity);
          DPRINT("mouth :"); DPRINT(i);
          DPRINTLN("  midden");
          mouth_switches[i] = 1;
        }
      }
    }
  }
}

