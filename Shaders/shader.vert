#version 400 core

uniform float resX;
uniform float resY;
uniform int axisOn;
uniform float centerXhi;
uniform float centerXlo;
uniform float centerYhi;
uniform float centerYlo;
uniform float zoomHi;
uniform float zoomLo;

flat out double xmin;
flat out double ymin;
flat out double xmax;
flat out double ymax;
flat out double xscl;
flat out double yscl;
out float resolutionX;
out float resolutionY;
flat out int axis;


layout(location = 0) in vec3 pos;


void main()	{

	xmin = -2.0;
	xmax = 2.0;
	ymin = -2.0;
	ymax = 2.0;

	double zoom = double(zoomHi) + double(zoomLo);
	double centerX = double(centerXhi) + double(centerXlo);
	double centerY 	= double(centerYhi) + double(centerYlo);

	xmin = xmin * zoom + centerX;
	ymin = ymin * zoom + centerY;
	xmax = xmax * zoom + centerX;
	ymax = ymax * zoom + centerY;

	double rangex = xmax - xmin;
	double rangey = ymax - ymin;
	
	xscl = rangex / double(resX);
	yscl = rangey / double(resY);
	
	resolutionX = resX;
	resolutionY = resY;
	axis = axisOn;

	gl_Position = vec4(pos, 1.0);
}

