#!/usr/bin/env node

/**
 * Define the RAPP Cloud Services object, which needs a username and password
 * @namespace RAPPCloud
 */
function RAPPCloud ( )
{
    //this.cloud_url = "http://155.207.19.13:9001";
    this.cloud_url = "http://localhost:9001"; 
}


/// Export
module.exports = RAPPCloud;
