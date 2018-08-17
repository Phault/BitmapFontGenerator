#ifndef EXPORTER_H
#define EXPORTER_H

#include "bitmapfont.h"
#include <QDir>
#include <QString>

class Exporter
{
public:
    virtual ~Exporter() {}

    virtual void exportFont(const BitmapFont &font) const = 0;
    void exportBitmaps(const BitmapFont &font);
    void exportAll(const BitmapFont &font);

    QString imageFormat() const;
    void setImageFormat(const QString &imageFormat);

    QFileInfo destination() const;
    void setDestination(const QFileInfo &destination);
    void setDestination(const QString &destination);

    QFileInfo getPagePath(int pageNumber, int pageNumberWidth) const;

private:
    QFileInfo mDestination { "./bitmapfont.fnt" };
    QString mImageFormat = "PNG";
};

#endif // EXPORTER_H
