//    Copyright (C) 2015 Rog131 <samrog131@hotmail.com>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "keneric.h"

#include <QLoggingCategory>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QProcess>
#include <QMimeType>
#include <QMimeDatabase>
#include <QStandardPaths>
#include <QCryptographicHash>
#include <KPluginFactory>

Q_LOGGING_CATEGORY(LOG_KENERIC, "com.keneric")

K_PLUGIN_CLASS_WITH_JSON(Keneric, "keneric.json")
Keneric::Keneric(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args) {};

Keneric::~Keneric() = default;

KIO::ThumbnailResult Keneric::create(const KIO::ThumbnailRequest &request)
{
    const QString path = request.url().toLocalFile();

    QImage img;
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(path);

    QString kenericDirectory((QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) + QString::fromUtf8("/keneric/")));
    QString md5Hash = QString::fromUtf8(QCryptographicHash::hash((path.toUtf8()),QCryptographicHash::Md5).toHex());
    QString protoThumbnail(kenericDirectory + md5Hash + QString::fromUtf8(".png"));

    QDir directory(kenericDirectory);
    if (!directory.exists()) {
        directory.mkpath(QString::fromUtf8("."));
    }

    QObject *parent = NULL;
    QString program = QString::fromUtf8("keneric");
    QStringList arguments;
    arguments << path << mime.name() << protoThumbnail;
    QProcess *startAction = new QProcess(parent);
    startAction->start(program, arguments);
    startAction->waitForFinished();

    QFile thumbnailFile(protoThumbnail);
    if (thumbnailFile.exists()){
        QImage previewImage(protoThumbnail);
        img = previewImage.scaled(request.targetSize().width(), request.targetSize().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QFile::remove(protoThumbnail);
    }

    if (!img.isNull()) {
        return KIO::ThumbnailResult::pass(img);
    }

    return KIO::ThumbnailResult::fail();
}

#include "keneric.moc"
