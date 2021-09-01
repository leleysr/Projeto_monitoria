#include "PIG.h"
#include "Estruturas.h"

#define WIDTH 1000
#define HEIGHT 600
#define DELTA_TIME 0.016

PIG_Evento evento;          //evento ser tratadoi a cada pssada do loop principal
PIG_Teclado meuTeclado;     //variável como mapeamento do teclado


int main( int argc, char* args[] ){

    //criando o jogo (aplicação)
    CriaJogo("Meu Jogo",0,HEIGHT,WIDTH);

    fonte = CriaFonteNormal("../fontes/arial.ttf", 12,BRANCO);
    timer = CriaTimer(true);
    bool continuarChecando = false;

    //associando o teclado (basta uma única vez) com a variável meuTeclado
    meuTeclado = GetTeclado();

    Nivel nivel1 = Nivel(400,400,4,4,200,62);
    nivel1.criarBlocos(4);

    Nivel nivel2 = Nivel(500-192,225,8,16,384,108);
    nivel2.criarBlocos(16);

    Nivel nivel3 = Nivel(500-284,20,12,36,568,154);
    nivel3.criarBlocos(36);

    vector<Nivel *> Niveis = {&nivel1,&nivel2,&nivel3};
    //loop principal do jogo
    while(JogoRodando()){

        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e as coisas devem ser atualizadas

        //será feita aprepação do frame que será exibido na tela
        IniciaDesenho();

        nivel1.desenhaNivel();
        nivel1.desenharElementos();

        nivel2.desenhaNivel();
        nivel2.desenharElementos();

        nivel3.desenhaNivel();
        nivel3.desenharElementos();

        if(meuTeclado[PIG_TECLA_ENTER]){
            continuarChecando = true;
        }

        continuarChecando = Niveis[0]->procuraBloco(continuarChecando);


        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada
        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}

