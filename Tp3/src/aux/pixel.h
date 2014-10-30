typedef unsigned int uint;

struct pixel {
pixel();
pixel(uint, uint, uint);

uint red;
uint green;
uint blue;
};

pixel::pixel(){red=0;green=0;blue=0;}
pixel::pixel(uint r, uint g, uint b){red=r;green=g;blue=b;}
