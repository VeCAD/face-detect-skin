#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cv.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "ary.hpp"

using namespace cv;

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

// Skip comments in image file
void skp_cmnt(FILE *fp) {
	int ch;
	char line[100];
	while ((ch = fgetc(fp)) != EOF && isspace(ch));
    if (ch == '#') {
        if(fgets(line, sizeof(line), fp));
        skp_cmnt(fp);
    } 
	else
		fseek(fp, -1, SEEK_CUR);
	return;
}

// Read RGB PPM image details
void rd_rgb_ppm_info(unsigned int subj, unsigned int inst, unsigned int *height, unsigned int *width, 
					 unsigned int *max_val) {
	char FN[100], ver[3];
	FILE *rd_img;
	sprintf(FN, "%s%d%s%d%s", "face_", subj, "_", inst, ".ppm");	
	rd_img = fopen(FN, "rb");
	if (rd_img == NULL) {
		printf("Failed to open file: %s\n", FN);
		exit(1);
	}
	// Check version
	if(fgets(ver, sizeof(ver), rd_img));
    if (strcmp(ver, "P6")) {
        fprintf(stderr, "Wrong file type!\n");
        exit(1);
    }
	// Read image details (height, width and maximum value)
	skp_cmnt(rd_img);
    if(fscanf(rd_img, "%d", width));
    skp_cmnt(rd_img);
    if(fscanf(rd_img, "%d", height));
    skp_cmnt(rd_img);
    if(fscanf(rd_img, "%d", max_val));
    fclose(rd_img);	
	return;
}

// Read RGB PPM image details
void rd_rgb_ppm(unsigned int ***in, unsigned int subj, unsigned int inst, unsigned int *height, 
				unsigned int *width, unsigned int *max_val) {
	unsigned int c, x, y;
	unsigned int ch = 3;
	char FN[100], ver[3];
	FILE *rd_img;
	sprintf(FN, "%s%d%s%d%s", "face_", subj, "_", inst, ".ppm");	
	rd_img = fopen(FN, "rb");
	if (rd_img == NULL) {
		printf("Failed to open file: %s\n", FN);
		exit(1);
	}
	// Check version
	if(fgets(ver, sizeof(ver), rd_img));
    if (strcmp(ver, "P6")) {
        fprintf(stderr, "Wrong file type!\n");
        exit(1);
    }
	// Read image details (height, width and maximum value)
	skp_cmnt(rd_img);
    if(fscanf(rd_img, "%d", width));
    skp_cmnt(rd_img);
    if(fscanf(rd_img, "%d", height));
    skp_cmnt(rd_img);
    if(fscanf(rd_img, "%d", max_val));
    fgetc(rd_img);
	for (x = 0 ; x < *height ; x++)
		for (y = 0 ; y < *width ; y++) 
			for (c = 0 ; c < ch ; c++) 
				in[x][y][c] = fgetc(rd_img);
	fclose(rd_img);	
	return;
}

// Write RGB PPM image
void wr_rgb_ppm(unsigned int ***in, unsigned int subj, unsigned int inst, unsigned int height, 
				unsigned int width, unsigned int max_val) {
	unsigned int c, x, y;
	unsigned int ch = 3;
	char FN[100];
	FILE *wr_img;
	sprintf(FN, "%s%d%s%d%s", "output_", subj, "_", inst, ".ppm");
	wr_img = fopen(FN, "wb");
	fprintf(wr_img, "P6\t%d\t%d\t%d\n", width, height, max_val);
	for (x = 0 ; x < height ; x++)
		for (y = 0 ; y < width ; y++)
			for (c = 0 ; c < ch ; c++)
				fputc(in[x][y][c], wr_img);
	fclose(wr_img);
	return;
}

// Write RGB PPM image (float)
void wr_rgb_ppm_float(float ***in, unsigned int subj, unsigned int inst, unsigned int height, 
					  unsigned int width, unsigned int max_val) {
	unsigned int c, x, y;
	unsigned int ch = 3;
	char FN[100];
	FILE *wr_img;
	sprintf(FN, "%s%d%s%d%s", "output_", subj, "_", inst, ".ppm");
	wr_img = fopen(FN, "wb");
	fprintf(wr_img, "P6\t%d\t%d\t%d\n", width, height, max_val);
	for (x = 0 ; x < height ; x++)
		for (y = 0 ; y < width ; y++)
			for (c = 0 ; c < ch ; c++)
				fputc((unsigned int)in[x][y][c], wr_img);
	fclose(wr_img);
	return;
}

// Write RGB PPM image (Mat data type)
void wr_rgb_ppm_mat(Mat in, unsigned int subj, unsigned int inst, unsigned int height, unsigned int width, 
					unsigned int max_val) {
	unsigned int c, x, y;
	unsigned int ch = 3;
	char FN[100];
	FILE *wr_img;
	sprintf(FN, "%s%d%s%d%s", "output_", subj, "_", inst, ".ppm");
	wr_img = fopen(FN, "wb");
	fprintf(wr_img, "P6\t%d\t%d\t%d\n", width, height, max_val);
	for (x = 0 ; x < height ; x++)
		for (y = 0 ; y < width ; y++)
			for (c = 0 ; c < ch ; c++)
				fputc((unsigned int)in.at<cv::Vec3b>(x, y)[ch - c - 1], wr_img);
	fclose(wr_img);
	return;
}

// Write RGB PPM image (Mat data type) //write images in sequence
void wr_rgb_ppm_mat_2(Mat in, unsigned int i, unsigned int height, unsigned int width, 
					unsigned int max_val) {
	unsigned int c, x, y;
	unsigned int ch = 3;
	char FN[100];
	FILE *wr_img;
	sprintf(FN, "./P1E_S4_C2_out/%04d%s", i , ".ppm");
	wr_img = fopen(FN, "wb");
	fprintf(wr_img, "P6\t%d\t%d\t%d\n", width, height, max_val);
	for (x = 0 ; x < height ; x++)
		for (y = 0 ; y < width ; y++)
			for (c = 0 ; c < ch ; c++)
				fputc((unsigned int)in.at<cv::Vec3b>(x, y)[ch - c - 1], wr_img);
	fclose(wr_img);
	return;
}


// Write grayscale PGM image
void wr_pgm(unsigned int **in, unsigned int subj, unsigned int inst, unsigned int height, unsigned int width, 
			unsigned int max_val)
{
	unsigned int x, y;
	char FN[200];
	FILE *wr_img;
	sprintf(FN, "%s%d%s%d%s", "output_", subj, "_", inst, ".pgm");
	wr_img = fopen(FN, "wb");
	fprintf(wr_img, "P5\t%d\t%d\t%d\n", width, height, max_val);
	for (x = 0 ; x < height ; x++)
		for (y = 0 ; y < width ; y++)
			fputc(in[x][y], wr_img);
	fclose(wr_img);	
	return;
}


// Write grayscale PGM image_second_version
void wr_pgm_2(unsigned char *in, unsigned int inst, unsigned int height, unsigned int width, 
			unsigned int max_val)
{
	unsigned int x, y;
	char FN[200];
	FILE *wr_img;
	sprintf(FN, "./train/%d%s", inst, ".pgm");
	wr_img = fopen(FN, "wb");
	fprintf(wr_img, "P5\t%d\t%d\t%d\n", width, height, max_val);
	for (y = 0 ; y < height ; y++)
		for (x = 0 ; x < width ; x++)
			fputc(in[y*width + x], wr_img);
	fclose(wr_img);	
	return;
}

// Write grayscale PGM image (float)
void wr_pgm_float(float **in, unsigned int subj, unsigned int inst, unsigned int height, unsigned int width, 
				  unsigned int max_val)
{
	unsigned int x, y;
	char FN[200];
	FILE *wr_img;
	sprintf(FN, "%s%d%s%d%s", "output_", subj, "_", inst, ".pgm");
	wr_img = fopen(FN, "wb");
	fprintf(wr_img, "P5\t%d\t%d\t%d\n", width, height, max_val);
	for (x = 0 ; x < height ; x++)
		for (y = 0 ; y < width ; y++)
			fputc((unsigned int)in[x][y], wr_img);
	fclose(wr_img);	
	return;
}

// Write text image
void wr_img_txt(unsigned int **in, unsigned int subj, unsigned int inst, unsigned int height, 
				unsigned int width) {
	unsigned int x, y;
	char FN[200];
	FILE *wr_img;
	sprintf(FN, "%s%d%s%d%s", "output_", subj, "_", inst, ".txt");
	wr_img = fopen(FN, "w");
	for (x = 0 ; x < height ; x++) {
		for (y = 0 ; y < width ; y++)
			fprintf(wr_img, "%d\t", in[x][y]);	
		fprintf(wr_img, "\n");
	}
	fclose(wr_img);	
	return;
}

// Write text image (float)
void wr_img_txt_float(float **in, unsigned int subj, unsigned int inst, unsigned int height, 
					  unsigned int width) {
	unsigned int x, y;
	char FN[200];
	FILE *wr_img;
	sprintf(FN, "%s%d%s%d%s", "output_", subj, "_", inst, ".txt");
	wr_img = fopen(FN, "w");
	for (x = 0 ; x < height ; x++) {
		for (y = 0 ; y < width ; y++)
			fprintf(wr_img, "%.2f\t", in[x][y]);	
		fprintf(wr_img, "\n");
	}
	fclose(wr_img);	
	return;
}

/* RGB to YCbCr conversion
   1st channel = Y
   2nd channel = Cb
   3rd channel = Cr
*/
void rgb_to_ycbcr(unsigned int ***in, float ***out, unsigned int height, unsigned int width) {
	for (unsigned int x = 0 ; x < height ; x++) {
		for (unsigned int y = 0 ; y < width ; y++) {
			out[x][y][0] = 0.257 * in[x][y][0] + 0.504 * in[x][y][1] + 0.098 * in[x][y][2] + 16;
			out[x][y][1] = -0.148 * in[x][y][0] - 0.291 * in[x][y][1] + 0.439 * in[x][y][2] + 128;
			out[x][y][2] = 0.439 * in[x][y][0] - 0.368 * in[x][y][1] - 0.071 * in[x][y][2] + 128;
		}
	}
	return;
}

// RGB to YCbCr converstion from Mat data type
void rgb_to_ycbcr_mat(Mat in, float ***out, unsigned int height, unsigned int width) {
	for (unsigned int x = 0 ; x < height ; x++) {
		for (unsigned int y = 0 ; y < width ; y++) {
			out[x][y][0] = 0.257 * in.at<cv::Vec3b>(x, y)[2] + 0.504 * in.at<cv::Vec3b>(x, y)[1] 
						   + 0.098 * in.at<cv::Vec3b>(x, y)[0] + 16;
			out[x][y][1] = -0.148 * in.at<cv::Vec3b>(x, y)[2] - 0.291 * in.at<cv::Vec3b>(x, y)[1] 
						   + 0.439 * in.at<cv::Vec3b>(x, y)[0] + 128;
			out[x][y][2] = 0.439 * in.at<cv::Vec3b>(x, y)[2] - 0.368 * in.at<cv::Vec3b>(x, y)[1] 
						   - 0.071 * in.at<cv::Vec3b>(x, y)[0] + 128;
		}
	}
	return;
}

/* Gaussian skin color segmentation
   1st channel = Y
   2nd channel = Cb
   3rd channel = Cr
*/
void gauss_skin_sgmnt(float ***in, float **out, unsigned int height, unsigned int width) {
	float Cb_m, Cr_m;
	for (unsigned int x = 0 ; x < height ; x++) {
		for (unsigned int y = 0 ; y < width ; y++) {
			Cr_m = in[x][y][2] - 150.3179;
			Cb_m = in[x][y][1] - 117.1057;
			out[x][y] = exp(-0.5 * (Cr_m * (149.6103 * Cr_m -18.2077 * Cb_m) + Cb_m * (-18.2077 * Cr_m + 250.2594 
							* Cb_m)) / 37109.8636);
		}
	}
	return;
}

// Probability density function (pdf) value scaling
void pdf_scale(float **in, unsigned int **out, unsigned int height, unsigned int width, unsigned int max_val) {
	unsigned int x, y;
	float pdf_max = 0;
	float pdf_min = max_val;
	for (x = 0 ; x < height ; x++) {
		for (y = 0 ; y < width ; y++) {
			if (in[x][y] > pdf_max)
				pdf_max = in[x][y];
			if (in[x][y] < pdf_min)
				pdf_min = in[x][y];
		}
	}
	for (x = 0 ; x < height ; x++)
		for (y = 0 ; y < width ; y++)
			out[x][y] = (unsigned int)(max_val * (in[x][y] - pdf_min) / (pdf_max - pdf_min));
	return;
}

// Grayscale image histogram
void hist_gray(unsigned int **in, unsigned int *hist, unsigned int *sum, unsigned int height, 
			   unsigned int width, unsigned int max_val) {
	unsigned int x, y;
	for (x = 0 ; x < height ; x++)
		for (y = 0 ; y < width ; y++)
			hist[in[x][y]]++;
	*sum = 0;
	for (x = 0 ; x < max_val + 1 ; x++) 
		*sum += x * hist[x];
	return;
}

// Threshold calculation
void calc_thres(unsigned int *hist, unsigned int sum, unsigned int *thres, unsigned int height, 
				unsigned int width, unsigned int max_val) {
	float m_B, m_F;
	float var, var_max = 0;
	float w_F, w_B = 0;
	unsigned int sum_B = 0;
	unsigned int hist_total = height * width;
	*thres = 0;
	for (unsigned int x = 0 ; x < max_val + 1 ; x++) {
		w_B += hist[x];
		if (w_B == 0)
			continue;
		w_F = hist_total - w_B;
		if (w_F == 0) 
			break;
		sum_B += x * hist[x];
		var = w_B * w_F * pow((sum_B / w_B - (sum - sum_B) / w_F), 2.0);
		if (var > var_max) {
			var_max = var;
			*thres = x;
		}	
	}
	return;
}

// Binarization
void binarize(unsigned int **in, unsigned int thres, unsigned int height, unsigned int width, unsigned max_val) {
	for (unsigned int x = 0 ; x < height ; x++) {
		for (unsigned int y = 0 ; y < width ; y++) {
			if (in[x][y] > thres)
				in[x][y] = max_val;
			else
				in[x][y] = 0;
		}
	}
	return;
}

// Median filtering
void median_filter(unsigned int **in, unsigned int **out, unsigned int height, unsigned int width, 
				   unsigned max_val) {
	unsigned int cnt_zero;
	for (unsigned int x = 1 ; x < height - 1 ; x++) {
		for (unsigned int y = 1 ; y < width - 1 ; y++) {
			cnt_zero = 0;
			for (unsigned int u = x - 1 ; u <= x + 1 ; u++)
				for (unsigned int v = y - 1 ; v <= y + 1 ; v++)
					if (in[u][v] == 0)
						cnt_zero++;
			if (cnt_zero > 4)
				out[x][y] = 0;
			else
				out[x][y] = max_val;
		}
	}
	return;
}

// Dilation filtering
void dilate_filter(unsigned int **in, unsigned int **out, unsigned int height, unsigned int width) {
	unsigned int d;
	for (unsigned int x = 1 ; x < height - 1 ; x++) {
		for (unsigned int y = 1 ; y < width - 1 ; y++) {
			d = 0;
			for (unsigned int u = x - 1 ; u <= x + 1 ; u++)
				for (unsigned int v = y - 1 ; v <= y + 1 ; v++)
					if (in[u][v] > d)
						d = in[u][v];
			out[x][y] = d;
		}
	}
	return;
}

// Erosion filtering
void erosion_filter(unsigned int **in, unsigned int **out, unsigned int height, unsigned int width, 
				   	unsigned max_val) {
	unsigned int e;
	for (unsigned int x = 1 ; x < height - 1 ; x++) {
		for (unsigned int y = 1 ; y < width - 1 ; y++) {
			e = max_val;
			for (unsigned int u = x - 1 ; u <= x + 1 ; u++)
				for (unsigned int v = y - 1 ; v <= y + 1 ; v++)
					if (in[u][v] < e)
						e = in[u][v];
			out[x][y] = e;
		}
	}
	return;
}

// Border clearing
void border_clr(unsigned int **in, unsigned int height, unsigned int width) {
	for (unsigned int y = 0 ; y < width ; y++) {
		in[0][y] = 0;
		in[height - 1][y] = 0;
	}
	for (unsigned int x = 1 ; x < height - 1 ; x++) {
		in[x][0] = 0;
		in[x][width - 1] = 0;
	}
	return;
}

// Hole filling
void hole_fill(unsigned int **in, unsigned int **out, unsigned int height, unsigned int width) {
	for (unsigned int x = 1 ; x < height - 1 ; x++) {
		for (unsigned int y = 1 ; y < width - 1 ; y++) {
			if (in[x - 1][y] && (in[x][y - 1] || in[x][y + 1]))
				out[x][y] = 1;
			else
				out[x][y] = in[x][y];
		}
	}
	return;
}

// Connected component labeling
void ccl(unsigned int **in, unsigned int *xbox_max, unsigned int *xbox_min, unsigned int *ybox_max, 
		 unsigned int *ybox_min, unsigned int height, unsigned int width) {
	unsigned int Ec, Ep, Ovrlp, i, loc, max;
	unsigned int max_label = width / 2;
	unsigned int max_obj = height * width / 2;
	unsigned int c = 0, f = 0, h = 0, p = 0, total = 0;
	unsigned int Rx_max = 0, Rx_min = height, Ry_max = 0, Ry_min = width;
	unsigned int head[max_label], next[max_label], tail[max_label];
	unsigned int Tx_max[max_label], Tx_min[max_label], Ty_max[max_label], Ty_min[max_label];
	unsigned int x_max[max_obj], x_min[max_obj], y_max[max_obj], y_min[max_obj], area[max_obj];
	// Equivalence resolving and feature collection
	for (unsigned int x = 1 ; x < height ; x++) {
		for (unsigned int y = 1 ; y < width ; y++) {
			Ec = in[x][y - 1] && !(in[x][y]);
			Ep = in[x - 1][y - 1] && !(in[x - 1][y]);
			Ovrlp = in[x - 1][y] && in[x][y] && (!(in[x - 1][y - 1]) || !(in[x][y - 1]));
			if (Ec) {
				i = f ? h : c;
				Tx_max[i] = Rx_max;
				Tx_min[i] = Rx_min;
				Ty_max[i] = Ry_max;
				Ty_min[i] = Ry_min;
				head[c] = c;
				next[c] = c;
				f = 0;
				Rx_max = 0;
				Rx_min = height;
				Ry_max = 0;
				Ry_min = width;
				if (++c > max_label)
					c = 0;
			}
			else if (Ep) {
				if (head[p] != p)
					head[next[p]] = head[p];
				else if (next[p] != p) {
					Tx_max[next[p]] = Tx_max[p];
					Tx_min[next[p]] = Tx_min[p];
					Ty_max[next[p]] = Ty_max[p];
					Ty_min[next[p]] = Ty_min[p];
				}
				else {
					x_max[total] = Tx_max[head[p]];
					x_min[total] = Tx_min[head[p]];
					y_max[total] = Ty_max[head[p]];
					y_min[total] = Ty_min[head[p]];
					total++;
				}
			}
			else if (Ovrlp) {
				if (head[p] != p) {
					if (f) {
						if (head[p] == h) {
							Rx_min = (x < Rx_min) ? x : Rx_min;
							Ry_max = (y > Ry_max) ? y : Ry_max;
							Ry_min = (y < Ry_min) ? y : Ry_min;	
						}
						else {
							Rx_min = (Tx_min[head[p]] < Rx_min) ? Tx_min[head[p]] : Rx_min;
							Ry_max = (Ty_max[head[p]] > Ry_max) ? Ty_max[head[p]] : Ry_max;						
							Ry_min = (Ty_min[head[p]] < Ry_min) ? Ty_min[head[p]] : Ry_min;
						}
						i = h;
					}
					else {
						Rx_min = (Tx_min[head[p]] < Rx_min) ? Tx_min[head[p]] : Rx_min;	
						Ry_max = (Ty_max[head[p]] > Ry_max) ? Ty_max[head[p]] : Ry_max;						
						Ry_min = (Ty_min[head[p]] < Ry_min) ? Ty_min[head[p]] : Ry_min;
						i = c;
					}
					Rx_max = x;
					f = 1;
					next[tail[head[p]]] = i;
					head[next[p]] = head[p];
					tail[head[p]] = c;
					h = head[p];
				}
				else {
					Rx_max = x;
					Rx_min = (Tx_min[head[p]] < Rx_min) ? Tx_min[head[p]] : Rx_min;
					Ry_max = (Ty_max[head[p]] > Ry_max) ? Ty_max[head[p]] : Ry_max;						
					Ry_min = (Ty_min[head[p]] < Ry_min) ? Ty_min[head[p]] : Ry_min;	
					if (f)
						i = h;
					else {
						i = c;
						h = c;
					}
					head[p] = i;
					head[next[p]] = i;
					tail[i] = c;
					f = 1;
				}
			}
			else if (in[x][y]) {
				Rx_max = x;
				Rx_min = (x < Rx_min) ? x : Rx_min;
				Ry_max = (y > Ry_max) ? y : Ry_max;
				Ry_min = (y < Ry_min) ? y : Ry_min;				
			}
			if (Ep && ((++p) > max_label))
				p = 0;
		}		
	}
	// Find box with biggest area
	for (i = 0 ; i < total ; i++)
		area[i] = (x_max[i] - x_min[i]) * (y_max[i] - y_min[i]);
	max = area[0];
	for (i = 1 ; i < total ; i++) {
		if (area[i] > max) {
			max = area[i];
			loc = i;
		}
	}
	*xbox_max = x_max[loc];
	*xbox_min = x_min[loc];
	*ybox_max = y_max[loc];
	*ybox_min = y_min[loc];
	return;
}

// Draw box in RGB image
void draw_box_rgb(unsigned int ***in, unsigned int x_max, unsigned int x_min, unsigned int y_max, 
				  unsigned int y_min, unsigned int height, unsigned int width) {
	for (unsigned int y = y_min ; y < y_max + 1 ; y++) {
		in[x_min][y][0] = 0;
		in[x_min][y][1] = 255;
		in[x_min][y][2] = 0;
		in[x_max][y][0] = 0;
		in[x_max][y][1] = 255;
		in[x_max][y][2] = 0;
	}
	for (unsigned int x = x_min + 1 ; x < x_max ; x++) {
		in[x][y_min][0] = 0;
		in[x][y_min][1] = 255;
		in[x][y_min][2] = 0;
		in[x][y_max][0] = 0;
		in[x][y_max][1] = 255;
		in[x][y_max][2] = 0;
	}
	return;
}

// Draw box in RGB image (Mat data type)
void draw_box_rgb_mat(Mat in, unsigned int x_max, unsigned int x_min, unsigned int y_max, unsigned int y_min, 
					  unsigned int height, unsigned int width) {

	for (unsigned int y = y_min ; y < y_max+1 ; y++) {
		in.at<cv::Vec3b>(y, x_min)[0] = 0;
		in.at<cv::Vec3b>(y, x_min)[1] = 255;
		in.at<cv::Vec3b>(y, x_min)[2] = 0;
		in.at<cv::Vec3b>(y, x_max)[0] = 0;
		in.at<cv::Vec3b>(y, x_max)[1] = 255;
		in.at<cv::Vec3b>(y, x_max)[2] = 0;
	}
	for (unsigned int x = x_min ; x < x_max+1 ; x++) {
		in.at<cv::Vec3b>(y_min,x)[0] = 0;
		in.at<cv::Vec3b>(y_min,x)[1] = 255;
		in.at<cv::Vec3b>(y_min,x)[2] = 0;
		in.at<cv::Vec3b>(y_max,x)[0] = 0;
		in.at<cv::Vec3b>(y_max,x)[1] = 255;
		in.at<cv::Vec3b>(y_max,x)[2] = 0;
	}
	return;
}


#endif
