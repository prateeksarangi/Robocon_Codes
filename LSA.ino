#include <pinmode.h>
pinmode pins;

#define incr(a, b, c) for(int a = b; a < c; a++)
#define num_sensors 7

byte S_pin[8] = {A0, A1, 4, A2, 5, A3, 6, A7}, E_pin[4] = {}, M_pin[4] = {10, 3, 12, 11}; // dirR, spR, dirL, spL
byte max_speed = 80;

int sum = 0, sum_pattern[8] = { -4, -3, -2, -1, 1, 3, 5, 7};
int pid = 0;
int spR = 0, spL = 0;

bool s[num_sensors];
bool dirR = LOW, dirL = LOW;
//bool enc_rA = LOW, enc_rB = LOW, enc_lA = LOW, enc_lB = LOW;

void setup()
{
  Serial.begin(9600);
  Serial.println(" SETUP STARTED! ");
  incr(i, 0, num_sensors)  
  {
    Serial.print(S_pin[i]); Serial.print(" ");
    pins.IN(1, S_pin[i]);
  }
  incr(i, 0, 4)
  {
    pins.IN(1, E_pin[i]);
    pins.OUT(1, M_pin[i]);
  }

  Serial.println(" SETUP COMPLETED SUCCESSFULLY! ");
}

void loop()
{
  incr(i, 0, num_sensors)
  {
    s[i] = digitalRead(S_pin[i]);
    sum += s[i] * sum_pattern[i];
  }
  S_print();
  motion(pid_calc(sum));
  sum = 0;
}

void S_print()
{
  incr(i, 0, num_sensors) Serial.print(s[i]), Serial.print("   ");

  Serial.print("\tSum = "); Serial.print(sum);

  Serial.print("\tPid = "); Serial.print(pid);
  
  Serial.print("\t"), Serial.print(dirL);
  Serial.print(" "), Serial.print(dirR);
  Serial.print("   "), Serial.print(spL);
  Serial.print(" "), Serial.print(spR);
  
  Serial.println();
}
