
/*
LilyPad Temperature Sensor Example
SparkFun Electronics
https://www.sparkfun.com/products/8777

This code reads the input of the temperature sensor, converts it to Farenheit and Celsius
and prints to the Serial Monitor.

Temperature sensor connections:
   * S tab to A3
   * + tab to A5 (or +)
   * - tab to -

Follow the tutorial at:
https://learn.sparkfun.com/tutorials/lilypad-temperature-sensor-hookup-guide

This code is released under the MIT License (http://opensource.org/licenses/MIT)
******************************************************************************/

// Connect the S tab of the Temperature Sensor to A3
// If using the LilyPad ProtoSnap Plus, change to A9
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0; 
int PulseSensorPurplePin = 2;  //heart pin
int sensorPin = A3;  
int LED13 = 13; 
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024


void setup()
{
  // Set the temperature sensor pin as an INPUT:
  pinMode(sensorPin, INPUT);
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
  // Set pin A5 to use as a power pin for the light sensor
  // If using the LilyPad Development Board or the + tab for power, comment out these lines of code
  //pinMode(A5, OUTPUT);
  //digitalWrite(A5, HIGH);

  // Initialize Serial, set the baud rate to 9600 bps.
  Serial.begin(9600);
    // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop()
{
  int i;
  // Variable to store raw temperature
  long rawTemp;

  // Variable to store voltage calculation
  float voltage;

  // Variable to store Fahrenheit value
  float fahrenheit;

  // Variable to store Celsius value
  float celsius;

  // Read the raw 0-1023 value of temperature into a variable.
  rawTemp = analogRead(sensorPin);

    // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(sensorPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.print("Runing Avg: ");
  Serial.println(average);
  delay(1); 

  // Calculate the voltage, based on that value.
  // Multiply by maximum voltage (3.3V) and divide by maximum ADC value (1023).
  // If you plan on using this with a LilyPad Simple Arduino on USB power, change to 4.2. Ideal is 3.3
  voltage = average * (3.3 / 1023.0);
  Serial.print("Raw: ");
  Serial.println(rawTemp);
  Serial.print("Voltage: "); // Print voltage reading to serial monitor
  Serial.println(voltage);

  // Calculate the celsius temperature, based on that voltage..
  celsius = (voltage - 0.5) * 100;
  Serial.print("Celsius: "); // Print celcius temp to serial monitor
  Serial.println(celsius);

  // Use a common equation to convert celsius to Fahrenheit. F = C*9/5 + 32.
  fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
  Serial.print("Fahrenheit: "); // Print Fahrenheit temp to serial monitor
  Serial.println(fahrenheit); 
  // Print a blank line
  Serial.println();       

    Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.
Serial.print("Signal from Pulse Sensor: ");
   Serial.println(Signal-420);                    // Send the Signal value to Serial Plotter.
  // Wait 1 second between readings
  delay(1000);

}
