#include "google-maps-timezone.h"

//GoogleMapsDeviceLocator locator;
GoogleMapsTimeZone zone;

void myHandler(const char *event, const char *data){
//    Serial.println(event);
//    Serial.println(data);
  char *mutableCopy = strdup(data);
	char *part, *end;
	int dstOffset, rawOffset;
	String  status;

	part = strtok_r(mutableCopy, ",", &end);
	if (part) {
//	    Serial.println(part);
		dstOffset = atoi(part);
		part = strtok_r(NULL, ",", &end);
		if (part) {
			rawOffset = atoi(part);
			part = strtok_r(NULL, ",", &end);
			if (part) {
				status = part;
//
//				//(*callback)(lat, lon, accuracy);
			}
		}
	}

	free(mutableCopy);
	Serial.println(dstOffset);
	Serial.println(rawOffset);
	Serial.println(status);
}


void setup() {
	Serial.begin(115200);
	delay(5000);

  //Particle.subscribe(System.deviceID() + "hook-response/timeZone", myHandler, MY_DEVICES);
  zone.begin();
}

void loop() {
	zone.loop();
}
