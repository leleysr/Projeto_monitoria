#ifndef _PIGFuncoesBasicas_
#define _PIGFuncoesBascias_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <string.h>
#include <time.h>
#include <vector>
#include <map>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <stdint.h>
#include <limits.h>

//separa uma string em palavras, usando os delimitadores indicados
std::vector<std::string> PIGSeparaPalavras(std::string texto,std::string delim){
    std::vector<std::string> resp;
    std::string strAtual = "";

    for (int i=0;i<texto.size();i++){

        if (delim.find(texto[i]) != std::string::npos){//achou delimitadores
            resp.push_back(strAtual);

            strAtual = texto[i];
            if (texto[i]!='\n'){
                resp.push_back(strAtual);
                strAtual = "";
            }

        }else strAtual += texto[i];
    }

    if (strAtual!=""){
        resp.push_back(strAtual);
    }
    return resp;
}

//verifica se uma string possui apenas digitos de 0 a 9
bool PIGSomenteNumeros(std::string frase){
    for (int i=0;i<frase.size();i++)
        if (frase[i]<'0'||frase[i]>'9')
            return false;
    return true;
}

//verifica se duas cores s�o iguais
inline bool PIGCoresIguais(PIG_Cor cor1, PIG_Cor cor2){
    return cor1.r==cor2.r&&cor1.g==cor2.g&&cor1.b==cor2.b&&cor1.a==cor2.a;
}

bool operator ==(PIG_Cor cor1, PIG_Cor cor2){
    return cor1.r==cor2.r&&cor1.g==cor2.g&&cor1.b==cor2.b&&cor1.a==cor2.a;
}

PIG_Cor operator *(PIG_Cor cor, double fator){
    return {(uint8_t)cor.r*fator,(uint8_t)cor.g*fator,(uint8_t)cor.b*fator};
}

PIG_Cor operator +(PIG_Cor cor1,PIG_Cor cor2){
    return {(uint8_t)cor1.r*cor2.r,(uint8_t)cor1.g*cor2.r,(uint8_t)cor1.b*cor2.b};
}

//cria uma cor a partir de uma string com um valor hexadecimal de 8 algarismos RRGGBBAA. Ex: 0xFF0000FF (vermelho)
PIG_Cor PIGCriaCor(char *stringHexa){
    unsigned long total = strtoul(stringHexa,0,16);//transforma a string em um inteiro (decimal)
    PIG_Cor cor;
    cor.a = total %256;
    total /= 256;
    cor.b = total %256;
    total /= 256;
    cor.g = total %256;
    total /= 256;
    cor.r = total %256;
    return cor;
}

//multiplica as componentes RGB da cor pelo fator
PIG_Cor PIGMultiplicaCor(PIG_Cor cor, float valor){
    PIG_Cor resp = cor;
    resp.r *= valor;
    resp.g *= valor;
    resp.b *= valor;
    return resp;
}

//troca a posi��o dos bytes de uma word(16bits)
uint16_t PIGTroca2Bytes(uint16_t valor){
    return (valor/256)+((valor%256)*256);
}

//mistura duas cores com uma propor��o entre elas
PIG_Cor PIGMixCor(PIG_Cor iniCor, PIG_Cor fimCor, double porc){
    PIG_Cor resp;
    resp.r = fimCor.r*porc + (iniCor.r)*(1-porc);
    resp.g = fimCor.g*porc + (iniCor.g)*(1-porc);
    resp.b = fimCor.b*porc + (iniCor.b)*(1-porc);
    resp.a = fimCor.a*porc + (iniCor.a)*(1-porc);
    return resp;
}

//retorna o diretorio onde est� o execut�vel
std::string PIGGetDiretorioAtual(){
    char *dir = SDL_GetBasePath();
    if (dir){
        std::string resp(dir);
        CHDIR(dir);
        free(dir);
        return resp;
    }else return "./";
}

//retorna "valor" limitado entre [vMin, vMax]
int PIGLimitaValor(int valor, int minimo,int maximo){
    if (valor<minimo) return minimo; //valor n�o pode ficar menor que o m�nimo informado
    else if (valor>maximo) return maximo;//valor n�o pode ficar maior que o m�ximo informado
    else return valor;
}

double PIGLimitaValor(double valor, double minimo,double maximo){
    if (valor<minimo) return minimo; //valor n�o pode ficar menor que o m�nimo informado
    else if (valor>maximo) return maximo;//valor n�o pode ficar maior que o m�ximo informado
    else return valor;
}

//cria uma lista de strings contendo o nome do arquivos de um diret�rio
std::vector<std::string> PIGListaArquivosDiretorio(std::string path) {
   std::vector<std::string> resp;
   struct dirent *entry;
   DIR *dir = opendir(path.c_str());

   if (dir != NULL) {
       while ((entry = readdir(dir)) != NULL) {
        resp.push_back(entry->d_name);
       }
       closedir(dir);
   }
   return resp;
}

void PIGCalculaBoundingBox(int px[],int py[],int lados,int *altura,int *largura,int *centroX,int *centroY){
    int minX=INT_MAX,maxX=-1,minY=INT_MAX,maxY=-1;
    *centroX=0,*centroY=0;

    //calcula o bounding-box do poligono
    for (int i=0;i<lados;i++){
        if (px[i]<minX) minX = px[i];
        if (py[i]<minY) minY = py[i];
        if (px[i]>maxX) maxX = px[i];
        if (py[i]>maxY) maxY = py[i];
        *centroX += px[i]; //centro do poligono
        *centroY += py[i]; //centro do poligono
    }
    *centroX /= lados; //centro do poligono
    *centroY /= lados; //centro do poligono

    *altura = maxY-minY+1;  //altura absoluta do poligono
    *largura = maxX-minX+1; //altura absoluta do poligono
}

inline int PIGArredondaProximo(float valor) {
    int resultado = (int)valor;
    if (valor - resultado >= 0.5)
        return valor + 1;
    return valor;
}

inline double PIGProjecaoY(double coefAngular, PIGPonto2D p) {
    if (std::isinf(coefAngular))
        return (double)p.y;
    return coefAngular * (-p.x) + p.y;
}

inline double PIGProjecaoX(double coefAngular, PIGPonto2D p){//, bool swapei,std::vector<std::string> &vet) {
    if (std::isinf(coefAngular))
        return (double)p.x;
    /*if (!swapei){
        char str[100]="";
        sprintf(str,"PIGPROJX %f %f %f %f\n",coefAngular,coefAngular*p.x,-p.y + (coefAngular * p.x),(-p.y + (coefAngular * p.x)) / coefAngular);
    vet.push_back(str);
    }*/
    return (-p.y + (coefAngular * p.x)) / coefAngular;
}

inline double PIGMinVetor(double  vetor[], int tamVetor) {
    double  menor = vetor[0];
    for (int i = 1; i < tamVetor; i++)
        if (vetor[i] < menor)
            menor = vetor[i];
    return menor;
}

inline double PIGMaxVetor(double  vetor[], int tamVetor) {
    double  maior = vetor[0];
    for (int i = 1; i < tamVetor; i++)
        if (vetor[i] > maior)
            maior = vetor[i];
    return maior;
}



inline double PIGDistancia(PIGPonto2D a, PIGPonto2D b) {
    double deltaX = (b.x - a.x);
    double deltaY = (b.y - a.y);
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

inline bool PIGValorEntre(int x, int a, int b) {
    return ((x > a) && (x < b) || (x < a) && (x > b));
}

#endif // _PigFuncoesBasicas_
