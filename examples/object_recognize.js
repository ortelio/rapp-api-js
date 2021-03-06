#!/usr/bin/env node

// Import the object_recognition_caffe JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.object_recognition_caffe = require('../lib/cloud/object_recognition_caffe');
var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.object_recognition_caffe
 */
function handler(object_class)
{
    if (object_class) 
		console.log('A(n) ' + object_class + ' object was recognized!');
	else
		console.log('No objects recognized');
}

services.object_recognition_caffe('../testdata/cat.jpg', handler);
