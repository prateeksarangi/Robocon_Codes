#include <PS4USB.h>


#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

double x, y, w = 0;
double s1, s2, s3, s4;
double lx, ly, rx, ry;

int d1 = 39, d2 = 37, d3 = 35, d4 = 31;
int m1 = 12, m2 = 11, m3 = 9, m4 = 8;

double a11 = -0.35, a12 = 0.35, a13 = 0.25;
double a21 = -0.35, a22 = -0.35, a23 = 0.25;
double a31 = 0.35, a32 = -0.35, a33 = 0.25;
double a41 = 0.35, a42 = 0.35, a43 = 0.25;

float sf = 1;

bool dir1 = LOW, dir2, dir3 = LOW , dir4 = LOW;

void setup()
{
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 USB Library Started"));
  motorSetup();
}

void motorSetup()
{
  pinMode(m1, OUTPUT); pinMode(d1, OUTPUT);
  pinMode(m2, OUTPUT); pinMode(d2, OUTPUT);
  pinMode(m3, OUTPUT); pinMode(d3, OUTPUT);
  pinMode(m4, OUTPUT); pinMode(d4, OUTPUT);
}

void loop()
{

  Usb.Task();
  PS4.setLed(Red);

  if (PS4.connected())
  {
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117)
    {
      x = -2 * (128 - PS4.getAnalogHat(LeftHatX));
      y = 2 * (PS4.getAnalogHat(LeftHatY) - 128);
      w = \
      * (PS4.getAnalogHat(RightHatX) - 128);

      if (x < 20 && x > -20)  x = 0;
      if (y < 20 && y > -20)  y = 0;
      if (w >= -10 && w <= 10)  w = 0;

      s1 =  sf * (a11 * x + a12 * y + a13 * w);
      s2 =  sf * (a21 * x + a22 * y + a23 * w);
      s3 =  sf * (a31 * x + a32 * y + a33 * w);
      s4 =  sf * (a41 * x + a42 * y + a43 * w);

//      s1 =  sf * (-0.6628433 * x - 0.0990626 * y + 0.3330024 * w);
//      s2 =  sf * (0.4263029 * x - 0.517146 * y + 0.3300284 * w);
//      s3 =  sf * (0.2365404 * x + 0.6162044 * y + 0.339504 * w);

      dir1 = s1 >= 0 ? 1 : 0;
      dir2 = s2 >= 0 ? 1 : 0;
      dir3 = s3 >= 0 ? 1 : 0;
      dir4 = s4 >= 0 ? 1 : 0;
      

       digitalWrite(d1, dir1);
      digitalWrite(d2, dir2);
      digitalWrite(d3, dir3);
      digitalWrite(d4, dir4);

      analogWrite(m1, abs(s1));
      analogWrite(m2, abs(s2));
      analogWrite(m3, abs(s3));
      analogWrite(m4, abs(s4));
    }
    else
    {
      analogWrite(m1, 0);
      analogWrite(m2, 0);
      analogWrite(m3, 0);
      analogWrite(m4, 0);
    }
  }
  if (PS4.getButtonClick(UP))
  {
    sf += 0.5;
  }

  if (PS4.getButtonClick(DOWN))
  {
    sf -= 0.5;
  }

  /*Serial.print("x= ");
  Serial.print(x);
  Serial.print("  y= ");
  Serial.print(y);
  Serial.print("  w= ");
  Serial.print(w);

  Serial.print("\t\t");
  Serial.print("S1= ");
  Serial.print(s1);
  Serial.print("  S2= ");
  Serial.print(s2);
  Serial.print("  S3= ");
  Serial.print(s3);

  Serial.print("\t\t");
  Serial.print("D1= ");
  Serial.print(dir1);
  Serial.print("  D2= ");
  Serial.print(dir2);
  Serial.print("  D3= ");
  Serial.println(dir3);*/
}
