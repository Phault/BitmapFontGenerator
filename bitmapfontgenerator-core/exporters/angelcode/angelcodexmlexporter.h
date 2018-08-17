#ifndef ANGELCODEXMLEXPORTER_H
#define ANGELCODEXMLEXPORTER_H

#include <exporters/exporter.h>

class AngelCodeXmlExporter : public Exporter
{
public:
    AngelCodeXmlExporter();

    void exportFont(const BitmapFont& font) const override;

    bool prettify() const;
    void setPrettify(bool prettify = true);

private:
    bool mPrettify = false;
};

#endif // ANGELCODEXMLEXPORTER_H
