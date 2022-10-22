#include <iostream>
#include <fstream>
#include "sculptor.h"

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
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

Sculptor :: ~Sculptor()
{
    for(int i=0; i<this->nx; i++){
        for(int j=0; j<this->ny; j++){
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v ;
}

void Sculptor :: setColor(float _r, float _g, float _b, float a)
{
    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = a; 
    std :: cout << "Cor selecionada!" << std :: endl;
}


void Sculptor :: putVoxel(int x, int y, int z)
{
    if(x >= 0 && x < nx && y >= 0 && y < ny && z >=0 && z < nz){
        this->v[x][y][z].r = this-> r;
        this->v[x][y][z].g = this-> g;
        this->v[x][y][z].b = this-> b;
        this->v[x][y][z].a = this-> a;
        this->v[x][y][z].isOn = true;
    }
}

void Sculptor :: cutVoxel(int x, int y, int z)
{
    this->v[x][y][z].isOn = false;
}

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

void Sculptor :: putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    this->putEllipsoid(xcenter, ycenter, zcenter, radius, radius, radius);
}

void Sculptor :: cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    this->cutEllipsoid(xcenter, ycenter, zcenter, radius, radius, radius);
}

void Sculptor :: putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    float elipse = 0;
    for (int i=xcenter-rx; i<xcenter+rx; i++){
        for (int j=ycenter-ry; j<ycenter+ry; j++){
            for (int k=zcenter-rz; k<zcenter+rz; k++){
                elipse = ((i-xcenter) * (i-xcenter))/(rx*rx) + ((j-ycenter) * (j-ycenter))/(ry*ry) + ((k-zcenter) * (k-zcenter))/(rz*rz);
                if (elipse < 1)
                    this->putVoxel(i, j, k); 
            }
        }
    }
}

void Sculptor :: cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    float elipse = 0;
    for (int i=xcenter-rx; i<xcenter+rx; i++){
        for (int j=ycenter-ry; j<ycenter+ry; j++){
            for (int k=zcenter-rz; k<zcenter+rz; k++){
                elipse = ((i-xcenter) * (i-xcenter))/(rx*rx) + ((j-ycenter) * (j-ycenter))/(ry*ry) + ((k-zcenter) * (k-zcenter))/(rz*rz);
                if (elipse < 1)
                    this->cutVoxel(i, j, k); 
            }
        }
    }
}

void Sculptor :: writeOFF(const char* filename)
{
    int vertices=0, faces=0, bordas=0, quantidade=0;

    std::ofstream fout;

    int p=0, cont=0;

    //Abertura do arquivo
    fout.open(filename); 

    if(!fout.is_open()){
        std::cout << "Falha na criação do arquivo\n" << std::endl;
        exit(1);
    } else {
        std::cout << "Arquivo criado com sucesso." << std::endl;
    }

    //Contador de voxels ativos
    for(int k=0; k<this->nz; k++){
        for(int i=0; i<this->nx; i++){
            for(int j=0; j<this->ny; j++){
                if(this->v[i][j][k].isOn){
                    quantidade++;
                }
            }
        }
    }

    vertices = quantidade*8; //Quantidade de vértices da figura
    faces = quantidade*6; //Quantidade de faces da figura

    //Para fazer a identificação
    fout << "OFF" << std::endl;

    //Número de faces, vértices e arestas
    fout << vertices << " " << faces << " " << bordas << std::endl;

    //Coordenadas espaciais
    for(int k=0; k<this->nz; k++){
        for(int i=0; i<this->nx; i++){
            for(int j=0; j<this->ny; j++){
                if(this->v[i][j][k].isOn){
                    fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                    fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                }
            }
        }
    }

    for(int k=0; k<this->nz; k++){
            for(int i=0; i<this->nx; i++ ){
                for(int j=0; j<this->ny; j++){
                    if(v[i][j][k].isOn == true){
                        p = 8 * cont;
                        fout << 4 << " " << p+0 << " " << p+3 << " " << p+2 << " " << p+1 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl;
                        
                        fout << 4 << " " << p+4 << " " << p+5 << " " << p+6 << " " << p+7 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl;
                        
                        fout << 4 << " " << p+0 << " " << p+1 << " " << p+5 << " " << p+4 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl;

                        fout << 4 << " " << p+0 << " " << p+4 << " " << p+7 << " " << p+3 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl;

                        fout << 4 << " " << p+3 << " " << p+7 << " " << p+6 << " " << p+2 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl;
                        
                        fout << 4 << " " << p+1 << " " << p+2 << " " << p+6 << " " << p+5 << " " << this->v[i][j][k].r << " " << this->v[i][j][k].g << " " << this->v[i][j][k].b << " " << this->v[i][j][k].a << std::endl;
                        
                        cont ++;
                    }
                }
            }
        }
    std::cout << "Escultura produzida com sucesso!" << std::endl;

    //Fechando arquivo
    fout.close(); 
}
