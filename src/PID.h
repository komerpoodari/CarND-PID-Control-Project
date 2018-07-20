#ifndef PID_H
#define PID_H

//#define TWIDDLE

#ifdef TWIDDLE
enum Tw_state { init, 
                kp_inc, kp_dec, 
                ki_inc, ki_dec, 
                kd_inc, kd_dec};
#endif //TWIDDLE
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
  

  unsigned int heart_beat, beats_per_lap;
  
#ifdef TWIDDLE

  unsigned int this_lap;

  double d_kp, d_ki, d_kd;

  double cte_sum, cte_best;
  Tw_state last_state;
#endif  // TWIDDLE
  
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
