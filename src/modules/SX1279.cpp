#include "SX1279.h"

SX1279::SX1279(Module* mod) : SX1278(mod) {
  
}

uint8_t SX1279::setFrequency(float freq) {
  // check frequency range
  if((freq < 137.0) || (freq > 960.0)) {
    return(ERR_INVALID_FREQUENCY);
  }
  
  // set frequency
  return(SX1278::setFrequencyRaw(freq));
}
