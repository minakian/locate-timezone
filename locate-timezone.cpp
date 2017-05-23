/****************************************
 *  Title:        locate-timezone.cpp
 *  Description:  Using google maps APIs
 *    gather the current timezone that the
 *    device is located in.
 *  Author:       Stephen Minakian
 *  Version:      0.2
 *  Date:         05/23/2017
 ****************************************/

#include "google-maps-timezone.h"


//GoogleMapsDeviceLocator locator;
GoogleMapsTimeZone zone;

void setup() {
	Serial.begin(115200);
	delay(5000);

  zone.begin();
  zone.getTimezone();
}

void loop() {
	//zone.loop();
}
