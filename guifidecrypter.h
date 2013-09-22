/*
 * QGuifi - WIFI Analizer
 * Copyright (C) 2013  J.A. Nache
 *
 * This file is part of QGuifi.
 *
 * QGuifi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QGuifi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef GUIFIDECRYPTER_H
#define GUIFIDECRYPTER_H

#include <QMainWindow>
#include <QTimer>
#include <QXmlStreamReader>
#include <QString>
#include <QDebug>
#include <QtNetwork/QtNetwork>
#include "xmlreader.h"

namespace Ui {
class GuifiDecrypter;
}

class GuifiDecrypter : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuifiDecrypter(QWidget *parent = 0);
    ~GuifiDecrypter();



private slots:
    void on_toolButtonStart_toggled(bool checked);
    void readXml();
    void parseWirelessNetwork(QXmlStreamReader& xml);
    void updateNetworkInterfaces();
    void startAirodump();
    void onAirodump_finished(int exitCode, QProcess::ExitStatus exitStatus);

    void on_textEditDebug_textChanged();

    void on_checkBoxChannel_toggled(bool checked);

private:
    Ui::GuifiDecrypter *ui;
    QTimer *timerXmlLoop;
    QString xmlfilename;
    QProcess *airodumpProcess;

};

#endif // GUIFIDECRYPTER_H
