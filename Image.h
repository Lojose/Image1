#pragma once
#include "Global.h"
class Image {
public:
	Image(double h, double w, double x, double y, byte *snapshot);
	void draw_();
	void setVelocity(double dx, double dy);
	void setSnap(byte *snapshot); 
	void update(double dt);
	void Imgload(byte *snapshot); 
	void write(FILE * file) const;
private:
	byte r;
	byte g;
	byte b;
	byte *snapshot; 
	byte *rgbofSnap; 
	double h;
	double w;
	double dx;
	double dy;
	double x;
	double y;

};