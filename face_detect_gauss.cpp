#include <cstdio>
#include <cstdlib>
#include <cv.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "ary.hpp"
#include "function.hpp"

using namespace cv;

int main() {
	unsigned int ***rgb, **pdf, *hist, **median, **dilate, **erosion, **fill;
	float ***ycbcr, **sgmnt;
	unsigned int c, x, y;
	unsigned int ch, height, width, max_val, max_val_binary;
	unsigned int hist_sum, thres;
	unsigned int subj, inst;
	unsigned int x_max, x_min, y_max, y_min;
	Mat frame;
	subj = 0;																// Subject number
	inst = 0;																// Instance number
	VideoCapture stream(0);													// Open video stream
	if (!stream.isOpened()) {
		printf("Error: Failed to open the camera\n");
		exit(1);
	}
	stream.read(frame);														// Read video frame
	max_val = 255;
	ch = 3;
	height = frame.rows;
	width = frame.cols;	
	rgb = new_uint_3D(height, width, ch);									// Allocate memory to array
	ycbcr = new_float_3D(height, width, ch);
	sgmnt = new_float_2D(height, width);
	pdf = new_uint_2D(height, width);
	hist = new_uint_1D(max_val + 1);
	median = new_uint_2D(height, width);
	dilate = new_uint_2D(height, width);
	erosion = new_uint_2D(height, width);
	fill = new_uint_2D(height, width);
//	while (1) {	
		stream.read(frame);									// Read video frame
		rgb_to_ycbcr_mat(frame, ycbcr, height, width);						// RGB to YCbCr					
		gauss_skin_sgmnt(ycbcr, sgmnt, height, width);						// Gaussian skin color segmentation
		pdf_scale(sgmnt, pdf, height, width, max_val);						// Probability density function value scaling
		hist_gray(pdf, hist, &hist_sum, height, width, max_val);			// Grayscale image histogram
		calc_thres(hist, hist_sum, &thres, height, width, max_val);			// Threshold calculation
		max_val_binary = 1;													
		binarize(pdf, thres, height, width, max_val);						// Binarization
		median_filter(pdf, median, height, width, max_val_binary);			// Median filtering
		dilate_filter(median, dilate, height, width);						// Dilation filtering
		erosion_filter(dilate, erosion, height, width, max_val);			// Erosion filtering
		border_clr(erosion, height, width);									// Border clearing
		hole_fill(erosion, fill, height, width);							// Hole filling
		ccl(fill, &x_max, &x_min, &y_max, &y_min, height, width);			// Connected component labeling	
		draw_box_rgb_mat(frame, x_max, x_min, y_max, y_min, height, width);	// Draw bounding box
		wr_rgb_ppm_mat(frame, subj, inst, height, width, max_val);			// Write RGB PPM image		
/*		imshow("Camera", frame);											// Show detected face
		if (waitKey(30) >= 0)
			break;
	}
*/	

//Clear all allocated memory
del_uint_3D(rgb);
del_float_3D(ycbcr);
del_float_2D(sgmnt);
del_uint_2D(pdf);
del_uint_1D(hist);
del_uint_2D(median);
del_uint_2D(dilate);
del_uint_2D(erosion);
del_uint_2D(fill);

return 0;

}
