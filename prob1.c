#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define row 3
#define col 5
#define h 0.5
#define error 1e-10
#define x0 0
#define x1 1
#define y0 0
#define y1 2

void contouring (double **matrix) {
	int i, j;
	double x = x0, y = y0;
	for (i = 0; i<row; i++ ) {
		matrix[i][0] = pow(x,2);	
		matrix[i][col-1] = pow(x-2,2);
		x += h;
	}
	for (j=0; j<col; j++) {
		matrix[0][j] = pow(y,2);	
		matrix[row-1][j] = pow(y-1,2);
		y += h;
	}
}


double f () {
	return 4;
}

double pde (double **matrix) {
	int i, j;
	double temp, t=0;
	for(i=1;i<row-1;i++) {
		for(j=1;j<col;j++) {
				temp = matrix[i][j];
				matrix[i][j] = (matrix[i-1][j] + matrix[i+1][j] + matrix[i][j-1] + matrix[i][j+1] - pow(h,2)*f(0))/4;
				temp = fabs(temp-matrix[i][j]);
				if(temp>t)
					t = temp;
		}
	}
	return t;	
}


void print (double **matrix) {
	int i, j;
    FILE *f;
	f = fopen("prob1.dat", "w+");
	printf("\nMatriz: \n");
	for(i=0;i<row;i++) {
		for(j=0;j<col;j++) { 
			printf("%5.2lf\t",matrix[i][j]);
            fprintf(f, "%lf\t", matrix[i][j]);
		}	 
        fprintf(f,"\n"); 
		printf("\n");
	}
	printf("\n");
    fclose(f);
}


void main() {
	double	**matrix, er;
	int  i, j;
	matrix = malloc(row*sizeof(double*));
	for( i = 0; i < col; i++ )
		matrix[i] = malloc(col*sizeof(double));		
	contouring(matrix);		
	do {
		er = pde(matrix);
	} while (er > error);
	print(matrix);
}