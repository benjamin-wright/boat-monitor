#ifndef UTILS_PINS_H
#define UTILS_PINS_H

struct PinInputs {
  float battery;
  float bilge;
};

class pins {
  public:
    static void init();
    static PinInputs read();
    static void resetCameras();
    static bool isResetting();
    static void tick();
};

#endif