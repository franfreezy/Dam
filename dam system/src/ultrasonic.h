#define TRIG_PIN 9       
#define ECHO_PIN 10    

String getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;  // Convert duration to distance in cm

  return String(distance, 2);  // Return distance as a string with 2 decimal places
}
