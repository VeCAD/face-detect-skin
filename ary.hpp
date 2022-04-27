#ifndef ARY_HPP
#define ARY_HPP

// Allocate unsigned int 1D array 
unsigned int *new_uint_1D(unsigned int first_dim) {
	unsigned int i;
	unsigned int *ary_1D = new unsigned int [first_dim];
	for (i = 0 ; i < first_dim ; i++)
		ary_1D[i] = 0;
	return ary_1D;
}

// Allocate unsigned int 2D array 
unsigned int **new_uint_2D(unsigned int first_dim, unsigned int second_dim) {
	unsigned int i, j;
	unsigned int **ary_2D = new unsigned int *[first_dim];
	unsigned int *ary_1D = new unsigned int [first_dim * second_dim];
	for (i = 0 ; i < first_dim ; i++, ary_1D += second_dim)
		ary_2D[i] = ary_1D;
	for (i = 0 ; i < first_dim ; i++)
		for (j = 0 ; j < second_dim ; j++)
			ary_2D[i][j] = 0;
	return ary_2D;
}

// Allocate unsigned int 3D array
unsigned int ***new_uint_3D(unsigned int first_dim, unsigned int second_dim, unsigned int third_dim) {
	unsigned int i, j, k;
	unsigned int ***ary_3D = new unsigned int **[first_dim];
	unsigned int **ary_2D = new unsigned int *[first_dim * second_dim];
	unsigned int *ary_1D = new unsigned int [first_dim * second_dim * third_dim];
	for (i = 0 ; i < first_dim ; i++, ary_2D += second_dim) {
		ary_3D[i] = ary_2D;
		for (j = 0 ; j < second_dim ; j++, ary_1D += third_dim)
			ary_3D[i][j] = ary_1D;
	}
	for (i = 0 ; i < first_dim ; i++)
		for (j = 0 ; j < second_dim ; j++)
			for (k = 0 ; k < third_dim ; k++)
				ary_3D[i][j][k] = 0;	
	return ary_3D;
}

// Allocate float 2D array
float **new_float_2D(unsigned int first_dim, unsigned int second_dim) {
	unsigned int i, j;
	float **ary_2D = new float *[first_dim];
	float *ary_1D = new float [first_dim * second_dim];
	for (i = 0 ; i < first_dim ; i++, ary_1D += second_dim)
		ary_2D[i] = ary_1D;
	for (i = 0 ; i < first_dim ; i++)
		for (j = 0 ; j < second_dim ; j++)
			ary_2D[i][j] = 0.0;
	return ary_2D;
}

// Allocate float 3D array
float ***new_float_3D(unsigned int first_dim, unsigned int second_dim, unsigned int third_dim) {
	unsigned int i, j, k;
	float ***ary_3D = new float **[first_dim];
	float **ary_2D = new float *[first_dim * second_dim];
	float *ary_1D = new float [first_dim * second_dim * third_dim];
	for (i = 0 ; i < first_dim ; i++, ary_2D += second_dim) {
		ary_3D[i] = ary_2D;
		for (j = 0 ; j < second_dim ; j++, ary_1D += third_dim)
			ary_3D[i][j] = ary_1D;
	}
	for (i = 0 ; i < first_dim ; i++)
		for (j = 0 ; j < second_dim ; j++)
			for (k = 0 ; k < third_dim ; k++)
				ary_3D[i][j][k] = 0.0;
	return ary_3D;
}

// Deallocate unsigned int 1D pointer
void del_uint_1D(unsigned int *ptr) {
	delete [] ptr;
	delete ptr;
	return;
}

// Deallocate unsigned int 2D pointer
void del_uint_2D(unsigned int **ptr) {
	delete [] ptr[0];
	delete [] ptr;
	delete ptr;
	return;
}

// Deallocate unsigned int 3D pointer 
void del_uint_3D(unsigned int ***ptr) {
	delete [] ptr[0][0];
	delete [] ptr[0];
	delete [] ptr;
	delete ptr;
	return;
}

// Deallocate float 2D pointer
void del_float_2D(float **ptr) {
	delete [] ptr[0];
	delete [] ptr;
	delete ptr;
	return;
}

// Deallocate float 3D pointer
void del_float_3D(float ***ptr) {
	delete [] ptr[0][0];
	delete [] ptr[0];
	delete [] ptr;
	delete ptr;
	return;
}

#endif
