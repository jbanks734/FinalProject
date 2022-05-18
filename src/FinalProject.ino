/*
 * PIR sensor tester
 */

int inputPin = 4;   // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0;        // variable for reading the pin status

int photoresistor = A0;
int analogValue;
int i = 4;
int high = 0;
int low = 0;

void light()
{
  while (i != 0 && i != 7)
  {
    analogValue = analogRead(photoresistor);
    if (analogValue > 6)
    {
      Serial.println("IsLight");
      Serial.println(i);
      i++;
    }
    else
    {
      Serial.println("NoLight");
      Serial.println(i);
      i--;
    }
    delay(2s);
  }
}

void setup()
{
  pinMode(inputPin, INPUT); // declare sensor as input
  pinMode(photoresistor, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // Serial.println("Hello");
  val = digitalRead(inputPin); // read input value
  if (val == HIGH)
  { // check if the input is HIGH
    if (pirState == LOW)
    {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  }
  else
  {
    if (pirState == HIGH)
    {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

  light();

  Serial.println("BreakOut");

  if (i == 7)
  {
    if (high == 0)
    {
      Serial.println("Notify light on");
      Particle.publish("on", "on");
      low = 0;
      high = 1;
    }
    else
    {
      Serial.println("Already Notified light on");
    }
  }
  else
  {
    if (low == 0)
    {
      Serial.println("Notify light off");
      Particle.publish("off", "off");
      high = 0;
      low = 1;
    }
    else
    {
      Serial.println("Already Notified light off");
    }
  }

  i = 4;

  delay(2s);
}