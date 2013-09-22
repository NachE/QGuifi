#include "xmlreader.h"
#include <QXmlStreamReader>


QString ReadXml::readFile(QString filename){
    QFile file(filename);
    bool open = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!open)
    {
        out.Print("No file");
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNext();
        if (xml.isStartElement())
        {
            out.Print("element Name: ");
            out.Print(xml.name().toString().toUtf8().constData());
            out.Print("text: ");
            out.Print(xml.text().toString().toUtf8().constData());
        }
        else if (xml.hasError())
        {
           out.Print("XML error ");
           out.Print(xml.errorString().toUtf8().constData());

        }
        else if (xml.atEnd())
        {
           out.Print("Reached end, done");
        }
    }

    QString a = "test";
    return a;
}
