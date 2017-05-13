#ifndef __GOOGLEMAPSTIMEZONE_H
#define __GOOGLEMAPSTIMEZONE_H

#include "google-maps-device-locator.h"
#include "Particle.h"

class GoogleMapsTimeZone{
public:
  GoogleMapsTimeZone();
  virtual ~GoogleMapsTimeZone();
  void begin();
  static void locationCallback(float lat, float lon, float accuracy);
  void loop();

  GoogleMapsDeviceLocator * locator;

protected:
  String eventName, status;
  int dstOffset, rawOffset;
  void timeZoneSubscribe();
  void subscriptionHandler(const char *event, const char *data);
};

#endif
