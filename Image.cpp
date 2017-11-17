#include <iostream>
#include "Image.h"
#include "Frame.h"
#include "Global.h"

extern Frame frame;
Image::Image(double h, double w, double x, double y, byte *snapshot) : h(h), w(w), x(x), y(y), snapshot(snapshot)  {
	rgbofSnap = new byte[W * H * 3]; 
}

void Image::setVelocity(double dx, double dy) {
	this->dx = dx;
	this->dy = dy;
}

void Image::update(double dt) {
	x += dx*dt;
	y += dy*dt;
}

void Image::setSnap(byte *snapshot) {
	this->snapshot = snapshot; 
}

void Image::Imgload(byte *snapshot) {
	//std::cout << static_cast<unsigned short>(r) << std::endl;
	for (int i = 0; i < 3;  i++) {
		for (int h = 0; h < 480; h++) {
			for (int k = 0; k < 720; k++) {
				rgbofSnap[k * h * i] = static_cast<unsigned short>(snapshot[k * h * i]);
			}
		}
	}
	/*
	for (int i = 0; i < 720 * 480; i++) {
		rgbofSnap[i] = static_cast<unsigned short>(snapshot[i]); 
	}
	*/
}

void Image::write(FILE * file) const {
	fwrite(rgbofSnap, 3, W * H, file);
}

void Image::draw_() {
	if (frame.isOutside(&x, &y)) return;
	double x0 = x;
	double x1 = x + w;
	double y0 = y;
	double y1 = y + h;
	frame.clamp(&x0, &y0);
	frame.clamp(&x1, &y1);
	for (double y = y0; y < y1; ++y) {
		for (double x = x0; x < x1; ++x) {
			frame.setPixel(x, y, r, g, b);
		}
	}
}
