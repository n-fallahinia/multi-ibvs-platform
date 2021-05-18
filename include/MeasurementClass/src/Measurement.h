#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include <vector>
#include <string>
#include <fstream>
#include "kalman_filter.h"

class Measurement {
 public:
  Measurement();
  virtual ~Measurement();
  void ProcessMeasurement();
  KalmanFilter kf_;

 private:
  bool is_initialized_;
  int64_t previous_timestamp_;

  //acceleration noise components
  float noise_ax;
  float noise_ay;

};

#endif  // MEASUREMENT_H_