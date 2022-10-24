#include <iostream>
#include "sculptor.h"

const char* elipses = "elipses.off";
const char* bloco = "bloco.off";
const char* treee = "tree.off";

int main()
{
    Sculptor teste(100,100,100);
    teste.setColor(255, 0, 0, 1.0);
    teste.putEllipsoid(20,20,20, 10,10,15);
    teste.cutSphere(15,15,15,7);
    teste.cutEllipsoid(16,16,16,4,4,6);
    teste.setColor(125, 120, 0, 1);
    teste.putVoxel(22,22,22);
    teste.putVoxel(22,22,23);
    teste.cutVoxel(22,22,22);
    teste.writeOFF(elipses);
    teste.~Sculptor();

    Sculptor caixa(50,50,50);
    caixa.setColor(0,15,100,1);
    caixa.putBox(0,35,0,10,5,10);
    caixa.cutBox(1,18,1,8,1,9);
    caixa.writeOFF(bloco);
    caixa.~Sculptor();

    Sculptor tree(50,50,50);
    tree.setColor(0.6, 0.3, 0, 1);
    tree.putBox(14, 20, 14, 19, 1, 16);
    tree.setColor(0.4, 0.8, 0, 1);
    tree.putEllipsoid(16,20,16,12,10,10);
    
    tree.setColor(0.514, 0.843, 0.933, 1);
    for(int i = 0; i < 30;i++){
        tree.putVoxel(rand() % 30, rand() % 30, rand() % 40);
    }
    tree.writeOFF(treee);
    tree.~Sculptor();
    
    return 0;
}