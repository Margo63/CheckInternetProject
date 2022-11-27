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

#include <auroraapp.h>
#include <QtQuick>
#include <QDebug>
#include <QObject>
#include <unistd.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <iostream>
#include <QTime>
#include <QQmlProperty>

void sleep(){
    QTime dieTime = QTime::currentTime().addSecs(10);
    while(QTime::currentTime()<dieTime)
        QGuiApplication::processEvents(QEventLoop::AllEvents,100);
}

class MyClass:public QObject{
    Q_OBJECT
    public :
    explicit MyClass(QObject *parent = nullptr):QObject(parent){

    }

};

Q_INVOKABLE QString func(){
    QScopedPointer<QQuickView> page(Aurora::Application::createView());
    page->setSource(Aurora::Application::pathTo(QStringLiteral("qml/pages/MainPage.qml")));
    QNetworkAccessManager nam;
    int i0=0;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();

    if(reply->bytesAvailable()){
        qDebug()<<i0<<" internet ok";
        page->rootObject()->setState("internet_ok");

        qDebug()<<page->rootObject()->setProperty("backgroundColor","forestgreen");
        page->rootObject()->setProperty("backgroundColor","forestgreen");
        return "internet_ok";
    }
    else{

        page->rootObject()->setState("internet_not");
        qDebug()<<page->rootObject()->setProperty("backgroundColor","forestgreen");
        page->rootObject()->setProperty("backgroundColor","firebrick");

        qDebug()<<i0<<"internet bad";
        return "internet_not";
    }
}
int main(int argc, char *argv[])
{
    //qmlRegisterType<MyClass>("io.myclass",1,0,"MyClass");
    //MyClass my;


    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("checkInternet"));



    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/checkInternet.qml")));
    view->show();


    QScopedPointer<QQuickView> page(Aurora::Application::createView());
    page->setSource(Aurora::Application::pathTo(QStringLiteral("qml/pages/MainPage.qml")));
    //qDebug()<<page->rootObject()->findChild<QObject*>("mouse")->setProperty("onClick",func());
    //page->rootContext()->setContextProperty("window",page->rootObject());

    QProcess proc;
    QNetworkAccessManager nam;
    int i0=0;

  // QObject * item = page->rootObject();
  // MyClass my;
  // QObject::connect(item,SIGNAL(qmlSignal(QString)),&my,SLOT(cppSlot(QString)));
   // while(true){
    //    sleep();
        i0+=10;
        QNetworkRequest req(QUrl("http://www.google.com"));
        QNetworkReply *reply = nam.get(req);
        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()),&loop,SLOT(quit()));
        loop.exec();

        if(reply->bytesAvailable()){
            qDebug()<<i0<<" internet ok";

            page->rootObject()->setState("internet_ok");

            qDebug()<<page->rootObject()->setProperty("backgroundColor","forestgreen");
            page->rootObject()->setProperty("backgroundColor","forestgreen");

        }
        else{

            page->rootObject()->setState("internet_not");
            qDebug()<<page->rootObject()->setProperty("backgroundColor","forestgreen");
            page->rootObject()->setProperty("backgroundColor","firebrick");

            qDebug()<<i0<<"internet bad";
        }

       // sleep();
        //qDebug()<<QQmlProperty(page->rootObject(),"backgroundColor").write("magenta");
    //}

    //qDebug()<<page->rootObject()->property("backgroundColor");
    return application->exec();
}
