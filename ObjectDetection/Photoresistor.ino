/**
 * @brief This method finds the luminosity from
 * the photoresistor.
 * 
 * @return int - luminosity from the photoresistor.
 */
int getLuminosity() {
  // do analogRead of photoresistor pin
  int luminosity = analogRead(PHOTORESISTOR_PIN);
  Serial.println(luminosity);
  return luminosity;
}