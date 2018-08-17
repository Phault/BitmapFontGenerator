#ifndef ANGELCODEBINARYEXPORTER_H
#define ANGELCODEBINARYEXPORTER_H

#include <exporters/exporter.h>

class AngelCodeBinaryExporter : public Exporter
{
public:
    AngelCodeBinaryExporter();

    void exportFont(const BitmapFont& font) const override;
};

#endif // ANGELCODEBINARYEXPORTER_H
