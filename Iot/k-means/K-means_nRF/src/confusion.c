#include <zephyr/kernel.h>
#include <math.h>
#include "confusion.h"
#include "adc.h"
#include <stdio.h>

int CM[6][6] = {0};

int CP[6][3]= {

		            {1766,1477,1428},
					{1178,1464,1471},
					{1475,1758,1533},
					{1469,1170,1473},
					{1446,1454,1787},
					{1467,1471,1199}
};

int measurements_array[6][3] = {0};

void printConfusionMatrix(void)
{

	for(int i = 0;i<6;i++)
	{
		printk("%d,%d,%d,%d,%d,%d\n",CM[i][0],CM[i][1],CM[i][2],CM[i][3],CM[i][4],CM[i][5]);

	}
}

void makeHundredFakeClassifications(void)
{
	
}	

void makeOneClassificationAndUpdateConfusionMatrix(int direction)
{
	struct Measurement m = readADCValue();

	int predicted = calculateDistanceToAllCentrePointsAndSelectWinner(m.x, m.y, m.z);

	CM[direction][predicted]++;
   printk("Oikea arvo = %d,   laskettu arvo = %d\n ",direction,predicted);
}

int calculateDistanceToAllCentrePointsAndSelectWinner(int x,int y,int z)
{

   int winner = 0;
   int shortest = 100000;

   for (int i = 0; i<6; i++){
	int dx = x - CP[i][0];
	int dy = y - CP[i][1];
	int dz = z - CP[i][2];
	
	int distance = (dx*dx + dy*dy + dz*dz);

	if (distance < shortest){
		shortest = distance;
		winner = i;
	}
   }
   return winner;
}

void resetConfusionMatrix(void)
{
	for(int i=0;i<6;i++)
	{ 
		for(int j = 0;j<6;j++)
		{
			CM[i][j]=0;
		}
	}
}

