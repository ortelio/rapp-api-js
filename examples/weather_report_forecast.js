#!/usr/bin/env node

// Import the weather_report_forecast JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.weather_report_forecast = 
    require('../lib/cloud/weather_report_forecast');

var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.weather_report_forecast
 */
function callback (forecast)
{
//    date: '', temperature: '', weather_description: '', humidity: '', visibility: '', pressure: '', wind_speed: '', wind_temperature: '', wind_direction: ''
    for (var i=0; i<forecast.length; i++) {
    	var str = JSON.stringify(forecast[i], null, 2);
    	console.log(str);
    }
}

services.weather_report_forecast('Thessaloniki', '', 0, callback);
