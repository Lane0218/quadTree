#include "Gaussian_blur.h"
#include "Average_blur.h"

void readImage(char *inFile);
void printImage(char *outFile);

int main(int argc, char **argv)
{
	char *inFile, *outFile1, *outFile2;
	if (argc == 5)
	{
		tolerance = atoi(argv[1]);
		inFile = argv[2];
		outFile1 = argv[3];
		outFile2 = argv[4];

		readImage(inFile);

		Gaussian_blur();
		printImage(outFile1);

		Average_blur();
		printImage(outFile2);
	}
	else
		cout << "Please input tolerance,inFile path and two outFile paths for Gaussian blur result and Average blur result" << endl;
	return 0;
}

void readImage(char *inFile)
{
	FILE *f = fopen(inFile, "rb");
	char u[3];
	int max_value;
	fscanf(f, "%s\n%d %d\n%d\n", u, &sideLength, &sideLength, &max_value);
	for (int i = 0; i < sideLength; i++)
		for (int j = 0; j < sideLength; j++)
			fread(&(ori_colors[i][j]), sizeof(color), 1, f);
	fclose(f);
}

void printImage(char *outFile)
{
	FILE *f = fopen(outFile, "wb");
	fprintf(f, "P6\n");
	fprintf(f, "%d %d\n", sideLength, sideLength);
	fprintf(f, "255\n");
	for (int i = 0; i < sideLength; i++)
		for (int j = 0; j < sideLength; j++)
			fwrite(&(res_colors[i][j]), sizeof(color), 1, f);
	fclose(f);
}