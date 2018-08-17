#include "angelcodebinaryexporter.h"
#include <QFile>
#include <QDataStream>
#include "angelcodefont.h"

AngelCodeBinaryExporter::AngelCodeBinaryExporter()
{

}

void AngelCodeBinaryExporter::exportFont(const BitmapFont &font) const
{
    QFile file(destination().absoluteFilePath());
    file.open(QFile::WriteOnly);

    QDataStream stream(&file);
    stream << AngelCodeFont(font, *this);

    file.close();
}
