#version 400 core

layout(origin_upper_left) in vec4 gl_FragCoord;
flat in double xmin;
flat in double ymin;
flat in double xmax;
flat in double ymax;
flat in double xscl;
flat in double yscl;
in float resolutionX;
in float resolutionY;
flat in int axis;

out vec4 frag_color;
 
#define MAX_ITERATIONS 500

int mandelbrot(double zReal, double zImagine, int iterations) {

	double ztReal = zReal;
	double ztImagine = zImagine;
	
	int i = 0;
	
	while(i <= iterations) {
		
		double distance = ztReal * ztReal + ztImagine * ztImagine;
		
		if(distance > 4.0) {
			return(i);
		}
		
		double real = (ztReal * ztReal - ztImagine * ztImagine) + zReal;
		double imagine = (2.0 * ztReal * ztImagine) + zImagine;
		
		ztReal = real;
		ztImagine = imagine;
		
		i += 1;
	}
	
	return(iterations);
}



vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}
 
 


void main() { 
	
	if(axis == 1) {
	
		if( int(gl_FragCoord.x) == int(resolutionX / 2.0) ) {
			frag_color = vec4(1.0, 1.0, 1.0, 1.0);
			return;
		}
	
		if( int(gl_FragCoord.y) == int(resolutionY / 2.0) ) {
			frag_color = vec4(1.0, 1.0, 1.0, 1.0);
			return;
		}
	}
	
	double zReal = xmin + double(gl_FragCoord.x) * xscl;
	double zImagine = ymin + double(gl_FragCoord.y) * yscl;
	int iterations;
	
	iterations = mandelbrot(zReal, zImagine, MAX_ITERATIONS);

	
	if(iterations == MAX_ITERATIONS) {
		frag_color = vec4(0.0, 0.0, 0.0, 1.0);
	} else {
		float hue = 255.0 - 30.0 * float(iterations) / 255.0;
		frag_color = vec4(hsv2rgb( vec3(hue, 1.0, 1.0) ), 1.0);
	}
}


