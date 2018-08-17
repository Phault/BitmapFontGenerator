# Bitmap Font Generator
## About
FOSS and cross-platform alternative to Glyph Designer made with Qt.

Renders specified characters with a font to one (or multiple) textures, applying several neat effects in the process and creates a lookup file containing each character's position and dimension in the textures. These 'Bitmap fonts' are used for efficiently rendering text in games and general 3D applications.

Created to teach myself modern-ish C++ and Qt.

## Status
Core is very far, but the GUI lacks a lot of features.

## Features
* Live preview
* Supports kerning
* Efficiently packed
* Customize how the font is packed
	* Padding
	* Glyph spacing
	* Kerning
	* Packing method
	* Texture size
* Customizable effects*
	* Filling
		* Gradient
		* Texture
		* Solid
	* Stroke
	* Drop shadow
	* Inner shadow
	* Blur
* Multiple export formats*
  * [AngelCode's BMFont](http://www.angelcode.com/products/bmfont/):
  	* Text
  	* Binary
  	* JSON
  	* XML

\* Not yet supported with the GUI

## Download
Sorry, there's no binaries to download yet. The GUI is not yet in a useable state.

## License
[MIT](https://tldrlegal.com/license/mit-license) - Do whatever you want. :)