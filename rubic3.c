#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_SQUARE_DEBUG_ 0
#define EMPTY 0
#define BLOCKED 1
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_RIGHT 3

void algo_line(int **table, int line)   //right
{
    int temp;
    for(int i=line; i<line+1; i++)
    {
        int buff=1;
        for(int j=0; j<4; j++)
        {   
            if(j==3)
                buff=0;
            
            temp=table[i][j];
            table[i][j]=table[i][j+buff];
            table[i][j+buff]=temp;
        }
    }
}

void algo_line_reverse(int **table, int line)    //right
{
    int temp;

   temp = table[line][3];
   for (int i = 3; i > 1; i--) 
   {
      table[line][i] = table[line][i - 1];
   }
   table[line][0] = temp;
}

void algo_column(int **table, int column)     //right
{
    int tmp;

    tmp = table[0][column];
    for (int i = 0; i < 3; i++) 
    {
       table[i][column] = table[i + 1][column];
    }
    table[3][column] = tmp;

}

void algo_column_reverse(int **table, int column)    //right
{
    int tmp;

    tmp = table[3][column];
    for (int i = 3; i > 1; i--) 
    {
       table[i][column] = table[i - 1][column];
    }
    table[0][column] = tmp;
}

void algo_square(int **table, int square)        //right
{
    int temp, f, g;
    if(square==0)
    {
        f=0;
        g=0;
    }
    else if(square==1)
    {
        f=0;
        g=2;
    }
    else if(square==2)
    {
        f=2;
        g=0;

    }
    else
    {
        f=2;
        g=2;
    }

    temp=table[f][g];
    table[f][g]=table[f+1][g];
    table[f+1][g]=table[f+1][g+1];
    table[f+1][g+1]=table[f][g+1];
    table[f][g+1]=temp;
}


void algo_square_reverse(int **table, int square)     //right
{
    int temp, f, g;
    if(square==0)
    {
        f=0;
        g=0;
    }
    else if(square==1)
    {
        f=0;
        g=2;
    }
    else if(square==2)
    {
        f=2;
        g=0;

    }
    else
    {
        f=2;
        g=2;
    }

    temp=table[f][g];
    table[f][g]=table[f][g+1];
    table[f][g+1]=table[f+1][g+1];
    table[f+1][g+1]=table[f+1][g];
    table[f+1][g]=temp;
}

int is_in_line(int **table, int line, int value)
{
    int check=0;
    for(int i=0; i<4; i++)
    {
        if(table[line][i]==value)
            check++;

    }
    if(check>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int is_in_column(int **table, int column, int value)
{
    int check=0;
    for(int i=0; i<4; i++)
    {
        if(table[i][column]==value)
            check++;
    }

    if(check>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

int *look_for_space(int **table, int *lines, int *columns, int value)
{
	int *nul = NULL;
    nul = malloc(sizeof(int)*2);


	for (int i=0; i<4; i++)
	{
		if (lines[i] != BLOCKED)
		{
			for(int j=0; j<4; j++)
			{
				if(columns[j] != BLOCKED && table[i][j] != value) 
				{
                    nul[0] = i;
                    nul[1] = j;
				}
			}
		}
	}

	return nul;
}

int *look_for_value(int **table, int *lines, int *columns, int value)
{
	int *nul = NULL;
    nul = malloc(sizeof(int)*2);


	for (int i=0; i<4; i++)
	{
		if (lines[i] != BLOCKED)
		{
			for(int j=0; j<4; j++)
			{
				if(columns[j] != BLOCKED && table[i][j] == value) 
				{
                    nul[0] = i;
                    nul[1] = j;
				}
			}
            lines[i] = BLOCKED;
		}
	}

	return nul;
}

void rotate_lines(int **table, int line, int offset)
{
	for(int i = 0; i < abs(offset); i++)
	{
		if(offset < 0)
        {
            algo_line(table, line);
        }
		else
        {
            algo_line_reverse(table, line); 
        }
	}
}

void rotate_columns(int **table, int column, int offset)
{
	for(int i = 0; i < abs(offset); i++)
	{
		if(offset < 0)
        {
            algo_column(table, column);
        }
		else 
        {
            algo_column_reverse(table, column);
        }
	}
}

int *get_space(int **table, int line, int value)
{
	int *first_coord = NULL;
    first_coord = malloc(2*sizeof(int));

	for(int i=0; i<4; i++)
	{
		if (table[line][i] != value) 
		{
			first_coord[0] = line;
			first_coord[1] = i;
		}
	}
	return first_coord;
}



void build_first_line(int **table)
{
	int *n_value;
	int *n_space;
	int lines[4];
	int columns[4];

	lines[0]=BLOCKED;
	for(int i = 1; i < 4; i++)
    {
        lines[i]=EMPTY;
    } 
	for(int j = 0; j < 4; j++)
    {
        columns[j]=EMPTY;
    } 

	while(get_space(table, 0, 0) != NULL)
	{
		n_space = get_space(table, 0, 0);   

		if(n_space == NULL)     
        {
            return;
        }

		n_value = look_for_value(table, lines, columns, 0);

		rotate_lines(table, n_value[0], n_space[1] - n_value[1]);
		rotate_columns(table, n_space[1], n_space[0] - n_value[0]);
	}
}

void line_to_square(int **table, int line)
{
	if(line != 0 && line != 3)
	{
		return;
	}

	if (line == 0)
	{
		algo_square(table, 0);
		algo_square(table, 0);
		rotate_lines(table, 0, -2);
	}
	else 
	{
		algo_square(table, 3);
		algo_square(table, 3);
		rotate_lines(table, 3, 2);
	}
}

void push_it_up(int **table)
{
	for(int i=2; i<4; i++)
    {
        rotate_columns(table, i, -2);
    }

}

void build_last_line(int **table)
{
																																																																																			

}


void print_tab(int **table) 
{
    for(int i=0; i<4; i++)
    {
        
        printf("-----------------\n");
        for (int j=0; j<4; j++)
        {
            printf("| %d ", table[i][j]);
        }
        printf("|");
        printf("\n");

        if(i==3)
        {
            printf("-----------------\n");
            printf("\n");
        }
        
    }
}


int main(int ac, char **av)
{
    int input1, input2;
    int **table;
    if (ac == 1)
    return 0;

    //memory allocation
    input1 = atoi(av[1]);
    input2 = atoi(av[2]);
    table = malloc(4 * sizeof(int *));
	for(int i = 0; i < 4; i++)
		table[i] = malloc(4 * sizeof(int));
        
    //filling array
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {   
            if(i==0 || i==1)
            {
                if(j==0 || j==1)
                {
                    table[i][j]=0;
                }

                else if(j==2 || j==3)
                {
                    table[i][j]=1;
                }
            } 

            if(i==2 || i==3)
            {
                if(j==0 || j==1)
                {
                    table[i][j]=2;
                }
                else if(j==2 || j==3)
                {
                    table[i][j]=3;
                }
            }

        }
    }

    int lines[4];
    int columns[4];

    lines[0] = BLOCKED;
    lines[1] = BLOCKED;
    lines[2] = EMPTY;
    lines[3] = BLOCKED;
    columns[0] = EMPTY;
    columns[1] = EMPTY;
    columns[2] = BLOCKED;
    columns[3] = BLOCKED;
    //verif_return(look_for_space(table, lines, columns, 1));
    //verif_return(look_for_space(table, lines, columns, 2));
    //printf("Rotate %d, column %d\n", input1, input2);

    //algo_line(table, 0);
    //algo_line_reverse(table, input);
    //algo_column_reverse(table, input);
    //algo_square_reverse(table, input);
    //is_in_line(table,input1,input2);

    print_tab(table);
    printf("\n");
    printf("%d - %d\n", is_in_line(table, 0, 1), is_in_column(table, 2, 3));
    printf("%d - %d\n", is_in_line(table, 3, 1), is_in_column(table, 2, 0));
    return 0;
}
