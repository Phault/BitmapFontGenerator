#include "angelcodetextexporter.h"
#include <QFile>
#include <QTextStream>
#include "angelcodefont.h"

AngelCodeTextExporter::AngelCodeTextExporter()
{

}

void AngelCodeTextExporter::exportFont(const BitmapFont &font) const
{
    QFile file(destination().absoluteFilePath());
    file.open(QFile::WriteOnly);

    QTextStream stream(&file);
    stream << AngelCodeFont(font, *this);

    file.close();
}
