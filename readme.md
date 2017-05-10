# Location and Timezone Readme
## This application is an example of how to use google APIs to gather location and timezone information

The first half of this action uses the Particle integration and demo application "Google Maps (beta)" for which more information can be found here https://docs.particle.io/tutorials/integrations/google-maps/

The second half uses a custom webhook to publish the latitude, longitude, and timestamp. The latitude and longitude information are obtained from the Google Maps integration, while the timestamp is the date in time as seconds since January 1, 1970 for which you would like to get the relevant time information.

INTEGRATION (Webhook) INFO

Event Name        timeZone
Full URL          https://maps.googleapis.com/maps/api/timezone/json
Request Type      GET
Device            *Your devices go here*
Query Params
  {
    "location": "{{lat}},{{lon}}",
    "timestamp": "{{timeStamp}}",
    "key": "XXXYourAPIKeyHere",
    "": ""
  }
     
Include Default Attributes    No
Enforce SSL                   Yes
Response Template

  {{dstOffset}},{{rawOffset}},{{status}},{{timeZoneId}},{{timeZoneName}}

From te above response template, the necessary data is parsed prior to sending it to the device, from which the device may then extrapolate the required data fields directly.

# Code for gathering data

```
locator.withLocateOnce(); 
locator.withSubscribe(locationCallback);
Particle.subscribe("hook-response/timeZone", myHandler, MY_DEVICES);
```

`locator.loop();`

```
void locationCallback(float lat, float lon, float accuracy){
  String data = String::format("{ \"lat\": %f, \"lon\": %f, \"timeStamp\": %i }",lat, lon, Time.now());
  Particle.publish("timeZone", data, PRIVATE);
}
```

```
void myHandler(const char *event, const char *data){
  char *mutableCopy = strdup(data);
  char *part, *end;
  int dstOffset, rawOffset;
  String  status;

  part = strtok_r(mutableCopy, ",", &end);
  if (part) {
    dstOffset = atoi(part);
    part = strtok_r(NULL, ",", &end);
    if (part) {
      rawOffset = atoi(part);
      part = strtok_r(NULL, ",", &end);
      if (part) {
        status = part;
      }
    }
  }

  free(mutableCopy);
}
```
The code above shows how to extract the first 3 pieces of data, though this data should be saved somewhere.
