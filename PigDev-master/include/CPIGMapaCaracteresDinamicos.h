#ifndef _CPIGMAPACARACTERESDINAMICOS_
#define _CPIGMAPACARACTERESDINAMICOS_

#include "CPIGStringFormatada.h"

class CPIGMapaCaracteresDinamicos:public CPIGMapaCaracteres{

private:

    //processa uma string para transform?-la em StringFormatada
    CPIGStringFormatada Processa(std::string textoOrig){
        CPIGStringFormatada resp;
        PIG_Cor cor = BRANCO;
        PIG_Estilo estilo = PIG_ESTILO_NORMAL;
        int larguraTotal = 0;
        int estado = 0;//estado atual da m?quinda de estados
        int i = 0;

        std::vector<PIG_Cor> pilhaCor;
        std::vector<PIG_Estilo> pilhaEstilo;
        pilhaCor.push_back(cor);
        pilhaEstilo.push_back(estilo);

        Uint16 letra,letraAnt;

        while (i<textoOrig.size()){
            letraAnt = letra;
            letra = textoOrig[i];
            letra = letra %256;

            switch (estado){
            case 0://estado sem formatacao
                if (letra == '<'){//alerta de entrada de formatacao
                   estado = 1;
                }else if (letra=='@'){//alerta de sa?da de cor
                    estado = 3;
                }else if (letra==PIG_SIMBOLO_NEGRITO||letra==PIG_SIMBOLO_ITALICO||letra==PIG_SIMBOLO_SUBLINHADO||letra==PIG_SIMBOLO_CORTADO){//alerta de sa?da de negrito, it?lico, underline ou strike
                    estado = 4;
                }else{
                    larguraTotal += larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                break;
            case 1://alerta para inicio de formatacao
                if (letra == '@'){//realmente ? entrada de cor
                    estado = 2;
                }else if (letra == PIG_SIMBOLO_NEGRITO){//negrito
                    estilo |= PIG_ESTILO_NEGRITO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_ITALICO){
                    estilo |= PIG_ESTILO_ITALICO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_SUBLINHADO){
                    estilo |= PIG_ESTILO_SUBLINHADO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else if (letra == PIG_SIMBOLO_CORTADO){
                    estilo |= PIG_ESTILO_CORTADO;
                    pilhaEstilo.push_back(estilo);
                    estado = 0;
                }else{//n?o ? entrada de cor nem de formatacao de estilo
                    larguraTotal += larguraLetra[estilo][letraAnt-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);

                    estado = 0;
                }
                break;
            case 2://reconhecimento da cor
                char stringCor[11];
                strncpy(stringCor,&textoOrig[i],10); //pega os caracteres em hexadecimal (ex: 0xffa64312)
                stringCor[10]='\0';

                i+=9;//avan?a os outros 9 caracteres
                cor = PIGCriaCor(stringCor);//converte para cor
                pilhaCor.push_back(cor);
                estado = 0;
                break;
            case 3://alerta para saida de cor
                if (letra == '>'){//realmente sa?da da cor
                    pilhaCor.pop_back();
                    if (pilhaCor.size()>1)//tira a cor da pilha e pega a de baixo
                        cor = pilhaCor[pilhaCor.size()-1];
                    else cor = BRANCO;
                }else{//n?o ? sa?da de cor
                    larguraTotal += larguraLetra[estilo][letraAnt-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                estado = 0;
                break;
            case 4://saida de negrito, it?lico, underline ou strike
                if (letra=='>'){
                    pilhaEstilo.pop_back();
                    if (pilhaEstilo.size()>1)//tira a cor da pilha e pega a de baixo
                        estilo = pilhaEstilo[pilhaEstilo.size()-1];
                    else estilo = PIG_ESTILO_NORMAL;
                }else{//n?o ? sa?da de cor
                    larguraTotal += larguraLetra[estilo][letraAnt-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letraAnt,larguraTotal,cor,estilo);//devolve o token anterior

                    larguraTotal += larguraLetra[estilo][letra-PIG_PRIMEIRO_CAR];
                    resp.Adiciona(letra,larguraTotal,cor,estilo);
                }
                estado = 0;
                break;
            }
            i++;
        }
        //system("pause");
        pilhaCor.clear();
        pilhaEstilo.clear();

        return resp;
    }

public:

    //construtor com o nome do arquivo da fonte, o tamanha e a janela
    CPIGMapaCaracteresDinamicos(char *nomeFonte, int tamanhoFonte, int idJanela):CPIGMapaCaracteres(nomeFonte,tamanhoFonte,PIG_ESTILO_NORMAL,BRANCO,idJanela){
        //IniciaBase(nomeFonte,tamanhoFonte,idJanela, -1);

        for (int estilo=1;estilo<PIG_TOTALESTILOS;estilo++)
            CriaLetrasSurface(estilo, 0, BRANCO, NULL, BRANCO);

        SDL_SetRenderTarget(render, NULL);
    }

    //escreve uma string j? formatada, alinhada com o ponto x,y e o par?metro pos
    void Escreve(CPIGStringFormatada formatada,int x,int y,PIG_PosTexto pos=PIG_TEXTO_ESQUERDA,float ang=0,int alvoTextura=0){
        int delta = 0;
        switch(pos){
        case PIG_TEXTO_ESQUERDA:
            break;
        case PIG_TEXTO_DIREITA:
            //EscreveStringEsquerda(texto,x-formatada.LargTotalPixels(),y,ang,formatada.LargTotalPixels());break;
            x -= formatada.LargTotalPixels();delta = formatada.LargTotalPixels();break;
        case PIG_TEXTO_CENTRO:
            //EscreveStringEsquerda(texto,x-formatada.LargTotalPixels()/2,y,ang,formatada.LargTotalPixels()/2);break;
            x -= formatada.LargTotalPixels()/2;delta = formatada.LargTotalPixels()/2;break;
        }

        SDL_Rect rectDestino;
        rectDestino.x = x;
        int *altJanela = CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura();
        //rectDestino.y = CGerenciadorJanelas::GetJanela(janela)->GetAltura()-y-tamFonte;
        PIG_Cor corAtual = BRANCO;
        PIG_Estilo estiloAtual = PIG_ESTILO_NORMAL;
        SDL_Point ponto = {delta,tamFonte};

        for (int i=0;i<formatada.size();i++){
            Uint16 aux = formatada.GetLetra(i);
            aux = aux %256;
            if (aux-PIG_PRIMEIRO_CAR<0) continue;
            corAtual = formatada.GetCor(i);
            estiloAtual = formatada.GetEstilo(i);

            if (alvoTextura)
                SDL_SetTextureBlendMode(glyphsT[estiloAtual][aux-PIG_PRIMEIRO_CAR], SDL_BLENDMODE_NONE);
            else SDL_SetTextureBlendMode(glyphsT[estiloAtual][aux-PIG_PRIMEIRO_CAR], SDL_BLENDMODE_BLEND);

            SDL_SetTextureColorMod(glyphsT[estiloAtual][aux-PIG_PRIMEIRO_CAR],corAtual.r,corAtual.g,corAtual.b);

            rectDestino.w = larguraLetra[estiloAtual][aux-PIG_PRIMEIRO_CAR];
            rectDestino.h = tamFonte+alturaExtra[estiloAtual][aux-PIG_PRIMEIRO_CAR];
            rectDestino.y = *altJanela-y-rectDestino.h;

            SDL_RenderCopyEx(render,glyphsT[estiloAtual][aux-PIG_PRIMEIRO_CAR],NULL,&rectDestino,-ang,&ponto,PIG_FLIP_NENHUM);

            rectDestino.x += rectDestino.w;
            ponto.x -= rectDestino.w;
        }
    }

    //escreve ums string normal, alinha com o ponto x,y e o par?metro pos
    void Escreve(std::string texto,int x,int y,PIG_Cor cor=BRANCO,PIG_PosTexto pos=PIG_TEXTO_ESQUERDA,float ang=0,int alvoTextura=0)override{
        if (texto=="") return;
        CPIGStringFormatada formatada = Processa(texto);
        Escreve(formatada,x,y,pos,ang,alvoTextura);
    }

    void Escreve(std::string texto,SDL_Texture *textura,PIG_Cor cor){
        SDL_SetRenderTarget(render,textura);
        SDL_SetRenderDrawColor(render,0,0,0,0);
        int *altJanela = CPIGGerenciadorJanelas::GetJanela(janela)->GetAltura();

        SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(textura,cor.r,cor.g,cor.b);

        Escreve(texto,0,*altJanela-tamFonte+fontDescent,cor,PIG_TEXTO_ESQUERDA,0,1);

        SDL_SetRenderTarget(render, NULL);
    }

    //escreve uma string longa (m?ltiplas linhas), incluindo formata??o interna, alinhada de acordo com o ponto x,y e o par?metro pos
    void EscreveLonga(std::string texto,int x,int y,int largMax,int espacoEntreLinhas,PIG_Cor corFonte=BRANCO,PIG_PosTexto pos=PIG_TEXTO_ESQUERDA,float angulo=0) override{
        if (texto=="") return;
        CPIGStringFormatada formatada = Processa(texto);
        //formatada.Print();
        std::vector<CPIGStringFormatada> linhas = formatada.ExtraiLinhas(largMax,delimitadores);
        EscreveLonga(linhas,x,y,espacoEntreLinhas,pos,angulo);
        linhas.clear();
        formatada.Clear();
    }

    //escreve uma string longa (m?ltiplas linhas), com formata??o j? processada e fornecida, alinhada de acordo com o ponto x,y e o par?metro pos
    void EscreveLonga(std::vector<CPIGStringFormatada> linhas, int x, int y, int espacoEntreLinhas,PIG_PosTexto pos=PIG_TEXTO_ESQUERDA,float angulo=0){
        int yTotal=y;
        for (int k=0;k<linhas.size();k++){
            Escreve(linhas[k],x,yTotal,pos,angulo);
            yTotal -= espacoEntreLinhas;
        }
    }

    //retorna a largura em pixels da string fornecida (faz a formata??o internamente)
    int GetLarguraPixelsString(std::string texto) override{
        if (texto=="") return 0;
        CPIGStringFormatada formatada = Processa(texto);
        int resp = formatada.LargTotalPixels();
        formatada.Clear();
        return resp;
    }

    //retorna as linhas j? formatadas e organizadas pela largura m?xima fornecida
    std::vector<CPIGStringFormatada> ExtraiLinhas(std::string texto, int largMax){
        CPIGStringFormatada formatada = Processa(texto);
        std::vector<CPIGStringFormatada> linhas = formatada.ExtraiLinhas(largMax,delimitadores);
        formatada.Clear();
        return linhas;
    }
};

typedef CPIGMapaCaracteresDinamicos* PIGMapaCaracteresDinamicos;

#endif //_CPIGMAPACARACTERESDINAMICOS_
