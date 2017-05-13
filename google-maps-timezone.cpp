#include "Particle.h"
#include "google-maps-timezone.h"

static char requestBuf[256];

GoogleMapsTimeZone::GoogleMapsTimeZone():eventName("timeZone"){
    locator = new GoogleMapsDeviceLocator();
}

GoogleMapsTimeZone::~GoogleMapsTimeZone(){

}

void GoogleMapsTimeZone::begin(){
  locator -> withLocateOnce();
  locator -> withSubscribe(GoogleMapsTimeZone::locationCallback);
  timeZoneSubscribe();
}

void GoogleMapsTimeZone::locationCallback(float lat, float lon, float accuracy){
  String data = String::format("{ \"lat\": %f, \"lon\": %f, \"timeStamp\": %i }",lat, lon, Time.now());
  Serial.println(data);
  Particle.publish("timeZone/" + String(System.deviceID()), data, PRIVATE);
}

void GoogleMapsTimeZone::loop(){
  locator ->loop();
}

void GoogleMapsTimeZone::timeZoneSubscribe(){
  snprintf(requestBuf, sizeof(requestBuf), "hook-response/%s/%s", eventName.c_str(), System.deviceID().c_str());
  Particle.subscribe(requestBuf, &GoogleMapsTimeZone::subscriptionHandler, this, MY_DEVICES);

}

void GoogleMapsTimeZone::subscriptionHandler(const char *event, const char *data) {
	// event: hook-response/timeZone/<deviceid>/0
  char *mutableCopy = strdup(data);
  char *part, *end;

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
  String dat = String::format("{ \"dstOffset\": %i, \"rawOffset\": %i, \"status\": " + status + " }",dstOffset, rawOffset);
  Serial.println(dat);
  Serial.println(dstOffset);
  Serial.println(rawOffset);
  Serial.println(status);
}
