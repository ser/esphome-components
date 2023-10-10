#include "esphome.h"
#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>

class SeeedGasSensor2 : public PollingComponent {
  public:
    GAS_GMXXX<TwoWire> gas;
    Sensor *GM102BSensor = new Sensor();
    Sensor *GM302BSensor = new Sensor();
    Sensor *GM502BSensor = new Sensor();
    Sensor *GM702BSensor = new Sensor();

    SeeedGasSensor2() : PollingComponent(2000) { }

    void setup() override {
      gas.begin(Wire, 0x08);
    }
    void update() override {
      uint32_t GM102B = gas.measure_NO2();
      GM102BSensor->publish_state(gas.calcVol(GM102B));

      uint32_t GM302B = gas.measure_C2H5OH();
      GM302BSensor->publish_state(gas.calcVol(GM302B));

      uint32_t GM502B = gas.measure_VOC();
      GM502BSensor->publish_state(gas.calcVol(GM502B));

      uint32_t GM702B = gas.measure_CO();
      GM702BSensor->publish_state(gas.calcVol(GM702B));
    }
  };
