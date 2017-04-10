#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3
#define ROOT 4

typedef enum 
{
	FALSE,
	TRUE
} bool;

typedef struct point
{
	float x;
	float y;
} Point;
typedef struct square
{
	Point corner;
	float l;
	float w;
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
	struct node* parent;
	struct node* children[4];
	struct node* adjacency_list[8];
	int depth;
	int num_adjacent;
	bool contains_object;
	Square square;
} Node;

Node* initializeNode(Square area, Node* parent, int depth, int cardinality);
void makeQT(Node* curr, Map* map, Node** children);
char contains_object(Map* map, Square area);
Map * makeMap(char* filename);
void makeAdjacencyLists(Map* map, int max_children, Node** children);
void printMap(Map * map);
void outputTree(Node* node, FILE *fp, Square area);
void freeTree(Node* node);
bool shares_edge(Node* node1, Node* node2);

//Maximum depth of the quadtree
const int qt_threshold = 7;
int num_children;

int main(int argc, char** args)
{
	clock_t start = clock();
	int max_children = pow(4, qt_threshold);
	num_children = 0;
	Node* children[max_children];

	for (int i = 0; i < max_children; i++)
	{
		children[i] = (Node *)malloc(max_children*sizeof(Node));
	}

	Map* map = makeMap("map.txt");
	printMap(map);
	
	Square root_area;
	root_area.corner.x = map->min.x;
	root_area.corner.y = map->min.y;
	root_area.l = map->max.x - map->min.x;
	root_area.w = map->max.y - map->min.y;
	Node* root = initializeNode(root_area, NULL, 0, ROOT);
	
	makeQT(root, map, children);
	makeAdjacencyLists(map, max_children, children);

	FILE* fp = fopen("tree.txt", "w");
	outputTree(root, fp, root->square);
	fclose(fp);
	free(map);
	freeTree(root);

	clock_t end = clock();
	float exec_time = (float)(end - start)/CLOCKS_PER_SEC;
	printf("Graph Generation Complete after %f seconds.\n", exec_time);
}

Node* initializeNode(Square area, Node* parent, int depth, int cardinality)
{
	float l = area.l;
	float w = area.w;
	Node* ret = (Node *)malloc(sizeof(Node));
	ret->parent = parent;
	ret->depth = depth;
	ret->num_adjacent = 0;

	//initialize adjacency list
	for (int j = 0; j < 8; j++)
	{
		ret->adjacency_list[j] = (Node *)malloc(sizeof(Node));
	}

	if (cardinality == TOP_LEFT)
	{
		//Top left child
		Point tl_loc;
		tl_loc.x = area.corner.x;
		tl_loc.y = area.corner.y + w/2;

		Square tl_area;
		tl_area.corner = tl_loc;
		tl_area.l = l/2;
		tl_area.w = w/2;
		ret->square = tl_area;
	}
	else if (cardinality == TOP_RIGHT)
	{
		//Top right child
		Point tr_loc;
		tr_loc.x = area.corner.x + l/2;
		tr_loc.y = area.corner.y + w/2;

		Square tr_area;
		tr_area.corner = tr_loc;
		tr_area.l = l/2;
		tr_area.w = w/2;
		ret->square = tr_area;
	}
	else if (cardinality == BOTTOM_LEFT)
	{
		//Bottom left child
		Point bl_loc;
		bl_loc.x = area.corner.x;
		bl_loc.y = area.corner.y;

		Square bl_area;
		bl_area.corner = bl_loc;
		bl_area.l = l/2;
		bl_area.w = w/2;
		ret->square = bl_area;
	}
	else if (cardinality == BOTTOM_RIGHT)
	{
		//Bottom right child
		Point br_loc;
		br_loc.x = area.corner.x + l/2;
		br_loc.y = area.corner.y;

		Square br_area;
		br_area.corner = br_loc;
		br_area.l = l/2;
		br_area.w = w/2;
		ret->square = br_area;
	}
	else if (cardinality == ROOT)
	{
		ret->square = area;
	}
	return ret; 
}

void makeQT(Node* curr, Map* map, Node** children)
{
	if (curr->depth == qt_threshold)
	{
		//Tree is deep enough, quit dividing
		for (int i = 0; i < 4; i++)
		{
			curr->children[i] = NULL;
		}
		children[num_children] = curr;
		num_children++;
		return;
	}

	if (contains_object(map, curr->square))
	{
		curr->contains_object = 1;

		for (int i = 0; i < 4; i++)
		{
			curr->children[i] = initializeNode(curr->square, curr, curr->depth + 1, i);
		}

		//Top left child
		makeQT(curr->children[TOP_LEFT], map, children);

		//Top right child
		makeQT(curr->children[TOP_RIGHT], map, children);

		//Bottom left child
		makeQT(curr->children[BOTTOM_LEFT], map, children);

		//Bottom right child
		makeQT(curr->children[BOTTOM_RIGHT], map, children);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			curr->children[i] = NULL;
		}
	}
}
/*contains_object checks if a given area contains an object
Params:
@map holds info about all the objects
@loc has fields loc.x and loc.y that are the x and y values for the bottom right corner of the area we are checking
@l is the length (in x direction) of the area
@w is the width (y direction) of the area
*/
char contains_object(Map* map, Square area)
{
	bool leftBounded = FALSE;
	bool rightBounded = FALSE;
	bool topBounded = FALSE;
	bool bottomBounded = FALSE;
	float l = area.l;
	float w = area.w;
	//obj_max and obj_min are two points that describe the location of an object.
	//obj_max.x and obj_max.y are the x and y values of the top right corner of the object
	//obj_min.x and obj_min.y are the x and y values of the bottom left corner of the object
	Point obj_min;
	Point obj_max;
	Square curr;
	for (int i = 0; i < map->numSquares; i++)
	{
		curr = map->squares[i];
		obj_max.x = curr.corner.x + curr.l;
		obj_max.y = curr.corner.y + curr.w;
		obj_min.x = curr.corner.x;
		obj_min.y = curr.corner.y;
		
		//Check if the left side is bounded by the area
		if (obj_min.x >= area.corner.x && obj_min.x <= area.corner.x + l)
		{
			if(obj_max.y >= area.corner.y + w && obj_min.y <= area.corner.y + w)
			{
				leftBounded = TRUE;
				break;
			}
			else if (obj_min.y <= area.corner.y && obj_max.y >= area.corner.y)
			{
				leftBounded = TRUE;
			}
			else if (obj_min.y >= area.corner.y && obj_max.y <= area.corner.y + w)
			{
				leftBounded = TRUE;
			}
		}
		//Check if the right side is bounded by the area
		else if (obj_max.x >= area.corner.x && obj_max.x <= area.corner.x + l)
		{
			if(obj_max.y >= area.corner.y + w && obj_min.y <= area.corner.y + w)
			{
				rightBounded = TRUE;
			}
			else if (obj_min.y <= area.corner.y && obj_max.y >= area.corner.y)
			{
				rightBounded = TRUE;
			}
			else if (obj_min.y >= area.corner.y && obj_max.y <= area.corner.y + w)
			{
				rightBounded = TRUE;
			}
		}
		//Check if the top side is bounded by the area
		else if (obj_max.y >= area.corner.y && obj_max.y <= area.corner.y + w)
		{
			if (obj_min.x <= area.corner.x && obj_max.x >= area.corner.x)
			{
				topBounded = TRUE;
			}
			else if (obj_max.x >= area.corner.x + l && obj_min.x <= area.corner.x + l)
			{
				topBounded = TRUE;
			}
			else if (obj_min.x >= area.corner.x && obj_max.x <= area.corner.x + l)
			{
				topBounded = TRUE;
			}
		}
		//Check if the bottom side is bounded by the area
		else if (obj_min.y >= area.corner.y && obj_min.y <= area.corner.y + w)
		{
			if (obj_min.x <= area.corner.x && obj_max.x >= area.corner.x)
			{
				bottomBounded = TRUE;
			}
			else if (obj_max.x >= area.corner.x + l && obj_min.x <= area.corner.x + l)
			{
				bottomBounded = TRUE;
			}
			else if (obj_min.x >= area.corner.x && obj_max.x <= area.corner.x + l)
			{
				bottomBounded = TRUE;
			}
		}
	}
	return leftBounded || rightBounded || topBounded || bottomBounded;
	
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
		map->squares[count].corner.x = num;
		fscanf(fp, "%f", &num);
		map->squares[count].corner.y = num;
		fscanf(fp, "%f", &num);
		map->squares[count].l = num;
		map->squares[count].w = num; //FOR NOW ASSUME SQUARE OBSTACLES
		count++;
	}
	fclose(fp);
	return map;
}
void makeAdjacencyLists(Map* map, int max_children, Node** children)
{
	for (int i = 0; i < num_children; i++)
	{
		for (int j = 0; j < num_children; j++)
		{
			if (j != i && shares_edge(children[i], children[j]) && !contains_object(map, children[j]->square))
			{
				children[i]->adjacency_list[children[i]->num_adjacent] = children[j];
				children[i]->num_adjacent++;
			}
		}
	}
}
void printMap(Map * map)
{
	printf("Min Coords: (%f,%f)\n", map->min.x, map->min.y);
	printf("Max Coords: (%f,%f)\n", map->max.x, map->max.y);
	printf("# of squares: %d\n", map->numSquares);
	for (int i = 0; i < map->numSquares; i++)
	{
		printf("Corner Coord: (%f,%f)\n", map->squares[i].corner.x, map->squares[i].corner.y);
		printf("Length: %f\n", map->squares[i].l);
		//printf("Width: %f\n", map->squares[i].w);
	}
}
void outputTree(Node* node, FILE *fp, Square area)
{
	if (node == NULL)
	{
		return;
	}
	if (node->children[0] != NULL)
	{
		Square newArea;
		float l = area.l;
		float w = area.w;

		newArea.l = l/2;
		newArea.w = w/2;

		newArea.corner.x = area.corner.x;
		newArea.corner.y = area.corner.y + l/2;
		outputTree(node->children[TOP_LEFT], fp, newArea);

		newArea.corner.x = area.corner.x + l/2;
		newArea.corner.y = area.corner.y + l/2;
		outputTree(node->children[TOP_RIGHT], fp, newArea);

		newArea.corner.x = area.corner.x;
		newArea.corner.y = area.corner.y;
		outputTree(node->children[BOTTOM_LEFT], fp, newArea);

		newArea.corner.x = area.corner.x + area.l/2;
		newArea.corner.y = area.corner.y;
		outputTree(node->children[BOTTOM_RIGHT], fp, newArea);
	}
	else
	{
		//Print info for all the deepest children of the tree, the higher up children don't matter for visualization
		fprintf(fp, "%f %f %f %f\n", area.corner.x, area.corner.y, area.l, area.w);
		//node info followed by number of adjacent nodes on next line
		//Then node info (one node per line) for all adjacent nodes
		fprintf(fp, "%d\n", node->num_adjacent);
		for (int i = 0; i < node->num_adjacent; i++)
		{
			fprintf(fp, "%f %f %f %f\n", node->adjacency_list[i]->square.corner.x, node->adjacency_list[i]->square.corner.y, node->adjacency_list[i]->square.l, node->adjacency_list[i]->square.w);
		}
	}
}
bool shares_edge(Node* node1, Node* node2)
{
	bool has_shared_edge = FALSE;

	float top1 = node1->square.corner.y + node1->square.w;
	float top2 = node2->square.corner.y + node2->square.w;
	float bottom1 = node1->square.corner.y;
	float bottom2 = node2->square.corner.y;
	float left1 = node1->square.corner.x;
	float left2 = node2->square.corner.x;
	float right1 = node1->square.corner.x + node1->square.l;
	float right2 = node2->square.corner.x + node2->square.l;

	if (bottom1 == top2 || top1 == bottom2)
	{
		if (node1->square.l <= node2->square.l)
		{
			if (left1 >= left2 && right1 <= right2)
			{
				has_shared_edge = TRUE;
			}
		}
		else if (node2->square.l < node1->square.l)
		{
			if (left2 >= left1 && right2 <= right1)
			{
				has_shared_edge = TRUE;
			}
		}
	}
	else if (left1 == right2 || left2 == right1)
	{
		if (node1->square.w <= node2->square.w)
		{
			if (top1 >= top2 && bottom1 <= bottom2)
			{
				has_shared_edge = TRUE;
			}
		}
		else if (node2->square.w < node1->square.w)
		{
			if (top2 >= top1 && bottom2 <= bottom1)
			{
				has_shared_edge = TRUE;
			}
		}
	}

	return has_shared_edge;
}
void freeTree(Node* node)
{
	if(node == NULL)
	{
		return;

	}
	if (node->children[0] == NULL)
	{
		free(node->adjacency_list);
		free(node);

		return;
	}
	for (int i = 0; i < 4; i++)
	{
		node->children[i] = NULL;
	}
}
