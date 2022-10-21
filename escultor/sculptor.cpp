#include <iostream>
#include <fstream>
#include "sculptor.h"

//Voxel ***

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;

    this->a = 0;
    this->r = 0;
    this->g = 0;
    this->b = 0;

    v = new Voxel**[_nx];

    for(int i = 0; i < _nx; i++){
        v[i] = new Voxel*[_ny];

        for(int j = 0; j < _ny; j++){
            v[i][j] = new Voxel[_nz];

            for(int k = 0; k < _nz; k++){
                this -> v[i][j][k].isOn = false;
                this -> v[i][j][k].r = 0;
                this -> v[i][j][k].g = 0;
                this -> v[i][j][k].b = 0;
                this -> v[i][j][k].a = 0;
            }
        }
    }
}

Sculptor :: ~Sculptor(){
    for(int i=0; i<this->nx; i++){
        for(int j=0; j<this->ny; j++){
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v ;
}

void Sculptor :: setColor(float _r, float _g, float _b, float alpha)
{
    this->r=_r;
    this->g = _g;
    this->b = _b;
    this->a = alpha; // seta os valores da cores a serem usadas
    std :: cout <<"Cor selecionada!" << std :: endl;
}
