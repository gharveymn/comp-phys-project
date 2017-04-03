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
	float width;
} Square;
typedef struct map
{
	Point min;
	Point max;
	int numSquares;
	Square* squares;
} Map;
typedef struct node
{
	struct node* tl_child;
	struct node* tr_child;
	struct node* bl_child;
	struct node* br_child;
	int depth;
} Node;
typedef struct queue
{
	Node* front;
	int length;
}Queue;


void makeQT(Node* curr, Map* map, Point loc, float l, float w);
char contains_object(Map* map, Point loc, float l, float w);
Map * makeMap(char* filename);
void printMap(Map * map);
void outputTree(Node* node, FILE *fp, Point point, float l, float w);

//Maximum depth of the quadtree
const int qt_threshold = 7;

int main(int argc, char** args)
{
	Map* map = makeMap("map.txt");
	printMap(map);
	Node* root = (Node *)malloc(sizeof(Node));
	root->depth = 0;
	makeQT(root, map, map->min, map->max.x - map->min.x, map->max.y - map->min.y);

	FILE* fp = fopen("tree.txt", "w+");
	outputTree(root, fp, map->min, map->max.x - map->min.x, map->max.y - map->min.y);
	fclose(fp);
}

void makeQT(Node* curr, Map* map, Point loc, float l, float w)
{
	if (curr->depth == qt_threshold)
	{
		curr->tl_child = NULL;
		curr->tr_child = NULL;
		curr->bl_child = NULL;
		curr->br_child = NULL;
		return;
	}

	if (contains_object(map, loc, l, w))
	{
		//Top left child
		curr->tl_child = (Node *)malloc(sizeof(Node));
		curr->tl_child->depth = curr->depth + 1;
		Point tl_loc;
		tl_loc.x = loc.x;
		tl_loc.y = loc.y + w/2;
		makeQT(curr->tl_child, map, tl_loc, l/2, w/2);

		//Top right child
		curr->tr_child = (Node *)malloc(sizeof(Node));
		curr->tr_child->depth = curr->depth + 1;
		Point tr_loc;
		tr_loc.x = loc.x + l/2;
		tr_loc.y = loc.y + w/2;
		makeQT(curr->tr_child, map, tr_loc, l/2, w/2);

		//Bottom left child
		curr->bl_child = (Node *)malloc(sizeof(Node));
		curr->bl_child->depth = curr->depth + 1;
		Point bl_loc;
		bl_loc.x = loc.x;
		bl_loc.y = loc.y;
		makeQT(curr->bl_child, map, bl_loc, l/2, w/2);

		//Bottom right child
		curr->br_child = (Node *)malloc(sizeof(Node));
		curr->br_child->depth = curr->depth + 1;
		Point br_loc;
		br_loc.x = loc.x + l/2;
		br_loc.y = loc.y;
		makeQT(curr->br_child, map, br_loc, l/2, w/2);
	}
	else
	{
		curr->tl_child = NULL;
		curr->tr_child = NULL;
		curr->bl_child = NULL;
		curr->br_child = NULL;
	}
}
char contains_object(Map* map, Point loc, float l, float w)
{
	char leftBounded;
	char rightBounded;
	char topBounded;
	char bottomBounded;
	Point obj_min;
	Point obj_max;
	Square curr;
	for (int i = 0; i < map->numSquares; i++)
	{
		curr = map->squares[i];
		obj_max.x = curr.center.x + curr.length/2;
		obj_max.y = curr.center.y + curr.width/2;
		obj_min.x = curr.center.x - curr.length/2;
		obj_min.y = curr.center.y - curr.width/2;
		
		//left bounded?
		if (obj_min.x >= loc.x && obj_min.x <= loc.x + l)
		{
			if(obj_max.y >= loc.y + w && obj_min.y <= loc.y + w)
			{
				leftBounded = 1;
			}
			else if (obj_min.y <= loc.y && obj_max.y >= loc.y)
			{
				leftBounded = 1;
			}
			else if (obj_min.y >= loc.y && obj_max.y <= loc.y + w)
			{
				leftBounded = 1;
			}
		}
		//right bounded?
		else if (obj_max.x >= loc.x && obj_max.x <= loc.x + l)
		{
			if(obj_max.y >= loc.y + w && obj_min.y <= loc.y + w)
			{
				rightBounded = 1;
			}
			else if (obj_min.y <= loc.y && obj_max.y >= loc.y)
			{
				rightBounded = 1;
			}
			else if (obj_min.y >= loc.y && obj_max.y <= loc.y + w)
			{
				rightBounded = 1;
			}
		}
		//top bounded?
		else if (obj_max.y >= loc.y && obj_max.y <= loc.y + w)
		{
			if (obj_min.x <= loc.x && obj_max.x >= loc.x)
			{
				topBounded = 1;
			}
			else if (obj_max.x >= loc.x + l && obj_min.x <= loc.x + l)
			{
				topBounded = 1;
			}
			else if (obj_min.x >= loc.x && obj_max.x <= loc.x + l)
			{
				topBounded = 1;
			}
		}
		//bottom bounded?
		else if (obj_min.y >= loc.y && obj_min.y <= loc.y + w)
		{
			if (obj_min.x <= loc.x && obj_max.x >= loc.x)
			{
				bottomBounded = 1;
			}
			else if (obj_max.x >= loc.x + l && obj_min.x <= loc.x + l)
			{
				bottomBounded = 1;
			}
			else if (obj_min.x >= loc.x && obj_max.x <= loc.x + l)
			{
				bottomBounded = 1;
			}
		}
	}
	if (leftBounded || rightBounded || topBounded || bottomBounded)
	{
		return 1;
	}
	return 0;
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
		map->squares[count].width = num; //FOR NOW ASSUME SQUARE OBSTACLES
		count++;
	}
	fclose(fp);
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
		//printf("Width: %f\n", map->squares[i].width);
	}
}
void outputTree(Node* node, FILE *fp, Point point, float l, float w)
{
	if (node == NULL)
	{
		return;
	}
	if (node->tl_child != NULL)
	{
		Point newPoint;

		newPoint.x = point.x;
		newPoint.y = point.y + l/2;
		outputTree(node->tl_child, fp, newPoint, l/2, w/2);

		newPoint.x = point.x + l/2;
		newPoint.y = point.y + l/2;
		outputTree(node->tr_child, fp, newPoint, l/2, w/2);

		newPoint.x = point.x;
		newPoint.y = point.y;
		outputTree(node->bl_child, fp, newPoint, l/2, w/2);

		newPoint.x = point.x + l/2;
		newPoint.y = point.y;
		outputTree(node->br_child, fp, newPoint, l/2, w/2);
	}
	else
	{
		fprintf(fp, "%f %f %f %f\n", point.x, point.y, l, w);
	}
}

