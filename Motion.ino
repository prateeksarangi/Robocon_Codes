#define dw(a, b) digitalWrite(a, b);
#define aw(a, b) analogWrite(a, b);

int pid_calc(int pv)
{
  int kp = 20, ki = 1, kd = 0.1;
  int lastError;
  int error = pv - 0;
  int I = 0, limI = 100;
  I += error;
  int D = error - lastError;
  lastError = error;

  I = I >= limI ? limI : I;
  I = I <= -limI ? -limI : I;

  pid = kp * error + ki * I + kd * D;
  return pid;
}

void motion(int pid_val)
{
  spR = max_speed + pid_val;
  spR = spR >= max_speed ? max_speed : spR;
  spR = spR <= -max_speed ? -max_speed : spR;

  spL = max_speed - pid_val;
  spL = spL >= max_speed ? max_speed : spL;
  spL = spL <= -max_speed ? -max_speed : spL;
  
  dirR = spR >= 0 ? 1 : 0;
  dirL = spL >= 0 ? 0 : 1;

  digitalWrite(10, dirR);
  digitalWrite(12, dirL);

  analogWrite(3, abs(spR));
  analogWrite(11, abs(spL));
}
