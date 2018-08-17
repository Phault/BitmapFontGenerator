#include "angelcodejsonexporter.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include "angelcodefont.h"

AngelCodeJsonExporter::AngelCodeJsonExporter()
{

}

void AngelCodeJsonExporter::exportFont(const BitmapFont &font) const
{
    QFile file(destination().absoluteFilePath());
    file.open(QFile::WriteOnly);

    QJsonObject root;
    root << AngelCodeFont(font, *this);

    QJsonDocument doc(root);
    auto format = mPrettify ? QJsonDocument::JsonFormat::Indented : QJsonDocument::JsonFormat::Compact;
    file.write(doc.toJson(format));

    file.close();
}

bool AngelCodeJsonExporter::prettify() const
{
    return mPrettify;
}

void AngelCodeJsonExporter::setPrettify(bool prettify)
{
    mPrettify = prettify;
}
