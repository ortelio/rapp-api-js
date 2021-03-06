#!/usr/bin/env node

var path = require('path');
var formData = require('form-data');
var randomstring = require('randomstring');
var __cloudDir = path.join(__dirname);
var __objectsDir = path.join(__dirname, '..', 'objects');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject.js'));
RAPPObject.human = require(path.join(__objectsDir, 'human.js'));
RAPPObject.picture = require(path.join(__objectsDir, 'picture.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class human_detection
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to detect humans
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param image is the input image 
 * @param callback is the function that will receive a vector of the detected
 * human(s) coordinates
 */
RAPPCloud.prototype.human_detection = function(
                                                image, 
                                                callback
                                              )
{
    var cloud = this;
    var object = new RAPPObject();
    var _delegate = callback;
    var request = cloud.determine_protocol();
	var form = new formData();
    var pic = new object.picture(image);
	//Generate a random file name under which the image will be saved on the Server 
	var filename = randomstring.generate() + '.' + pic.img_type;
	
	form.append('file', pic.image, { 
		filename: filename,
		contentType: 'image/' + pic.img_type
	});
	var r = request.post(
                            cloud.cloud_url + '/hop/human_detection/ ', 
                            function(error, res, json) { 
                                if (res.statusCode==200 && !error){
                                    handle_reply(json);
                                }
                                else if (error) {
                                    error_handler(error);	
                                }
                                else if (res.statusCode != 200) {
                                    console.log(res.statusCode);
                                }
                            }
                        );
	r._form = form;
	r.setHeader('Connection', 'close');
	r.setHeader('Accept-Token', cloud.token);

	function handle_reply(json)
    {
		var json_obj;
		var humans = [];
		try {
			// JSON reply is eg.: { "humans":[{"up_left_point":{"x":212.0,"y":200.0},
            // "down_right_point":{"x":391.0,"y":379.0}}],"error":""}
            json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors  
				console.log('humanDetection JSON error: ' + json_obj.error);
			}
			for (var i=0; i<json_obj.humans.length; i++){
				var up_left = json_obj.humans[i].up_left_point;
				var down_right = json_obj.humans[i].down_right_point;
				humans.push(new object.Human(up_left.x, up_left.y, down_right.x, down_right.y));
			}
			_delegate(humans);
		} catch (e) {
			console.log('human_detection::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}
};

/// Export
module.exports = RAPPCloud.human_detection;
