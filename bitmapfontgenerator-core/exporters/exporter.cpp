#include "exporter.h"

void Exporter::exportBitmaps(const BitmapFont &font)
{
    auto format = imageFormat().toLatin1();

    const auto &pages = font.pages();
    for (int i = 0; i < pages.length(); ++i)
        pages[i].save(getPagePath(i, pages.length()).absoluteFilePath(), format);
}

void Exporter::exportAll(const BitmapFont &font)
{
    exportFont(font);
    exportBitmaps(font);
}

QString Exporter::imageFormat() const
{
    return mImageFormat;
}

void Exporter::setImageFormat(const QString &imageFormat)
{
    mImageFormat = imageFormat;
}

QFileInfo Exporter::destination() const
{
    return mDestination;
}

void Exporter::setDestination(const QFileInfo &fileInfo)
{
    mDestination = fileInfo;
}

void Exporter::setDestination(const QString &destination)
{
    mDestination = QFileInfo(destination);
}

QFileInfo Exporter::getPagePath(int pageNumber, int totalPages) const
{
    const static QString fileNamePattern(QString("%1.%2"));
    const auto pageNumberWidth = int(log10(totalPages) + 1);

    auto fileName = destination()
            .baseName()
            .append(fileNamePattern.arg(pageNumber, pageNumberWidth, 10, QChar('0')).arg(imageFormat().toLower()));

    return destination()
            .absoluteDir()
            .absoluteFilePath(fileName);
}
