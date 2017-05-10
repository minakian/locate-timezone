# Location and Timezone Readme
## This application is an example of how to use google APIs to gather location and timezone information

The first half of this action uses the Particle integration and demo application "Google Maps (beta)" for which more information can be found here https://docs.particle.io/tutorials/integrations/google-maps/

The second half uses a custom webhook to publish the latitude, longitude, and timestamp. The latitude and longitude information are obtained from the Google Maps integration, while the timestamp is the date in time as seconds since January 1, 1970 for which you would like to get the relevant time information.

