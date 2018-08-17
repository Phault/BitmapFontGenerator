#ifndef ANGELCODETEXTEXPORTER_H
#define ANGELCODETEXTEXPORTER_H

#include <exporters/exporter.h>

class AngelCodeTextExporter : public Exporter
{
public:
    AngelCodeTextExporter();

    void exportFont(const BitmapFont& font) const override;
};

#endif // ANGELCODETEXTEXPORTER_H
