#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <search.h>
#include<stdbool.h> 



static float dw1 = 0;
static float dw2 = 0;
static float db = 0;

float Hingeloss(float x1, float x2, int y, float w1, float w2, float b){

    float loss = 0;

    if(y==1){
        loss = 1-(w1*x1 + w2*x2 + b);
    }
    else{
        loss = 1+(w1*x1 + w2*x2 + b);
    }

    if(loss < 0){
        loss = 0;
    }

    return loss;

}



float SVMcostGen(int X1[], int X2[], int Y[], float w1, float w2, float b){

    int n = 18;

    // hinge loss

    float cost=0;
    dw1 = 0;
    dw2 = 0;
    db = 0;

    for(int i = 0; i<n;i++){
        float loss = Hingeloss(X1[i], X2[i], Y[i], w1, w2, b);
        cost += loss;
        // when loss = 0, all derivatives are 0
        if(loss > 0){
            dw1 += (-X1[i]*Y[i]);
            dw2 += (-X2[i]*Y[i]);
            db += (-Y[i]);
        }
    }

    cost /= n;
    dw1 /= n;
    dw2 /= n;
    db /=n;

    return cost;
}






void MainFunc(int X1[], int X2[], int Y[]){

    float lrate = 0.0007;
    float threshold = 0.001;
    float w1 = 1;
    float w2 = 1;
    float b = 0;

    int iter = 0;
    float cost;

    while(true){
        cost = SVMcostGen(X1, X2, Y, w1, w2, b);
        if(iter%1000==0){
            printf("Iter: %d , cost = %f , dw1 = %f , dw2 = %f , db = %f \n",iter,cost,dw1,dw2,db);
            printf("Accuracy is %f \n",100.0-cost);
        }

        iter++;

        if(fabs(dw1) < threshold && fabs(dw2) < threshold && fabs(db) < threshold){
            printf("y = %f * x1 + %f *x2 + %f \n",w1,w2,b);
            break;
        }

        w1 -= (lrate* dw1);
        w2 -= (lrate* dw2);
        b -= (lrate * db);
    }

}





int main() {
    // age
    int X1[18] = {35,27,19,25,26,45,46,48,47,29,27,28,27,30,28,23,27,18};

    // income in K
    int X2[18] = {20,57,76,33,52,26,28,29,49,43,137,44,90,49,84,20,54,44};

    // buy a house
    int Y[18] = {-1, -1, -1, -1, -1, 1, 1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, -1 };

    MainFunc(X1, X2, Y);

}

