#include <stdio.h>
#include <stdlib.h>

typedef struct point
{
	float x;
	float y;
} Point;
typedef struct square
{
	Point center;
	float length;
} Square;
typedef struct map
{
	Point min;
	Point max;
	int numSquares;
	Square* squares;
} Map;

int** qdDecomp(Map* map);
Map * makeMap(char* filename);
void printMap(Map * map);

int main(int argc, char** args)
{
	Map* map = makeMap("map.txt");
	printMap(map);
}

int** qdDecomp(Map* map)
{
	return NULL;
}

Map * makeMap(char* filename)
{
	FILE *fp;
	fp = fopen(filename, "r+");
	float num;
	

	Map* map = (Map *)malloc(sizeof(Map));
	
	fscanf(fp, "%f", &num);
	map->min.x = num;
	fscanf(fp, "%f", &num);
	map->max.x = num;
	fscanf(fp, "%f", &num);
	map->min.y = num;
	fscanf(fp, "%f", &num);
	map->max.y = num;
	fscanf(fp, "%f", &num);
	map->numSquares = (int)num;

	map->squares = (Square *)malloc(map->numSquares*sizeof(Square));
	int count = 0;
	while (!feof(fp) && count < map->numSquares)
	{
		fscanf(fp, "%f", &num);
		map->squares[count].center.x = num;
		fscanf(fp, "%f", &num);
		map->squares[count].center.y = num;
		fscanf(fp, "%f", &num);
		map->squares[count].length = num;
		count++;
	}
	return map;
}
void printMap(Map * map)
{
	printf("Min Coords: (%f,%f)\n", map->min.x, map->min.y);
	printf("Max Coords: (%f,%f)\n", map->max.x, map->max.y);
	printf("# of squares: %d\n", map->numSquares);
	for (int i = 0; i < map->numSquares; i++)
	{
		printf("Center Coord: (%f,%f)\n", map->squares[i].center.x, map->squares[i].center.y);
		printf("Length: %f\n", map->squares[i].length);
	}
}

