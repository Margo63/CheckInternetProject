/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the Моё приложение для ОС Аврора project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id:page1
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    state: "internet_not"
    backgroundColor: "firebrick"
    states: [
        State {
            name: "internet_ok"
            PropertyChanges {
                target: page1;
                backgroundColor: "forestgreen"

            }
            PropertyChanges {
                target: label;
                text:"Internet connection ok"

            }
        },
        State {
            name: "internet_not"
            PropertyChanges {
                target: page1;
                 backgroundColor: "firebrick"
            }
            PropertyChanges {
                target: label;
                text:"No Internet"

            }
        }
    ]

    Label{
        id:label
        text:  "Есть доступ в интернет"
        font.pixelSize: 42
    }


    MouseArea{
        objectName: "mouse"
        id: mouse
        anchors.fill: parent
        onClicked: {

            //parent.state=(parent.state == "internet_not"?"internet_ok":"internet_not")
            //parent.qmlSignal("Hello")
           // parent.state = func()

            var req = new XMLHttpRequest;
//            //var i=0;
            //var nam = Qt.QNetworkAccessManager;
            req.onreadystatechange =function(){
                if(req.readyState === XMLHttpRequest.DONE){
                    console.log(req.responseText)
                     //parent.state = "internet_ok";
                }
                //else
                    //console.log(req.responseText)
                     //parent.state = "internet_not";
            }
            req.open("GET","http://www.google.com");
            req.send()
            if (req.responseText!=" ") {
                //i++;
                parent.state = "internet_ok";
            }
            else{
               // var nam = new QNetworkAccessManager;

                parent.state = "internet_not";
                //("http://www.google.com"));


            }


        }
    }

}

