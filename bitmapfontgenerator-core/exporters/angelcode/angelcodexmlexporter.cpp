#include "angelcodexmlexporter.h"
#include <QFile>
#include <QXmlStreamWriter>
#include "angelcodefont.h"

AngelCodeXmlExporter::AngelCodeXmlExporter()
{

}

void AngelCodeXmlExporter::exportFont(const BitmapFont &font) const
{
    QFile file(destination().absoluteFilePath());
    file.open(QFile::WriteOnly);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(mPrettify);
    stream << AngelCodeFont(font, *this);

    file.close();
}

bool AngelCodeXmlExporter::prettify() const
{
    return mPrettify;
}

void AngelCodeXmlExporter::setPrettify(bool prettify)
{
    mPrettify = prettify;
}
