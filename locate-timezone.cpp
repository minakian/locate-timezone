#include "google-maps-device-locator.h"

GoogleMapsDeviceLocator locator;

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

void locationCallback(float lat, float lon, float accuracy){
    Serial.println(lat);
    Serial.println(lon);
    Serial.println(accuracy);
    String data = String::format("{ \"lat\": %f, \"lon\": %f, \"timeStamp\": %i }",lat, lon, Time.now());
    Serial.println(data);
    Particle.publish("timeZone", data, PRIVATE);

}

void setup() {
	Serial.begin(115200);
	delay(5000);
	locator.withLocateOnce();
	locator.withSubscribe(locationCallback);
//	Particle.subscribe("hook-response/deviceLocator", myHandler, MY_DEVICES);
    Particle.subscribe("hook-response/timeZone", myHandler, MY_DEVICES);
}

void loop() {
	locator.loop();
}
