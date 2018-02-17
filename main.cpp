#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL\glut.h>
#define SORT_NO 4	// Number of sorting algorithms
#define MAX 50		// Number of values in the array
#define SPEED 700	// Speed of sorting, must be greater than MAX always
int a[MAX];			// Array
int swapflag=0;		// Flag to check if swapping has occured
int i=0,j=0;		// To iterate through the array
int flag=0;			// For Insertion Sort
int dirflag=0;		// For Ripple Sort, to change direction at the ends
int count=1;		// For Ripple Sort, to keep count of how many are sorted at the end		
int k=0;			// To Switch from Welcome screen to Main Screen
int sorting=0;		// 1 if Sorted
char *sort_string[]={"Bubble Sort","Selection Sort","Insertion Sort","Ripple Sort"};
int sort_count=0;	// To cycle through the string

// Function to display text on screen char by char
void bitmap_output(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

// Function to integer to string
void int_str(int rad,char r[])
{
	itoa(rad,r,10);
}

void display_text()
{
	glColor3f(0,0,1);
	bitmap_output(150, 665, "DYNAMIC SORTING ALGORITHM VISUALIZER",GLUT_BITMAP_TIMES_ROMAN_24);
	glBegin(GL_LINE_LOOP);
		glVertex2f(145, 660);
		glVertex2f(520, 660);
	glEnd();

	// other text small font
	bitmap_output(10, 625, "This program sorts a random set of numbers in ascending order displaying them graphically as ",GLUT_BITMAP_9_BY_15);
	bitmap_output(10, 605, "bars with varying height",GLUT_BITMAP_9_BY_15);


	if (sorting == 0)	// if not sorting display menu
	{
		bitmap_output(10, 575, "MENU",GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 555, "Press s to SORT",GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 535, "Press c to SELECT the sort algorithm",GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 515, "Press r to RANDOMISE",GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 495, "Esc to QUIT",GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 475, "Selected sort: ",GLUT_BITMAP_9_BY_15);
		bitmap_output(150, 475, *(sort_string+sort_count),GLUT_BITMAP_9_BY_15);
	}
	else if (sorting == 1)	// while sorting
	{
		glColor3f(0.5,0.5,0.5);
		bitmap_output(10, 555, "Sorting in progress...",GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 535, "Press p to PAUSE",GLUT_BITMAP_9_BY_15);
		glColor3f(0.0,0.0,0.0);
	}
}

void front()
{
	glColor3f(0.0,0.0,1.0);
	bitmap_output(300, 565, "WELCOME!",GLUT_BITMAP_TIMES_ROMAN_24);
	glBegin(GL_LINE_LOOP);
		glVertex2f(295, 560);
		glVertex2f(395, 560);
	glEnd();
	bitmap_output(330, 525, "TO",GLUT_BITMAP_TIMES_ROMAN_24);
	glBegin(GL_LINE_LOOP);
		glVertex2f(325, 521);
		glVertex2f(360, 521);
	glEnd();

	bitmap_output(150, 475, "DYNAMIC SORTING ALGORITHM VISUALIZER",GLUT_BITMAP_TIMES_ROMAN_24);
	glBegin(GL_LINE_LOOP);
		glVertex2f(145, 470);
		glVertex2f(520, 470);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);
		glVertex2f(520,120.0);glVertex2f(520,170);glVertex2f(796,170);glVertex2f(796,120.0);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	bitmap_output(530, 125, "Press Enter to continue.......",GLUT_BITMAP_HELVETICA_18);
}

void Initialize() {
	int temp1;

	// Reset the array
	for(temp1=0;temp1<MAX;temp1++){
		a[temp1]=rand()%100+1;
		printf("%d ",a[temp1]);
	}

	// Reset all values
	i=j=0;
	dirflag=0;
	count=1;
	flag=0;

	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 699,0,799);
}

// Return 1 if not sorted
int notsorted(){
	int q;
	for(q=0;q<MAX-1;q++)
	{
		if(a[q]>a[q+1])
			return 1;
	}
	return 0;
}

// Main function for display
void display()
{
	int ix,temp;
	glClear(GL_COLOR_BUFFER_BIT);

	if(k==0)
		front();
	else{
		display_text();
		char text[10];
		
		for(ix=0;ix<MAX;ix++)
		{
			glColor3f(1,0,0);
			glBegin(GL_LINE_LOOP);
				glVertex2f(10+(700/(MAX+1))*ix,50);
				glVertex2f(10+(700/(MAX+1))*(ix+1),50);
				glVertex2f(10+(700/(MAX+1))*(ix+1),50+a[ix]*4);
				glVertex2f(10+(700/(MAX+1))*ix,50+a[ix]*4);
			glEnd();

			int_str(a[ix],text);
			//printf("\n%s",text);
			glColor3f(0,0,0);
			bitmap_output(12+(700/(MAX+1))*ix, 35, text,GLUT_BITMAP_TIMES_ROMAN_10);
		}

		if(swapflag || sorting==0)
		{
			glColor3f(0,0,1);
			glBegin(GL_POLYGON);
				glVertex2f(10+(700/(MAX+1))*j,50);
				glVertex2f(10+(700/(MAX+1))*(j+1),50);
				glVertex2f(10+(700/(MAX+1))*(j+1),50+a[j]*4);
				glVertex2f(10+(700/(MAX+1))*j,50+a[j]*4);
			glEnd();
			swapflag=0;
		}
	}
	glFlush();
}

// Insertion Sort
void insertionsort()
{
	int temp;
	
	while(i<MAX)
	{
		if(flag==0){j=i; flag=1;}
		while(j<MAX-1)
		{
			if(a[j]>a[j+1])
			{
				swapflag=1;
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;

				goto A;
			}
			j++;
			if(j==MAX-1){flag=0;}
			printf("swap %d and %d\n",a[j],a[j+1]);
		}
		i++;
	}
	sorting=0;
	A:
	i=j=0;
}

// Selection Sort
void selectionsort()
{
	int temp,j,min,pos;

	while(notsorted())
	{
	
		while(i<MAX-1)
		{
			min=a[i+1];
			pos=i+1;
			if(i!=MAX-1)
			{
				for(j=i+2;j<MAX;j++)
				{
					if(min>a[j])
					{
						min=a[j];
						pos=j;
					}	
				}	
			}
			printf("\ni=%d min=%d at %d",i,min,pos);
			printf("\nchecking %d and %d",min,a[i]);
			if(min<a[i])
			{
				
				//j=pos;
				printf("\nswapping %d and %d",min,a[i]);
				temp=a[pos];
				a[pos]=a[i];
				a[i]=temp;
				goto A;
			}
			i++;
		}
	}
	sorting=0;
	i=j=0;
	A:  printf("");
}

//Bubble Sort
void bubblesort()
{
	int temp;
	while(notsorted())
	{
		while(j<MAX-1)
		{
			if(a[j]>a[j+1])
			{
				swapflag=1;
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;

				goto A;
			}
			j++;
			if(j==MAX-1) j=0;
			printf("swap %d and %d\n",a[j],a[j+1]);
		}
	}
	sorting=0;
	A: printf("");
}

//Ripple Sort
void ripplesort()
{
	int temp;
	while(notsorted() && sorting)
	{
		if(dirflag==0)
		{
			while(j<MAX-1)
			{
				if(a[j]>a[j+1])
				{
					swapflag=1;
					temp=a[j];
					a[j]=a[j+1];
					a[j+1]=temp;
	
					goto A;
				}
				j++;
				if(j==MAX-1) {count++; j=MAX-count;	dirflag=1-dirflag;}
				printf("j=%d forward swap %d and %d\n",j,a[j],a[j+1]);
			}
		}
		else
		{
			while(j>=0)
			{
				if(a[j]>a[j+1])
				{
					swapflag=1;
					temp=a[j];
					a[j]=a[j+1];
					a[j+1]=temp;
	
					goto A;
				}
				j--;
				if(j==0){ dirflag=1-dirflag;}
				printf("j=%d backward swap %d and %d\n",j,a[j],a[j+1]);
			}
		}
	}
	sorting=0;
	A: printf("");
}

// Timer Function, takes care of sort selection
void makedelay(int)
{
	if(sorting)
	{
		switch(sort_count)
		{
			case 0:	bubblesort();		break;
			case 1:	selectionsort();	break;
			case 2: insertionsort();	break;
			case 3: ripplesort();		break;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(SPEED/MAX,makedelay,1);
}

// Keyboard Function
void keyboard (unsigned char key, int x, int y)
{
	if(key==13)
		k=1;
	if (k==1 && sorting!=1)
	{
		switch (key)
		{
			case 27	 :	exit (0); // 27 is the ascii code for the ESC key
			case 's' :	sorting = 1; break;
			case 'r' :	Initialize(); break;
			case 'c' :	sort_count=(sort_count+1)%SORT_NO;	break;
		}
	}
	if(k==1 && sorting==1)
		if(key=='p')	sorting=0;
}

// Main Function
void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1000,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Dynamic Sorting Visualizer");
	Initialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000,makedelay,1);
	glutMainLoop();
}