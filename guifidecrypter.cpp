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

#include "guifidecrypter.h"
#include "ui_guifidecrypter.h"


GuifiDecrypter::GuifiDecrypter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuifiDecrypter)
{
    ui->setupUi(this);
    timerXmlLoop = new QTimer(this);
    connect(timerXmlLoop, SIGNAL(timeout()), this, SLOT(readXml()));
    xmlfilename = "/tmp/1304109527.0-01.kismet.netxml"; //This is just for debug
    airodumpProcess = new QProcess(this);
    connect(airodumpProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onAirodump_finished(int, QProcess::ExitStatus)));
    ui->labelOn->setVisible(false);
    ui->labelAction->setVisible(false);
    updateNetworkInterfaces();


}

GuifiDecrypter::~GuifiDecrypter()
{
    delete ui;
}

void GuifiDecrypter::on_checkBoxChannel_toggled(bool checked)
{
        ui->lineEditChannel->setEnabled(!checked); //awsom :D
}

void GuifiDecrypter::onAirodump_finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    //QMessageBox::information(this, "", "process finished");
    qDebug() << "Finished airodump" << exitCode << " - " << exitStatus;
    ui->textEditDebug->append(QString("Finished airodump-ng:\n\tExitCode: %1 \n\texit Status: %2").arg(exitCode).arg(exitStatus));
    ;
}

void GuifiDecrypter::on_textEditDebug_textChanged()
{
    ui->statusBar->showMessage("New Message in Debug Tab", 1599);
}

void GuifiDecrypter::on_toolButtonStart_toggled(bool checked)
{
    if(checked){
        qDebug() << "Scan On";
        timerXmlLoop->start(2000);
        ui->labelOn->setVisible(true);
        startAirodump();
    }else{
        qDebug() << "Scan Off";
        timerXmlLoop->stop();
        ui->labelOn->setVisible(false);
        ui->labelAction->setVisible(false);
    }
}

void GuifiDecrypter::startAirodump(){
    //DONE ME, USE WIDGETS
    QString command = "/bin/touch";
    QStringList arguments;
    arguments << "/tmp/testttttttttttttttttttt";
    airodumpProcess->start(command, arguments);
}

void GuifiDecrypter::updateNetworkInterfaces(){
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    QNetworkInterface iface;
    ui->comboBoxInterface->clear();
    foreach( iface, list ){
        ui->comboBoxInterface->addItem(iface.name());
        qDebug() << "fount interface: " << iface.name();
        ui->textEditDebug->append("fount interface: " + iface.name());
    }
}

void GuifiDecrypter::readXml(){
    QFile file(xmlfilename);

    ui->labelAction->setVisible(true);

    bool open = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!open)
    {
        qDebug() << "No file " << xmlfilename;
        ui->textEditDebug->append("No file " + xmlfilename);
    }
    else{

        QXmlStreamReader xml(&file);
        while (!xml.atEnd() && !xml.hasError())
        {
            xml.readNext();
            if (xml.isStartElement() && xml.name() == "wireless-network")
            {
                parseWirelessNetwork(xml);
                //qDebug() << "Element Name: " << xml.name();
                //qDebug() << "Text: " << xml.readElementText();
            }
            else if (xml.hasError())
            {
                qDebug() << "XML ERROR: " << xml.errorString();
                ui->textEditDebug->append("XML ERROR: " + xml.errorString());

            }
            else if (xml.atEnd())
            {
                qDebug() << "End of file";
            }
        }
    }

    ui->labelAction->setVisible(false);

}

void GuifiDecrypter::parseWirelessNetwork(QXmlStreamReader& xml){
    QString bssid, pwr, data, ch, mb, enc, essid, lts;
    QStringList columns;
    QTreeWidget * tree = ui->treeWidgetNetworks;
    QList<QTreeWidgetItem *> itemsMatchs;
    QTreeWidgetItem itemManipulation;

    xml.readNextStartElement();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "wireless-network")){
        if(xml.name() == "BSSID"){
            bssid = xml.readElementText();
        }
        else if(xml.name() == "last_signal_dbm"){
            pwr = xml.readElementText();
        }
        else if(xml.name() == "data"){
            data = xml.readElementText();
        }
        else if(xml.name() == "channel"){
            ch = xml.readElementText();
        }
        else if(xml.name() == "max-rate"){
            mb = xml.readElementText();
        }
        else if(xml.name() == "encryption"){
            enc = xml.readElementText();
        }
        else if(xml.name() == "essid"){
            essid = xml.readElementText();
        }
        else if(xml.name() == "SSID"){
            lts = "done me";
        }

        xml.readNextStartElement();
    }
    columns << bssid << pwr << data << ch << mb << enc << essid << lts;

    itemsMatchs = tree->findItems(bssid,0,0);

    //ugly but works. Improve later. ¿proxyModel?;
    if(itemsMatchs.length() > 0){
        itemsMatchs.first()->setText(0,bssid);
        itemsMatchs.first()->setText(1,pwr);
        itemsMatchs.first()->setText(2,data);
        itemsMatchs.first()->setText(3,ch);
        itemsMatchs.first()->setText(4,mb);
        itemsMatchs.first()->setText(5,enc);
        itemsMatchs.first()->setText(6,essid);
        itemsMatchs.first()->setText(7,lts);
    }else{
        tree->addTopLevelItem(new QTreeWidgetItem(columns));
    }

}



// NOTES
//
//ui->toolButtonStart->click();

//QTreeWidget * tree = ui->treeWidgetNetworks;
//QTreeWidgetItem * topLevel = new QTreeWidgetItem();
//topLevel->setText(0, "This is top level");
//topLevel->
//for(int i=0; i<5; i++)
//{
//    QTreeWidgetItem * item = new QTreeWidgetItem();
//    item->setText(0,"item " + QString::number(i+1));
//    topLevel->addChild(item);
//}

//QStringList columns;
//columns << QString("columna0");
//columns << QString("columna1");
//columns << QString("columna2");
//columns << QString("columna3");
//columns << QString("columna4");
//columns << QString("columna5");
//columns << QString("columna6");
//columns << QString("columna7");

//tree->addTopLevelItem(new QTreeWidgetItem(columns));


