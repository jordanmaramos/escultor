/**
 * @file	sculptor.cpp
 * @brief	Implementação dos métodos da classe Sculptor, tais como
 *  construtor, destrutor e outros.
 * @author	Jordan Marques
 * @author  Pedro Rêgo
 * @date	10/2022
 */

#include <iostream>
#include <fstream>
#include "sculptor.h"

/**
 * @brief Classe Sculptor
 * @details	Construtor da classe Sculptor.
 */
Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;

    this->a = 0;
    this->r = 0;
    this->g = 0;
    this->b = 0;

    this->v = new Voxel**[this->nx];

    for(int i = 0; i < this->nx; i++){
        this->v[i] = new Voxel*[this->ny];

        for(int j = 0; j < this->ny; j++){
            this->v[i][j] = new Voxel[this->nz];

            for(int k = 0; k < this->nz; k++){
                this->v[i][j][k].isOn = false;
                this->v[i][j][k].r = 0;
                this->v[i][j][k].g = 0;
                this->v[i][j][k].b = 0;
                this->v[i][j][k].a = 0;
            }
        }
    }
}

/**
 * @details	Destrutor da classe Sculptor.
 */
Sculptor :: ~Sculptor()
{
    for(int i=0; i<this->nx; i++){
        for(int j=0; j<this->ny; j++){
            delete[] this->v[i][j];
        }
        delete[] this->v[i];
    }
    delete[] this->v;
}

/**
 * @details	Método que define a cor do objeto.
 */
void Sculptor :: setColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a; 
    std :: cout << "Cor selecionada!" << std :: endl;
}

/**
 * @details	Método que define as cores do voxel e ativa o voxel na posição (x, y, z).
 */
void Sculptor :: putVoxel(int x, int y, int z)
{
    this->v[x][y][z].r = this->r;
    this->v[x][y][z].g = this->g;
    this->v[x][y][z].b = this->b;
    this->v[x][y][z].a = this->a;
    this->v[x][y][z].isOn = true;
}

/**
 * @details	Método que desativa o voxel na posição (x, y, z).
 */
void Sculptor :: cutVoxel(int x, int y, int z)
{
    this->v[x][y][z].isOn = false;
}

/**
 * @details	Método que desenha um cubo, ativando os voxels de acordo com as coordenadas fornecidas.
 */
void Sculptor :: putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i=x0; i<x1; i++){
        for (int j=y0; j<y1; j++){
            for (int k=z0; k<z1; k++){
                this->putVoxel(i, j, k);
            }
        }        
    }
}

/**
 * @details	Método que corta/elimina um cubo, desativando os voxels de acordo com as coordenadas fornecidas.
 */
void Sculptor :: cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i=x0; i<x1; i++){
        for(int j=y0; j<y1; j++){
            for(int k=z0; k<z1; k++){
                this->cutVoxel(i, j, k);
            }
        }
    }
}

/**
 * @details	Método que desenha uma esfera, ativando os voxels de acordo com o raio fornecido.
 */
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
   float r;
   for(int i=0; i<this->nx; i++){
       for(int j=0; j<this->ny; j++){
           for(int k=0; k<this->nz; k++){
               r = ((i-xcenter)*(i-xcenter))+((j-ycenter)*(j-ycenter))+((k-zcenter)*(k-zcenter));
               if(r <= (radius*radius)){
                   this->putVoxel(i,j,k);
               }
           }
       }
   }
}

/**
 * @details	Método que faz um corte em formato de esfera, desativando os voxels de acordo com o raio fornecido.
 */
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    float r;
    for(int i=0; i<this->nx; i++){
        for(int j=0; j<this->ny; j++){
           for(int k=0; k<this->nz; k++){
                r = ((i-xcenter)*(i-xcenter))+((j-ycenter)*(j-ycenter))+((k-zcenter)*(k-zcenter));
                if(r <= (radius*radius)){
                    this->cutVoxel(i,j,k);
                }
            }
        }
    }
}

/**
 * @details	Método que desenha um elipse, ativando os voxels de acordo com as dimensões fornecidas.
 */
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    float elipse;

    for (int k=(zcenter-rz); k<=(zcenter+rz); k++){
        for (int i=(ycenter-ry); i<=(ycenter+ry); i++) {
            for (int j=(xcenter-rx); j<=(xcenter+rx); j++) {
                elipse = ((((i-ycenter)/(float)ry)*((i-ycenter)/(float)ry))+
                   (((j-xcenter)/(float)rx)*((j-xcenter)/(float)rx))+
                   (((k-zcenter)/(float)rz)*((k-zcenter)/(float)rz)));

                if (elipse <= 1){
                    this->putVoxel(k,i,j);
                }
            }
        }
    }
}

/**
 * @details	Método que faz um corte em formato de elipse, desativando os voxels de acordo com as dimensões fornecidas.
 */
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    float elipse;

    for (int k=(zcenter-rz); k<=(zcenter+rz); k++){
        for (int i=(ycenter-ry); i<=(ycenter+ry); i++) {
            for (int j=(xcenter-rx); j<=(xcenter+rx); j++) {
                elipse = ((((i-ycenter)/(float)ry)*((i-ycenter)/(float)ry))+
                   (((j-xcenter)/(float)rx)*((j-xcenter)/(float)rx))+
                   (((k-zcenter)/(float)rz)*((k-zcenter)/(float)rz)));

                if (elipse <= 1){
                    this->cutVoxel(k,i,j);
                }
            }
        }
    }
}

/**
 * @details	Método que gera o arquivo .off para exibição da figura.
 */
void Sculptor :: writeOFF(const char* filename)
{
    std::ofstream fout;
    
    fout.open(filename);
    
    if(!fout.is_open()){
        std::cout << "Falha na criação do arquivo\n" << std::endl;
        exit(1);
    }  else {
        std::cout << "Arquivo criado com sucesso." << std::endl;
    }
    
    fout << "OFF" << std::endl;

    int count_voxel = 0;
    for(int i=0; i < this->nx; i++){
        for(int j=0; j < this->ny; j++){
            for(int k=0; k < this->nz; k++){
                if (this->v[i][j][k].isOn){
                    count_voxel++;
                }
            }
        }
    }

    fout << 8*count_voxel << " " << 6*count_voxel << " " << 0 << std::endl;

    // Vertices do voxel
    for(int i=0; i < this->nx; i++){
        for(int j=0; j < this->ny; j++){
            for(int k=0; k < this->nz; k++){
                if (this->v[i][j][k].isOn){
                    fout << -0.5+i << " " << 0.5+j << " " << -0.5+k << std::endl; // P0
                    fout << -0.5+i << " " << -0.5+j << " " << -0.5+k << std::endl; // P1
                    fout << 0.5+i << " " << -0.5+j << " " << -0.5+k << std::endl; // P2
                    fout << 0.5+i << " " << 0.5+j << " " << -0.5+k << std::endl; // P3
                    fout << -0.5+i << " " << 0.5+j << " " << 0.5+k << std::endl; // P4
                    fout << -0.5+i << " " << -0.5+j << " " << 0.5+k << std::endl; // P5
                    fout << 0.5+i << " " << -0.5+j << " " << 0.5+k << std::endl; // P6
                    fout << 0.5+i << " " << 0.5+j << " " << 0.5+k << std::endl; // P7
                }
            }
        }
    }

    // Estruturar os voxel
    int nvoxel = 0;
    for(int i=0; i < this->nx; i++){
        for(int j=0; j < this->ny; j++){
            for(int k=0; k < this->nz; k++){
                if (this->v[i][j][k].isOn){
                    fout << "4 " << 0+nvoxel*8 << " " << 3+nvoxel*8 << " " << 2+nvoxel*8 << " " << 1+nvoxel*8 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl; // Face1: P0 P3 P2 P1
                    
                    fout << "4 " << 4+nvoxel*8 << " " << 5+nvoxel*8 << " " << 6+nvoxel*8 << " " << 7+nvoxel*8 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl; // Face2: P4 P5 P6 P7
                    
                    fout << "4 " << 0+nvoxel*8 << " " << 1+nvoxel*8 << " " << 5+nvoxel*8 << " " << 4+nvoxel*8 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl; // Face3: P0 P1 P5 P4
                    
                    fout << "4 " << 0+nvoxel*8 << " " << 4+nvoxel*8 << " " << 7+nvoxel*8 << " " << 3+nvoxel*8 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl; // Face4: P0 P4 P7 P3
                    
                    fout << "4 " << 7+nvoxel*8 << " " << 6+nvoxel*8 << " " << 2+nvoxel*8 << " " << 3+nvoxel*8 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl; // Face5: P7 P6 P2 P3
                    
                    fout << "4 " << 1+nvoxel*8 << " " << 2+nvoxel*8 << " " << 6+nvoxel*8 << " " << 5+nvoxel*8 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl; // Face6: P1 P2 P6 P5
                    nvoxel++;
                }
            }
        }
    }
    std::cout << "Escultura gerada!" << std::endl;
    fout.close();
}
