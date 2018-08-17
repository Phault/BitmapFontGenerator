#ifndef ANGELCODEJSONEXPORTER_H
#define ANGELCODEJSONEXPORTER_H

#include <exporters/exporter.h>

class AngelCodeJsonExporter : public Exporter
{
public:
    AngelCodeJsonExporter();

    void exportFont(const BitmapFont& font) const override;

    bool prettify() const;
    void setPrettify(bool prettify = true);

private:
    bool mPrettify = false;
};

#endif // ANGELCODEJSONEXPORTER_H
