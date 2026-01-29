#ifndef CONFUSION_MATRIX_H
#define CONFUSION_MATRIX_H

extern int CM[6][6];
extern int measurements_array[6][3];

void printConfusionMatrix(void);
void makeHundredFakeClassifications(void);
void makeOneClassificationAndUpdateConfusionMatrix(int);
int calculateDistanceToAllCentrePointsAndSelectWinner(int,int,int);
void resetConfusionMatrix(void);


#endif
