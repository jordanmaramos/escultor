#include <iostream>
#include "sculptor.h"

const char* Escultura = "Escultura.off";

int main()
{
    Sculptor tree(31,31,41);
    tree.setColor(0.486, 0.988, 0, 1);
    tree.putBox(0, 30, 0, 31, 0, 1);
    tree.setColor(0.588, 0.294, 0, 1);
    tree.putBox(14, 19, 14, 19, 1, 16);
    tree.setColor(0.388, 0.792, 0, 1);
    tree.putEllipsoid(16,16,20,10,10,12);
    tree.putSphere(5, 5, 1, 5);
    tree.setColor(0.514, 0.843, 0.933, 1);
    for(int i = 0; i < 30;i++){
        tree.putVoxel(rand() % 30, rand() % 30, rand() % 40);
    }
    tree.writeOFF(Escultura);

    return 0;
}