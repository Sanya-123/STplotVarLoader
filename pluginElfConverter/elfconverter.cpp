#include "elfconverter.h"
#include "conf2var.h"

ElfConverter::ElfConverter(QObject *parent) : QObject(parent)
{
    backendIp = "10.9.0.190";
}

varloc_node_t *ElfConverter::readTree(QString fileName)
{
    QNetworkAccessManager manager;
    QString filePath = fileName;
    QFileInfo fileInfo(fileName);
    //Upload
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Failed to open file for reading:" << file.errorString();
        return nullptr;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + fileInfo.baseName() + "\""));
    filePart.setBodyDevice(&file);
    file.setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
    multiPart->append(filePart);

    QNetworkRequest request_upl = QNetworkRequest(QUrl("http://"+backendIp+":5000/upload")); // Change the URL to your server's endpoint
    // Send the request
    QNetworkReply *reply_upl = manager.post(request_upl, multiPart);

    // Wait for the reply to finish or timeout after 2 seconds
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);

    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    QObject::connect(reply_upl, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    timer.start(2000);
    loop.exec();

    if (!timer.isActive())
    {
        // Timeout occurred, abort the request and handle the timeout
        timer.stop();
        QObject::disconnect(reply_upl, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        qCritical() << "Request timed out";
        reply_upl->abort();
        QMessageBox::warning(0,"ElfConverter","Reqeust timed out");
        return nullptr;
    }
    else
    {
        timer.stop();
        if(reply_upl->error() > 0) {
            qCritical() << "Network error:" << reply_upl->errorString();
            reply_upl->abort();
            QMessageBox::warning(0,"ElfConverter","Network error: "+reply_upl->errorString());
            return nullptr;
        }
        else {
            int v = reply_upl->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            if (v >= 200 && v < 300) {  // Success
                qDebug() << "Request completed";
            }
            else
            {
                qCritical() << "Request no success";
                reply_upl->abort();
                QMessageBox::warning(0,"ElfConverter","Request no success");
                return nullptr;
            }
        }
    }

    // Check for errors
    if (reply_upl->error() != QNetworkReply::NoError)
    {
        qCritical() << "Error:" << reply_upl->errorString();
        QMessageBox::warning(0,"ElfConverter","Error: " + reply_upl->errorString());
    }
    else
    {
        qDebug() << "Upload successful";
        qDebug() << "Response:" << reply_upl->readAll();

        QString url = "http://"+backendIp+":5000/download/" + fileInfo.baseName() + ".elfconf";

        QNetworkAccessManager manager;
        QNetworkRequest request_dnld = QNetworkRequest(QUrl(url));

        QNetworkReply *reply_dnld = manager.get(request_dnld);

        // Wait for the reply to finish or timeout after 2 seconds
        timer.setSingleShot(true);

        QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        QObject::connect(reply_dnld, &QNetworkReply::finished, &loop, &QEventLoop::quit);

        timer.start(2000);
        loop.exec();

        if (!timer.isActive())
        {
            // Timeout occurred, abort the request and handle the timeout
            timer.stop();
            qCritical() << "Request timed out";
            QMessageBox::warning(0,"ElfConverter","Request timed out");
            reply_dnld->abort();
        }
        else
        {
            // Request finished before timeout
            qDebug() << "Request completed";

            // Check for errors
            if (reply_dnld->error() == QNetworkReply::NoError)
            {
                QByteArray data = reply_dnld->readAll();
                QString filePath = fileInfo.baseName()+".elfconf"; // Change the filename if needed
                QFile file(filePath);
                if (file.open(QIODevice::WriteOnly))
                {
                    file.write(data);
                    file.close();
                    qDebug() << "File downloaded successfully";
                    varloc_node_t* node = conf2var(filePath.toLocal8Bit().data());
                    return node;
                }
                else
                {
                    qCritical() << "Failed to open file for writing:" << file.errorString();
                    QMessageBox::warning(0,"ElfConverter","Failed to open file for writing: " + file.errorString());
                }
            }
            else
            {
                qCritical() << "Download failed:" << reply_dnld->errorString();
                QMessageBox::warning(0,"ElfConverter","Download failed: " + reply_dnld->errorString());
            }
        }
        reply_dnld->deleteLater();
    }

    reply_upl->deleteLater();
    return nullptr;
}

QString ElfConverter::getBackendIp() const
{
    return backendIp;
}

void ElfConverter::setBackendIp(const QString &newBackendIp)
{
    backendIp = newBackendIp;
}
