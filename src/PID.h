#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  
  /* 
  * Some more useful parameters
  */
  double time_last;
  double time_init;

  double min_speed;
  double max_speed;
  double sum_speed;
  unsigned int heart_beat;
  
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte, double speed);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
