#!/usr/bin/env python


# Copyright 2016 RAPP

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

    #http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Authors: Konstantinos Panayiotou
# contact: klpanagi@gmail.com


## @file RappCloud/CloudServices/Service.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


import base64
from os import path

from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


##
#  @brief Face-Detection Cloud Service Class.
#  @param fast
#  @param image
#
class TextToSpeech(Service):
    def __init__(self, *args, **kwargs):
        # Cloud Service request arguments
        self.text = ''
        self.language = ''
        ###############################

        super(TextToSpeech, self).__init__(
            svcname='text_to_speech',
            **kwargs
            )


    def get_audio_raw(self):
        try:
            b64Data = self.resp.payload
            rawData = base64.b64decode(b64Data)
        except TypeError as e:
            print str(e)
            return None
        return rawData


    def store_audio(self, destfile):
        destfile = path.expanduser(destfile)
        rawData = self.get_audio_raw()
        try:
            with open(destfile, 'wb') as f:
                f.write(rawData)
        except IOError as e:
            print str(e)
            return False
        return True



    ##
    #  @brief Create payload object of face_detection cloud service
    #
    def _make_payload(self):
        # Create and return payload object
        return Payload(text=self.text, language=self.language)


    ##
    #  @brief Create array of file object(s) of face_detection cloud service.
    #
    def _make_files(self):
        # Create and return array of file objects
        return []
