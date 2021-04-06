#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char** maze;
int** visited;
int rows;
int cols;
int start_row;
int start_col;

enum terrain {
	empty,
	wall,
	goal,
	crumb
};

void alloc_maze()
{
	maze = malloc(rows * sizeof(char*));
	
	int i;
	for (i = 0; i < rows; ++i){
		maze[i] = malloc(cols * sizeof(char*));
	}
}


void alloc_visited()
{
	visited = malloc(rows * sizeof(int*));
	int i;
	for (i = 0; i < rows; ++i){
		visited[i] = malloc(cols * sizeof(int*));
	}
}

void get_maze()
{
	char c,file_name[25];
	char rows_s[3] = { '\0' };
	char cols_s[3] = { '\0' };
	int rows_i = 0;
	int cols_i = 0;
	int swap = 0;
	printf("Buka File Labirin : ");
	scanf("%s",file_name);
	FILE* maze_file = fopen(file_name, "r");

		while ((c = getc(maze_file)) != EOF) {
			if (c == '\n') {
				break;
			} else if (c == ','){
				swap = 1;
			} else if (!swap) {
				rows_s[rows_i] = c;
				rows_i++;
			} else {
				cols_s[cols_i] = c;
				cols_i++;
			}
		}


	rows = atoi(rows_s);
	cols = atoi(cols_s);

	alloc_maze();
	
	int i,j;

	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {

			if ((c = getc(maze_file)) == '\n') {
				c = getc(maze_file);
			}

			maze[i][j] = c;

			if (c =='s') {
				start_row = i;
				start_col = j;
			}
		}
	}

	fclose(maze_file);
}

void init_visited()
{
	alloc_visited();

	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if (maze[i][j] == '#') {
				visited[i][j] = wall;
			} else if (maze[i][j] == 'g') {
				visited[i][j] = goal;
			} else {
				visited[i][j] = empty;
			}
		}
	}
}	

void print_maze()
{
	int i, j,x;
	x=178;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if(maze[i][j]=='#')
				printf("%c", x);
			else
				printf("%c", maze[i][j]);
			
		}
		printf("\n");
	}	
	printf("\n");
}

void add_crumbs()
{
	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if (maze[i][j] != 's' && visited[i][j] == crumb) {
				maze[i][j] = '.';
			}
		}
	}
}

int dfs(int row, int col)
{
	int* current = &visited[row][col];

	if (*current == goal) {
		return 1;
	}

	if (*current == empty) {
		*current = wall;

		if (dfs(row, col - 1)){
			*current = crumb;
			return 1;
		} 
		if (dfs(row + 1, col)){
			*current = crumb;
			return 1;
		} 
		if (dfs(row, col + 1)){
			*current = crumb;
			return 1;		
		} 
		if (dfs(row - 1, col)){
			*current = crumb;
			return 1;
		}
	}

	return 0;
}

void reset()
{
	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if (maze[i][j] != 's' && visited[i][j] == crumb) {
				maze[i][j] = ' ';
			}
		}
	}
}

int main() {
	char i;
	int x,y;
	get_maze();

	xy:
		
		system ("cls");
		print_maze();
		printf (" --------------------------------------------------------\n");		
		printf (" |  1.Mencari jalur tercepat      3.Hapus jalur         |\n");
		printf (" |  2.Buka Peta Labirin Baru      4.Keluar              |\n");
		printf (" --------------------------------------------------------\n\n");
		printf (" --------------------------\n");
		printf (" |   KONTROL GERAKAN 'S'  |\n");
		printf (" |   w:atas	s:bawah	  |\n");
		printf (" |   a:kiri	d:kanan	  |\n");
		printf (" --------------------------\n");
		i=getch();
		switch (i){
		case 'd' :
			if (maze[start_row ][start_col + 1]=='#')
			{
				goto xy;
			}
			
			if((maze[start_row ][start_col + 1]==' ')||(maze[start_row ][start_col + 1]=='.'))
			{
				y = start_col;
				start_col++;
				maze[start_row ][start_col]='s';
				maze[start_row][y]=' ';
				goto xy;
			}
		case 'a' :
			if (maze[start_row ][start_col - 1]=='#')
			{
				goto xy;
			}
			
			if((maze[start_row ][start_col - 1]==' ')|| (maze[start_row ][start_col - 1]=='.'))
			{
				x= start_col;
				start_col--;
				maze[start_row ][start_col]='s';
				maze[start_row][x]=' ';
				goto xy;
			}
		case 's' :
			if (maze[start_row + 1 ][start_col ]=='#')
			{
				goto xy;
			}
			
			if((maze[start_row + 1][start_col]==' ')|| (maze[start_row + 1][start_col]=='.'))
			{
				y = start_row;
				start_row++;
				maze[start_row ][start_col]='s';
				maze[y][start_col]=' ';
				goto xy;
			}
		case 'w' :
			if (maze[start_row - 1][start_col]=='#' )
			{
				goto xy;
			}
			
			if((maze[start_row - 1][start_col ]==' ')|| (maze[start_row - 1 ][start_col]=='.'))
			{
				x= start_row;
				start_row--;
				maze[start_row ][start_col]='s';
				maze[x][start_col]=' ';
				goto xy;
			}
		printf("Selamat Anda Berhasil Mencapai Tujuan\n");
		
		case '2':
			get_maze();
			goto xy;
			
		
		case '1' :
		  	init_visited();
		  	if (!dfs(start_row, start_col)) {
			 	printf("No path to the goal could be found.\n");
		   	} else {
			 	add_crumbs();
			 	print_maze();
			}
			goto xy;
		
		case '3':
			reset();
			goto xy;
			
		case '4' :
			break;
		}
	

	return 0;
}
