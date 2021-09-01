#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_net.h"
#include "SDL_mixer.h"

#include "PIGTipos.h"
#include "PIGFuncoesBasicas.h"
#include "CPIGErros.h"

#include "CPIGRepositorio.h"
#include "CPIGGerenciadorTimers.h"
#include "CPIGAssetLoader.h"
#include "CPIGOffscreenRenderer.h"
#include "CPIGGerenciadorAudios.h"
#include "CPIGGerenciadorJanelas.h"
#include "CPIGGerenciadorSockets.h"
#include "CPIGGerenciadorFontes.h"
#include "CPIGGerenciadorSprites.h"
#include "CPIGGerenciadorGDP.h"
#ifdef PIGCOMVIDEO
#include "CPIGGerenciadorVideos.h"
#endif
#include "CPIGGerenciadorControles.h"
#include "CPIGGerenciadorForms.h"
#include "CPIGJogo.h"


/********************************
/ Vari�veis Globais
/********************************/
PIGJogo jogo=NULL;

/********************************
A fun��o CriaJogo() � respons�vel pela cria��o da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra fun��o da biblioteca PIG.h. N�o � poss�vel criar dois
jogos no mesmo progama. Logo, somente a primeira chamada ter� efeito. A janela padr�o da aplica��o ter� o tamanho definido pelas constantes PIG_ALT_TELA e PIG_LARG_TELA
definidas no arquivo PIGTipos.h, exceto se forem passados outros valores.
Par�metros:
nomeJanela (entrada, passagem por refer�ncia*): indica o nome que a janela do jogo mostrar� no seu t�tulo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
cursorProprio (entrada, passagem por valor): indica se o jogo utilizar� cursores (ponteiros) pr�prios para o mouse ou utilizar� o cursor padr�o.
altura (entrada, passagem por valor n�o-obrigat�rio): indica a altura em pixels da janela principal do jogo.
largura (entrada, passagem por valor n�o-obrigat�rio): indica a largura em pixels da janela principal do jogo.
********************************/
/**
 *  \brief Cria o jogo.
 *
 *  \param nomeJanela   T�tulo da janela do jogo.
 *  \param cursorProrio Se diferente de zero, indica que o usu�rio definir� cursores
 *  \param altura       Altura da tela do jogo
 *  \param largura      Largura da tela do jogo
 *
 *
 *  \sa FinalizaJogo()
 */
void CriaJogo(char *nomeJanela,int cursorProprio=0,int altura=PIG_ALT_TELA,int largura=PIG_LARG_TELA){
    if (jogo==NULL){
        jogo = new CPIGJogo(nomeJanela,cursorProprio,altura,largura);
        CPIGAssetLoader::Inicia();
        CPIGMouse::Inicia(cursorProprio);
        CPIGGerenciadorSprites::Inicia();
        CPIGGerenciadorGDP::Inicia();
        CPIGGerenciadorFontes::Inicia();
        CPIGGerenciadorTimers::Inicia();
        CPIGGerenciadorAudios::Inicia();
        CPIGGerenciadorControles::Inicia();
        CPIGGerenciadorSockets::Inicia();
        #ifdef PIGCOMVIDEO
        CPIGGerenciadorVideos::Inicia();
        #endif
        CPIGGerenciadorForms::Inicia();
    }
}

/********************************
A fun��o SetValorIntJogo() � respons�vel incorporar ao jogo um atributo inteiro.
Par�metros:
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao jogo.
********************************/
void SetValorIntJogo(int indice,int valor){
    jogo->SetValorInt(indice,valor);
}

/********************************
A fun��o SetValorFloatJogo() � respons�vel incorporar ao jogo um atributo float.
Par�metros:
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao jogo.
********************************/
void SetValorFloatJogo(int indice,float valor){
    jogo->SetValorFloat(indice,valor);
}

/********************************
A fun��o SetValorIntJogo() � respons�vel incorporar ao jogo um atributo inteiro.
Par�metros:
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado ao jogo.
********************************/
void SetValorStringJogo(int indice,char *valor){
    jogo->SetValorString(indice,valor);
}

/********************************
A fun��o SetValorIntJogo() � respons�vel incorporar ao jogo um atributo inteiro.
Par�metros:
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao jogo.
********************************/
void SetValorIntJogo(char *indice,int valor){
    jogo->SetValorInt(indice,valor);
}

/********************************
A fun��o SetValorFloatJogo() � respons�vel incorporar ao jogo um atributo float.
Par�metros:
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao jogo.
********************************/
void SetValorFloatJogo(char *indice,float valor){
    jogo->SetValorFloat(indice,valor);
}

/********************************
A fun��o SetValorIntJogo() � respons�vel incorporar ao jogo um atributo inteiro.
Par�metros:
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado ao jogo.
********************************/
void SetValorStringJogo(char *indice,char *valor){
    jogo->SetValorString(indice,valor);
}

/********************************
A fun��o GetValorIntJogo() � respons�vel recuperar o valor de um atributo inteiro relacionado ao jogo.
Par�metros:
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntJogo(int indice,int *valor){
    return jogo->GetValorInt(indice,*valor);
}

/********************************
A fun��o GetValorFloatJogo() � respons�vel recuperar o valor de um atributo float relacionado ao jogo.
Par�metros:
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatJogo(int indice,float *valor){
    return jogo->GetValorFloat(indice,*valor);
}

/********************************
A fun��o GetValorStringJogo() � respons�vel recuperar o valor de um atributo string relacionado ao jogo.
Par�metros:
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringJogo(int indice,char *valor){
    std::string str;
    bool resp = jogo->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A fun��o GetValorIntJogo() � respons�vel recuperar o valor de um atributo inteiro relacionado ao jogo.
Par�metros:
indice (entrada, passagem por refer�ncia): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntJogo(char *indice,int *valor){
    return jogo->GetValorInt(indice,*valor);
}

/********************************
A fun��o GetValorFloatJogo() � respons�vel recuperar o valor de um atributo float relacionado ao jogo.
Par�metros:
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatJogo(char *indice,float *valor){
    return jogo->GetValorFloat(indice,*valor);
}

/********************************
A fun��o GetValorStringJogo() � respons�vel recuperar o valor de um atributo string relacionado ao jogo.
Par�metros:
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringJogo(char *indice,char *valor){
    std::string str;
    bool resp = jogo->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A fun��o GetEstadoJogo() indica o estado do jogo. Este estado � apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Retorno:
inteiro indicando o valor do estado do jogo.
********************************/
//int GetEstadoJogo(){
//    return jogo->GetEstado();
//}

/********************************
A fun��o SetEstadoJogo() atribui um novo valor ao estado do jogo. Este estado � apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Par�metro:
estado (entrada, passagem por valor): indica o novo estado do jogo;
********************************/
//void SetEstadoJogo(int estado){
//    jogo->SetEstado(estado);
//}

/********************************
A fun��o DefineFundoJanela() permite escolher um arquivo de imagem como fundo (background) de uma janela que ser� automaticamente desenhado a cada nova etapa de desenho na tela.
Par�metros:
nomeArquivoImagem (entrada, passagem por refer�ncia*): indica o caminho relativo ou absoluto do arquivo de imagem que ser� utilizado como fundo do jogo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
idJanela (entrada, passagem por valor n�o-obrigatorio): indica de qual janela � a imagem.
********************************/
void DefineFundo(char *nomeArquivoImagem,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DefineFundo(nomeArquivoImagem);
}

/********************************
A fun��o GetTeclado() faz um mapeamento entre o teclado f�sico a uma vari�vel do tipo PIG_Teclado que funciona como um vetor de vari�veis l�gicas,
sendo cada posi��o do vetor relativo a uma tecla f�sica.
Uma lista das poss�veis teclas e seus c�digo pode ser vista no arquivo Tipos_PIG.h.
Retorno:
O valor de retorno da fun��o � um vetor de n�meros inteiros que indicam se uma determinada tecla (�ndice do vetor) foi
pressionada (valor diferente de 0,zero) ou n�o (valor igual a zero).
********************************/
PIG_Teclado GetTeclado(){
    return jogo->PegaTeclado();
}

/********************************
A fun��o GetEvento() indica se houve algum tipo de evento desde a �ltima vez que a fun��o foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada � tela do jogo.
Maiores informa��e podem ser vistas no arquivo PIGTipos.h
Retorno:
O valor de retorno � um struct contendo o tipo de evento ocorrido e v�rios outros structs com informa��es espec�ficas.
********************************/
PIG_Evento GetEvento(){
    return jogo->PegaEvento();
}

/********************************
A fun��o IniciaDesenho() � respons�vel por preparar a janela do jogo para que os objetos gr�ficos
possam ser mostrados, al�m de desenhar a imagem de fundo do jogo, caso tenha sido definida.
Deve ser chamada repetidamente a cada novo quadro (frame) a ser desenhado.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela deve preparar a renderiza��o. O valor (-1) indica que todas as janelas devem ser preparadas.
********************************/
void IniciaDesenho(int idJanela=-1){
    jogo->IniciaDesenho(idJanela);
}

/********************************
A fun��o EncerraDesenho() � respons�vel por encerrar o desenho que foi criado, mostrando na janela do jogo.
Deve ser chamado sempre ao final do loop principal do jogo.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela deve preparar a renderiza��o. O valor (-1) indica que todas as janelas devem ser exibidas.
********************************/
void EncerraDesenho(int idJanela=-1){
    CPIGMouse::Desenha();
    jogo->EncerraDesenho(idJanela);
}

/********************************
A fun��o SalvaTela() � respons�vel por criar um arquivo Bitmap, contendo uma c�pia de uma janela do jogo naquele momento.
Par�metros:
nomeArquivoBMP (entrada, passagem por refer�ncia*): indica o nome do arquivo Bitmap que ser� salvo. O valor do par�metro deve conter a extens�o ".bmp".
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela deve ter a imagem salva.
********************************/
void SalvaTela(char *nomeArquivoBMP,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SaveScreenshot(nomeArquivoBMP,true);
}

/********************************
A fun��o JogoRodando() � repons�vel por retornar se o jogo ainda est� ativo ou n�o.
O jogo ser� encerrado se a janela do jogo for fechada, por exemplo.
Retorno:
inteiro que indica se o jogo ainda est� sendo executado (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int JogoRodando(){
    return jogo->GetRodando();
}

/********************************
A fun��o Espera() "congela" a tela do jogo por alguns milissegundos, impedindo que qualquer outro comando seja executado enquanto isso.
Par�metros:
tempo (entrada, passagem por valor): indica a quantidade de milissegundos durante a qual o jogo ser� pausado.
********************************/
void Espera(int tempo){
    SDL_Delay(tempo);
}

/********************************
A fun��o FinalizaJogo() � respons�vel por encerrar com a PIG. Ap�s tudo o jogo ser executado
a fun��o deve ser chamada e ela ir� realizar a libera��o de mem�ria dos elementos criados pela PIG.
********************************/
void FinalizaJogo(){
    CPIGGerenciadorControles::Encerra();
    CPIGGerenciadorFontes::Encerra();
    CPIGGerenciadorAudios::Encerra();
    #ifdef PIGCOMVIDEO
    CPIGGerenciadorVideos::Encerra();
    #endif
    CPIGGerenciadorSockets::Encerra();
    CPIGGerenciadorForms::Encerra();
    CPIGGerenciadorSprites::Encerra();
    CPIGGerenciadorGDP::Encerra();
    CPIGGerenciadorTimers::Encerra();
    CPIGMouse::Encerra();
    CPIGAssetLoader::Encerra();
    delete jogo;
}

/********************************
A fun��o GetFPS() � respons�vel por calcular o valor do Frames Per Seconds (FPS), que representa a quantidade de
frames (quadros) desenhados por segundo pela PIG.
Retorno:
float que indica a m�dia de quadros desenhados por segundo.
********************************/
float GetFPS(){
    return jogo->GetFPS();
}

/********************************
A fun��o CarregaCursor() � respons�vel por armazenar um novo cursor para o mouse, dado pelo arquivo de imagem indicado.
O arquivo deve ser uma imagem com 32 pixels de altura orbigatoriamente.
Par�metro:
nomeArquivoCursor (entrada, passagem por refer�ncia*): indica o nome do arquivo de imagem que ser� utilziado como cursor do mouse.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void CarregaCursor(char *nomeArquivoCursor, int idJanela=0){
    CPIGMouse::CarregaCursor(nomeArquivoCursor,idJanela);
}

/********************************
A fun��o CriaFrameCursor() � respons�vel por delimitar a �rea do arquivo de imagem para um cursor espec�fico.
Idealmente, a altura e largura informadas devem ter tamanho igual a 32 pixels (para n�o haver perda de qualidade na exibi��o do cursor).
Par�metro:
idFrame (entrada, passagem por valor): n�mero inteiro associado ao cursor (�rea do arquivo de imagem) em quest�o.
xBitmap (entrada, passagem por valor): indica a posi��o de eixo X onde come�a o frame.
yBitmap (entrada, passagem por valor): indica a posi��o de eixo Y onde come�a o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameCursor(int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGMouse::CriaFrameCursor(idFrame,xBitmap,yBitmap,altura,largura);
}

/********************************
A fun��o CarregaFramesPorLinhaCursor() � respons�vel por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivis�o representar� um frame que ser� automaticamente criado para o cursor do mouse, com numera��o incremental a partir do par�metro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a defini��o dos frames continua na linha inferior.
A fun��o pode ser utilizada em spritesheets regulares.
Par�metros:
frameInicial (entrada, passagem por valor): numera��o do primeiro frame a ser criado pela fun��o. Os demais frames ter�o numera��o consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem ser� dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem ser� dividido.
********************************/
void CarregaFramesPorLinhaCursor(int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGMouse::CarregaFramesPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A fun��o CarregaFramesPorColunaCursor() � respons�vel por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivis�o representar� um frame que ser� automaticamente criado para o cursor do mouse, com numera��o incremental a partir do par�metro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a defini��o dos frames continua na coluna seguinte.
A fun��o pode ser utilizada em spritesheets regulares.
Par�metros:
frameInicial (entrada, passagem por valor): numera��o do primeiro frame a ser criado pela fun��o. Os demais frames ter�o numera��o consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem ser� dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem ser� dividido.
********************************/
void CarregaFramesPorColunaCursor(int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGMouse::CarregaFramesPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A fun��o MudaCursor() � respons�vel por alterar o cursor atual do mouse por outro j� definido (fun��o DefineFrameCursor).
Par�metro:
idFrame (entrada, passagem por valor): informa o identificador de um cursor (frame) j� criado.
Retorno:
Se o identifador informado n�o corresponder a um frame j� criado, o valor de retorno � igual a 0. Caso contr�rio, � igual a 1.
********************************/
int MudaCursor(int idFrame){
    return CPIGMouse::MudaCursor(idFrame);
}


/********************************
A fun��o GetEstadoBotaoMouse() � respons�vel por recuperar o eatado atual de um dos botoes (PIG_MOUSE_DIREITO, PIG_MOUSE_CENTRAL ou PIG_MOUSE_RODINHA) do mouse.
O valor retornado pode ser PIG_MOUSE_PRESSIONADO ou PIG_MOUSE_LIBERADO.
Retorno:
inteiro que indica a o estado atual do bot�o do mouse solicitado.
********************************/
int GetEstadoBotaoMouse(int botao){
    return CPIGMouse::GetEstadoBotao(botao);
}

/********************************
A fun��o ExecutaBackground() � respons�vel por executar uma fun��o em bckground, ou seja, fora do fluxo principal de execu��o do programa.
Essa execu��o � feita por outra Thread, com suporte do Sistema Operacional
Par�metros:
dados (entrada, passagem por refer�ncia): ponteiro gen�rico para qualquer tipo de dado a ser utilizado na fun��o.
********************************/
void ExecutaBackground(PIG_FuncaoBackground funcao,void *dados){
    SDL_CreateThread(funcao,"",dados);
}


/********************************
Se��o de tratamento de janelas
********************************/

/********************************
A fun��o GetQtdJanela() � respons�vel por calcular quantas janelas est�o criadas pelo jogo, incluindo as que est�o minimizadas ou escondidas.
Retono:
inteiro que representa a quantidade de janelas ainda abertas pelo jogo, incluindo as que est�o minimizadas ou escondidas.
********************************/
int GetQtdJanelas(){
    return CPIGGerenciadorJanelas::GetQtdJanelas();
}

/********************************
A fun��o CriaJanela() � respons�vel por criar e exibir uma nova janela para a aplica��o. O identificador num�rico da nova janela � retornado como par�metro.
Se n�o foi poss�vel criar a janela, o valor de retorno ser� -1. Existe um limite m�ximo de janela que podem ser criadas. Esse limite � dado pelo par�metro MAX_JANELAS configurado na Tipos_PIG.h.
O valor da janela original (padr�o) � sempre igual a 0 (zero). Para se desenhar qualquer coisa nas janelas adicionais, � preciso criar objetos, anima��es, geradores de part�culas e fontes
especificando-se a janela na qual estes elementos ser�o renderizados. Ao utilizar-se janelas adicionais, tamb�m � poss�vel estipular individualmente quais janelas ser�o preparadas e mostradas, utilizando o
n�mero da janela nas chamadas das fun��es IniciaDesenho e EncerraDesenho. Caso n�o seja especificado o n�mero, todas as janelas s�o preparadas e mostradas, respectivamente.
Par�metros:
nomeJanela (entrada, passagem por refer�ncia*): indica o nome que a nova janela mostrar� no seu t�tulo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
altura (entrada, passagem por valor n�o-obrigat�rio): indica a altura em pixels da janela a ser criada.
largura (entrada, passagem por valor n�o-obrigat�rio): indica a largura em pixels da janela a ser criada.
Retorno
inteiro que representa o n�mero de identifica��o dessa janela. esse n�mero deve ser utilizado sempre que um comando deva ser executado para uma janela espec�fica.
A janela padr�o da aplica��o possui sempre o n�mero 0 (zero).
********************************/
int CriaJanela(char *nomeJanela,int altura=PIG_ALT_TELA,int largura=PIG_LARG_TELA){
    return CPIGGerenciadorJanelas::CriaJanela(nomeJanela,altura,largura);
}

/********************************
A fun��o FechaJanela() � respons�vel por fechar uma janela. As renderiza��es nessa janela que ocorrerem posteriormente n�o ter�o qualquer efeito.
A janela fechada vai deixar de gerar eventos, mas n�o poderpa ser reaberta. O efeito de reabrir um janela pode ser obtido com os comandos EscondeJanela() e ExibeJanela().
Par�metros:
idJanela (entrada, passagem por valor): indica o n�mero da janela a ser fechada.
********************************/
void FechaJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Fecha();
}

/********************************
A fun��o EscondeJanela() � respons�vel por fazer a janela deixar de ser vis�vel, mas n�o a fecha de forma definitiva.
A janela poder� ser reaberta com a fun��o ExibeJanela().
Par�metros:
idJanela (entrada, passagem por valor): indica o n�mero da janela a ser oculta.
********************************/
void EscondeJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Esconde();
}

/********************************
A fun��o ExibeJanela() � respons�vel por fazer a janela voltar a ser vis�vel, mas n�o faz automaticamente a janela ter o foco para gerar eventos.
A janela poder� ser reaberta com foca por meio da fun��o GanhaFocoJanela().
Par�metros:
idJanela (entrada, passagem por valor): indica o n�mero da janela a ser reexibida sem foco.
********************************/
void ExibeJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Exibe();
}

/********************************
A fun��o GanhaFocoJanela() � respons�vel por fazer a janela voltar a ser vis�vel e automaticamente voltar a ter o foco para gerar eventos.
Par�metros:
idJanela (entrada, passagem por valor): indica o n�mero da janela a ser reexibida com foco.
********************************/
void GanhaFocoJanela(int idJanela){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->GanhaFoco();
}

/********************************
A fun��o GetAlturaJanela() � respons�vel por recuperar a altura da janela em pixels.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser consultada.
Retorno:
inteiro que representa a altura da janela em pixels.
********************************/
int *GetAlturaJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
}

/********************************
A fun��o GetLarguraJanela() � respons�vel por recuperar a largura da janela em pixels.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser consultada.
Retorno:
inteiro que representa a largura da janela em pixels.
********************************/
int GetLarguraJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetLargura();
}


/********************************
A fun��o SetTamanhoJanela() � respons�vel por definir o tamanho para a janela.
Par�metros:
altura (entrada, passagem por valor): indica a quantidade de linhas da janela (em pixels).
largura (entrada, passagem por valor): indica a quantidade de colunas da janela (em pixels).
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void SetTamanhoJanela(int altura, int largura,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetTamanho(altura,largura);
}

/********************************
A fun��o SetAfastamentoCamera() � respons�vel por afastar ou aproximar a c�mera dos objetos da tela, em um eixo perpendicular.
O valor de afastamento deve variar entre PIG_AFASTAMENTO_MINIMO (0.1) e PIG_AFASTAMENTO_MAXIMO (100).
Quanto maior for o valor, mais "afastada" estar� a c�mera dos objetos. O valor padr�o � 1.0.
Par�metros:
afastamento (entrada, passagem por valor): indica o afastamento da c�mera em rela��o ao plano representado pela tela.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
Retorno:
O valor retornado � igual ao afastamento ap�s a execu��o da fun��o.
********************************/
double SetAfastamentoCamera(double afastamento,int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->SetAfastamento(afastamento);
}

/********************************
A fun��o GetAfastamentoCamera() recupera o valor atual de afastamento da c�mera.
O valor de afastamento deve variar entre PIG_AFASTAMENTO_MINIMO (0.1) e PIG_AFASTAMENTO_MAXIMO (100).
Quanto maior for o valor, mais "afastada" estar� a c�mera dos objetos. O valor padr�o � 1.0.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
Retorno:
O valor retornado � igual ao afastamento atual da c�mera.
********************************/
double GetAfastamentoCamera(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAfastamento();
}

/********************************
A fun��o MoveCamera() � respons�vel por reposicionar a c�mera no cen�rio. O ponto de refer�ncia � o canto inferior esquerdo da tela.
Todos os objetos ser�o automaticamente recolocados na tela conforme a posi��o da c�mera.
Par�metros:
posicaoX (entrada, passagem por valor): indica a posi��o no eixo X onde a c�mera ficar�.
posicaoY (entrada, passagem por valor): indica a posi��o no eixo Y onde a c�mera ficar�.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void MoveCamera(int posicaoX, int posicaoY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->MoveCamera(posicaoX,posicaoY);
}

/********************************
A fun��o DeslocaCamera() � respons�vel por deslocar a c�mera em rela��o � sua posi��o atual.
Par�metros:
deltaX (entrada, passagem por valor): valor a ser somado ou subtra�do na componente X da posi��o da c�mera.
deltaY (entrada, passagem por valor): valor a ser somado ou subtra�do na componente Y da posi��o da c�mera.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void DeslocaCamera(int deltaX, int deltaY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DeslocaCamera(deltaX,deltaY);
}

/********************************
A fun��o GetXYCamera() � respons�vel recuperar o valor da posi��o (X,Y) da c�mera de acordo com o sistema de coordenadas do jogo.
Par�metros:
posicaoX (sa�da, passagem por referencia): indica a posicao no eixo X da c�mera.
posicaoY (sa�da, passagem por referencia): indica a posicao no eixo Y da c�mera.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela.
********************************/
void GetXYCamera(int *posicaoX, int *posicaoY, int idJanela=0){
    SDL_Point p = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetPosicaoCamera();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o PreparaCameraMovel() � respons�vel utilizar a c�mera movel relativa � janela em quest�o.
A c�mera m�vel est� sujeita � movimenta��es e ajuste de zoom (afastamento). Todas as renderiza��es posteriores estar�o sujeitas a essas transforma��es.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela.
********************************/
void PreparaCameraMovel(int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->PreparaCameraMovel();
}

/********************************
A fun��o PreparaCameraFixa() � respons�vel utilizar a c�mera fixa relativa � janela em quest�o.
A c�mera fixa n�o est� sujeita � movimenta��es e ajuste de zoom (afastamento). Todas as renderiza��es posteriores ser�o feitas utilizando o sistema de coordenadas da tela.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela.
********************************/
void PreparaCameraFixa(int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->PreparaCameraFixa();
}

/********************************
A fun��o ConverteCoordenadaDaTelaParaMundo() transforma uma coordenada da tela para uma coordenada do cen�rio, de acordo com o afastamento e a posi��o da c�mera e do sistema de coordenadas do jogo.
Par�metros:
telaX (entrada, passagem por valor): indica a componente X da coordenada da tela em quest�o.
telaY (entrada, passagem por valor): indica a componente Y da coordenada da tela em quest�o.
mundoX (sa�da, passagem por referencia): indica a componente X da coordenada do cen�rio.
mundoY (sa�da, passagem por referencia): indica a componente Y da coordenada do cen�rio.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela.
********************************/
void ConverteCoordenadaDaTelaParaMundo(int telaX, int telaY, int *mundoX, int *mundoY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaScreenWorld(telaX, telaY, *mundoX, *mundoY);
}

/********************************
A fun��o ConverteCoordenadaDoMundoParaTela() transforma uma coordenada do cen�rio para uma coordenada da tela, de acordo com o afastamento e a posi��o da c�mera e do sistema de coordenadas do jogo.
Par�metros:
mundoX (entrada, passagem por valor): indica a componente X da coordenada do cen�rio em quest�o.
mundoY (entrada, passagem por valor): indica a componente Y da coordenada do cen�rio em quest�o.
telaX (sa�da, passagem por referencia): indica a componente X da coordenada da tela.
telaY (sa�da, passagem por referencia): indica a componente Y da coordenada da tela.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela.
********************************/
void ConverteCoordenadaDoMundoParaTela(int mundoX, int mundoY, int *telaX, int *telaY, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(mundoX, mundoY, *telaX, *telaY);
}

/********************************
A fun��o GetTituloJanela() � respons�vel por recuperar o t�tulo (caption) atual da janela.
Par�metros:
tituloJanela (sa�da, passagem por refer�ncia): armazena o t�tulo da janela que foi recuperado.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser consultada.
********************************/
void GetTituloJanela(char *tituloJanela,int idJanela=0){
    strcpy(tituloJanela,CPIGGerenciadorJanelas::GetJanela(idJanela)->GetTitulo().c_str());
}

/********************************
A fun��o SetTituloJanela() � respons�vel por definir um novo t�tulo (caption) para a janela.
Par�metros:
novoTitulo (entrada, passagem por refer�ncia*): indica o novo t�tulo para a janela.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterada dentro da fun��o.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void SetTituloJanela(char *novoTitulo,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetTitulo(novoTitulo);
}

/********************************
A fun��o GetCorFundoJanela() � respons�vel por recuperar uma cor de fundo para a janela indicada. A cor de fundo ser� utilizada como background autom�tico quando a janela for preparada para renderiza��es.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
Retorno
cor contendo os componentes RGBA da cor utilizada para pintar automaticamente o fundo da janela.
********************************/
PIG_Cor GetCorFundoJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetCorFundo();
}

/********************************
A fun��o SetCorFundoJanela() � respons�vel por definir uma cor de fundo para a janela indicada. A cor de fundo ser� utilizada como background autom�tico quando a janela for preparada para renderiza��es.
Par�metros:
cor (entrada, passagem por valor): indica a cor para o fundo da janela.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void SetCorFundoJanela(PIG_Cor cor,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetCorFundo(cor);
}

/********************************
A fun��o GetOpacidadeJanela() � respons�vel por recuperar o n�vel de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
Retorno:
n�mero real que indica o n�vel de opacidade da janela, variando entre 1.0 e 0.
********************************/
float GetOpacidadeJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetOpacidade();
}

/********************************
A fun��o SetOpacidadeJanela() � respons�vel por definir o n�vel de opacidade de uma janela. A opacidade pode variar entre 1.0 (totalmente opaca) e 0 (totalmente transparente).
Par�metros:
nivelOpacidade (entrada, passagem por valor): indica o n�vel de opacidade da janela, variando entre 1.0 e 0.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser alterada.
********************************/
void SetOpacidadeJanela(float nivelOpacidade,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetOpacidade(nivelOpacidade);
}

/********************************
A fun��o SetPosicaoJanela() � respons�vel por definir a posi��o de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) � o canto superior esquerdo.
Par�metros:
posicaoX (entrada, passagem por valor): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (entrada, passagem por valor): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
********************************/
void SetPosicaoJanela(int posicaoX,int posicaoY,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetPosicao(posicaoX,posicaoY);
}

/********************************
A fun��o SetPosicaoJanela() � respons�vel por recuperar a posi��o de um janela na tela correspondente. A tela normalmente utiliza um sistema de coordenadas, cujo ponto (0,0) � o canto superior esquerdo.
Par�metros:
posicaoX (sa�da, passagem por refer�ncia): indica o valor no eixo X (horizontal) da esquerda para direita.
posicaoY (saida, passagem por refer�ncia): indica o valor no eixo Y (vertical), normalmente de cima para baixo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
********************************/
void GetPosicaoJanela(int *posicaoX,int *posicaoY,int idJanela=0){
    SDL_Point p = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o SetBordaJanela() � respons�vel por definir se uma janela possuir� ou n�o bordas vis�veis. O valor de 0 (zero) indica aus�ncia de borda, enquanto valores diferentes de zero indicam presen�a de borda.
Par�metros:
valor (entrada, passagem por valor): indica se a janela possui borda (valor diferente de zero) ou n�o (valor igual a zero).
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
********************************/
void SetBordaJanela(int valor,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetBorda(valor);
}

/********************************
A fun��o SetModoJanela() � respons�vel por definir o modo de exibi��o de uma janela. A janela pode ser exibida em tr�s diferentes modos: PIG_JANELA_NORMAL, que � o modo padr�o onde a janela ocupa o espa�o da tela definido por sua altura e largura atual;
PIG_JANELA_TELACHEIA_DISPLAY, que � o modo no qual a janela fica em tela cheia com a resolu��o id�ntica � da tela; PIG_JANELA_TELACHEIA, que � o modo onde a janela fica em tela cheia, mas com a resolu��o atual mantida.
A tela cheia n�o � acionada automaticamente com a combin��o ALT+ENTER, � preciso executar o comando espec�fico.
Par�metros:
modo (entrada, passagem por valor): indica qual dos tr�s modos (PIG_JANELA_NORMAL, PIG_JANELA_TELACHEIA, PIG_JANELA_TELACHEIA_DISPLAY) deve ser usado para exibir a janela.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
********************************/
void SetModoJanela(int modo,int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetModo(modo);
}

/********************************
A fun��o GetModoJanela() � respons�vel por recuperar o modo de exibi��o de uma janela. A janela pode ser exibida em tr�s diferentes modos: PIG_JANELA_NORMAL, que � o modo padr�o onde a janela ocupa o espa�o da tela definido por sua altura e largura atual;
PIG_JANELA_TELACHEIA_DISPLAY, que � o modo no qual a janela fica em tela cheia com a resolu��o id�ntica � da tela; PIG_JANELA_TELACHEIA, que � o modo onde a janela fica em tela cheia, mas com a resolu��o atual mantida.
A tela cheia n�o � acionada automaticamente com a combina��o ALT+ENTER, � preciso executar o comando espec�fico.
Par�metros:
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela a ser reposicionada.
Retorno:
inteiro que indica qual dos tr�s modos (PIG_JANELA_NORMAL, PIG_JANELA_TELACHEIA, PIG_JANELA_TELACHEIA_DISPLAY) est� sendo usado para exibir a janela.
********************************/
int GetModoJanela(int idJanela=0){
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetModo();
}


/********************************
Se��o de controle de jogo
********************************/

/********************************
A fun��o BotaoPressionadoControle() � respons�vel por verificar se um determinado bot�o do controle est� ou n�o pressionado.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
botao (entrada, passagem por valor): indica qual botao est� sendo verificado.
retono:
inteiro que representa se o bot�o est� pressionado (valor diferente de zero) ou est� livre (valor igual a zero).
********************************/
int BotaoPressionadoControle(int idControle,int botao){
    return CPIGGerenciadorControles::GetControle(idControle)->BotaoPressionado(botao);
}

/********************************
A fun��o EixoAcionadoControle() � respons�vel por verificar o n�vel de acionamento de um eixo do controle. Essa fun��o pode ser utilizada
tanto para eixos anal�gicos, cujos valores s�o de -32768 a 32767, ou gatilhos, cujos valores s�o de 0 a 32767.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
eixo (entrada, passagem por valor): indica qual eixo est� sendo verificado.
retono:
inteiro que representa o n�vel de acionamento do eixo. Pode ser um valor negativo (eixos anal�gicos) ou valores positivos (eixos anal�gicos e gatilhos).
********************************/
int EixoAcionadoControle(int idControle,int eixo){
    return CPIGGerenciadorControles::GetControle(idControle)->EixoAcionado(eixo);
}

/********************************
A fun��o EixoAcionadoPercentualControle() � respons�vel por verificar o n�vel percentual de acionamento de um eixo do controle. Essa fun��o pode ser utilizada
tanto para eixos anal�gicos, cujos valores s�o de -1.0 a 1.0, ou gatilhos, cujos valores s�o de 0 a 1.0.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
eixo (entrada, passagem por valor): indica qual eixo est� sendo verificado.
retono:
n�mero real que representa o n�vel percentual de acionamento do eixo. Pode ser um valor negativo (eixos anal�gicos) ou valores positivos (eixos anal�gicos e gatilhos).
********************************/
float EixoAcionadoPercentualControle(int idControle,int eixo){
    return CPIGGerenciadorControles::GetControle(idControle)->EixoAcionadoPercentual(eixo);
}

/********************************
A fun��o GetQtdEixosControle() � respons�vel por calcular quantos eixos e gatilhos est�o dispon�veis no controle.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
retono:
inteiro que representa a quantidade de eixos e gatilhos.
********************************/
int GetQtdEixosControle(int idControle){
    return CPIGGerenciadorControles::GetControle(idControle)->GetQtdEixos();
}

/********************************
A fun��o GetQtdBotoesControle() � respons�vel por calcular quantos bot�es digitais (incluindo os direcionais) est�o dispon�veis no controle.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
retono:
inteiro que representa a quantidade de bot�es digitais (incluindo os direcionais).
********************************/
int GetQtdBotoesControle(int idControle){
    return CPIGGerenciadorControles::GetControle(idControle)->GetQtdBotoes();
}

/********************************
A fun��o GetNomeControle() � respons�vel recuperar o nome com o qual o controle foi registrado no sistema.
Par�metros:
idControle (entrada, passagem por valor): indica qual controle est� sendo verificado.
nomeControle (sa�da, passagem por refer�ncia): armazena a string contendo o nome que foi recuperada para o controle.
********************************/
void GetNomeControle(int idControle,char *nomeControle){
    strcpy(nomeControle,CPIGGerenciadorControles::GetControle(idControle)->GetNome().c_str());
}


/********************************
Se��o de elementos geom�tricos
********************************/

/********************************
A fun��o DesenhaLinhasSimples() � respons�vel por desenhar uma �nica linha, cujo in�cio � o ponto (x1,y1) e o fim � o ponto (x2,y2).
Par�metros:
pontoX1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho da linha.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde a linha ser� desenhada.
********************************/
void DesenhaLinhaSimples(int pontoX1,int pontoY1,int pontoX2,int pontoY2, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(pontoX1,pontoY1,pontoX2,pontoY2,cor);
}

/********************************
A fun��o DesenhaLinhasDisjuntas() � respons�vel por desenhar linhas separadamente, ou seja, os ponto iniciais de cada linha est�o nas posi��es pares e
os pontos finais est�o nas posi��es �mpares. Assim, os vetores precisam ter tamanho qtdPontos*2.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores Y (inicias e finais) de cada linha.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde as linhas ser�o desenhadas.
********************************/
void DesenhaLinhasDisjuntas(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhasDisjuntas(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A fun��o DesenhaLinhasSequencia() � respons�vel por desenhar linhas em sequ�ncia, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores X de cada linha da sequ�ncia.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores Y de cada linha da sequ�ncia.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde as linhas ser�o desenhadas.
********************************/
void DesenhaLinhasSequencia(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhasSequencia(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A fun��o DesenhaRetangulo() � respons�vel por desenhar um ret�ngulo com preenchimento s�lido na tela em uma posi��o desejada pelo usu�rio.
O mesmo pode ser colocado em qualquer lugar do campo de vis�o da tela.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do ret�ngulo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde o ret�ngulo ser� desenhado.
********************************/
void DesenhaRetangulo(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(posicaoX,posicaoY,altura,largura,cor);
}

/********************************
A fun��o DesenhaRetanguloVazado() � respons�vel por desenhar um ret�ngulo sem preenchimento na tela em uma posi��o desejada pelo usu�rio.
O mesmo pode ser colocado em qualquer lugar do campo de vis�o da tela.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do ret�ngulo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde o ret�ngulo ser� desenhado.
********************************/
void DesenhaRetanguloVazado(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(posicaoX,posicaoY,altura,largura,cor);
}

/********************************
A fun��o DesenhaPoligono() � respons�vel por desenhar na janela um pol�gono de preenchimento s�lido com o n�mero de lados indicados. Os dois primeiros par�metros indicam as coordenadas
de cada um dos v�rtices do pol�gono.
AVISO: essa fun��o utiliza o renderizador offscreen para gerar o pol�gono e posteriormente o renderiza na janela em quest�o; isto pode fazer o FPS da aplica��o diminuir consideravelmente.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos, contendo as coordenadas X de cada v�rtice do pol�gono.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos, contendo as coordenadas Y de cada v�rtice do pol�gono.
qtdPontos (entrada, passagem por valor): quantidade de lados do pol�gono.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do pol�gono.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica o n�mero da janela onde o pol�gono ser� desenhado.
********************************/
void DesenhaPoligono(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor, int idJanela=0){
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaPoligono(pontosX,pontosY,qtdPontos,cor);
}


/********************************
Se��o de desenho Offscreen
********************************/

/********************************
A fun��o PreparaOffScreenRenderer() serve para criar um novo bitmap offscreen que servir� de �rea
de desenho para outras fun��es que utilizem este bitmap.
Par�metros:
altura (entrada, passagem por valor): indica a altura em pixels do novo bitmap.
largura (entrada, passagem por valor): indica a largura em pixels do novo bitmap.
********************************/
void PreparaOffScreenRenderer(int altura,int largura){
    jogo->PreparaOffScreenRenderer(altura,largura);
}

/********************************
A fun��o SalvaOffScreenBMP() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuar� existindo em mem�ria e a��es subsequentes ainda poder�o ser feitas. Para "limpar" a imagem
deve-se utilizar a fun��o PintaFundoOffScreen().
Par�metros:
nomeArquivoBMP (entrada, passagem por refer�ncia*): indica com que nome a imagem offscreen ser� salva. O valor do par�metro deve conter a extens�o ".bmp".
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void SalvaOffScreenBMP(char *nomeArquivoBMP){
    jogo->GetOffScreenRender()->SalvarImagemBMP(nomeArquivoBMP);
}

/********************************
A fun��o SalvaOffScreenPNG() serve para efetivamente salvar a imagem offscreen como um arquivo do sistema operacional.
A imagem offscreen continuar� existindo em mem�ria e a��es subsequentes ainda poder�o ser feitas. Para "limpar" a imagem
deve-se utilizar a fun��o PintaFundoOffScreen().
Par�metros:
nomeArquivoPNG (entrada, passagem por refer�ncia*): indica com que nome a imagem offscreen ser� salva. O valor do par�metro deve conter a extens�o ".png".
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void SalvaOffScreenPNG(char *nomeArquivoPNG){
    jogo->GetOffScreenRender()->SalvarImagemPNG(nomeArquivoPNG);
}

/********************************
A fun��o PintaAreaOffScreen() serve para mudar a cor de uma �rea cont�gua de pixels da mesma cor.
A funcionalidade � semelhante � ferramenta "balde" dos editores de imagem. A �rea ser� pintada a partir do
ponto (posicaoX,posicaoY) de acordo com o sistema de coordenadas da PIG. A fun��o de pintura padr�o pode ser
substitu�da por outra fun��o customizada qualquer com o comando DefineFuncaoPintarAreaOffscreen().
Par�metros:
posicaoX (entrada, passagem por valor): indica o ponto no eixo X para come�ar a pintar a �rea cont�gua de pixels.
posicaoY (entrada, passagem por valor): indica o ponto no eixo Y para come�ar a pintar a �rea cont�gua de pixels.
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura da �rea cont�gua de pixels.
ponteiro (entrada, passagem por refer�ncia): ponteiro para qualquer tipo de estrutura a ser usada na fun��o customizada de pintura da �rea.
********************************/
void PintaAreaOffScreen(int posicaoX,int posicaoY,PIG_Cor cor,void *ponteiro=NULL){
    jogo->GetOffScreenRender()->PintarArea(posicaoX,posicaoY,cor,ponteiro);
}

/********************************
A fun��o DefineFuncaoPintarAreaOffScreen() permite substituir a fun��o padr�o de pintura por outra fun��o customizada que deve ser passada como par�metro.
A fun��o de pintura deve ser definida de forma que receba 4 par�metros inteiros (respectivamente, a posi��o x e y do pixel que deve ser pintado e as
dimens�es - altura e largura - da imagem offscreen) e 2 cores (a cor atual do pixel e a cor que deveria ser usada para pint�-lo). A fun��o deve tamb�m retornar
o valor de uma cor, que ser� a cor efetivamente utilizada para pintar o pixel em quest�o. A fun��o, portanto, deve definir para cada ponto solicitado qual a cor
final daquele ponto.
Par�metros:
funcao (entrada, passagem por refer�ncia): nome da fun��o customizada para pintar uma �rea no renderizador offscreen.
********************************/
void DefineFuncaoPintarAreaOffscreen(PIG_Cor (*funcao)(int,int,int,int,PIG_Cor,PIG_Cor)){
    jogo->GetOffScreenRender()->DefineFuncaoPintarArea(funcao);
}

/********************************
A fun��o MoveCanetaOffScreen() reposiciona a caneta do renderizador offscreen em algum outro ponto da imagem.
Par�metros:
novoX (entrada, passagem por valor): nova posi��o no eixo X na qual a caneta ser� reposicionada. O tipo de par�metro � double mas ser� convertido para int, dentro da fun��o.
novoY (entrada, passagem por valor): nova posi��o no eixo Y na qual a caneta ser� reposicionada. O tipo de par�metro � dpuble mas ser� convertido para int, dentro da fun��o.
********************************/
void MoveCanetaOffscreen(double novoX,double novoY){
    jogo->GetOffScreenRender()->MoveCanetaPara(novoX,novoY);
}

/********************************
A fun��o AvancaCanetaOffScreen() cria uma linha no renderizador offscreen na dire��o e sentido nos quais a canete est� orientada.
Par�metros:
distancia (entrada, passagem por valor): dist�ncia a ser percorrida pela caneta. O tipo de par�metro � double para permitir que o c�lculo da dist�ncia seja feito livremente.
********************************/
void AvancaCanetaOffscreen(double distancia){
    jogo->GetOffScreenRender()->AvancaCaneta(distancia);
}

/********************************
A fun��o MudaCorCanetaOffScreen() modifica a cor a ser utilizada pela caneta do renderizador offscreen daqui por diante. Desenhos feitos anteriormente permancem com a cor com a qual foram feitos.
Par�metros:
novaCor (entrada, passagem por valor): valor da nova cor a ser utilizada pela caneta do renderizador offscreen.
********************************/
void MudaCorCanetaOffscreen(PIG_Cor novaCor){
    jogo->GetOffScreenRender()->MudaCorAtualCaneta(novaCor);
}

/********************************
A fun��o GiraCanetaHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova dire��o e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de dire��o e sentido ser�o utilizados para que o ponto final do tra�o seja calculado.
Par�metros:
angulo (entrada, passagem por valor): valor do �ngulo (sentido hor�rio, em radianos) pelo qual a caneta ser� redirecionada.
********************************/
void GiraCanetaHorarioOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraCanetaHorario(angulo);
}

/********************************
A fun��o GiraCanetaAntiHorarioOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova dire��o e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de dire��o e sentido ser�o utilizados para que o ponto final do tra�o seja calculado.
Par�metros:
angulo (entrada, passagem por valor): valor do �ngulo (sentido anti-hor�rio, em radianos) pelo qual a caneta ser� redirecionada.
********************************/
void GiraCanetaAntiHorarioOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraCanetaAntiHorario(angulo);
}

/********************************
A fun��o GiraCanetaAnguloFixoOffScreen() gira a caneta do renderizador offscreen. A caneta passa a ter uma nova dire��o e sentido. Se o comando AvancaCanetaOffscreen() for executado posteriormente,
esses novos valores de dire��o e sentido ser�o utilizados para que o ponto final do tra�o seja calculado.
Par�metros:
angulo (entrada, passagem por valor): valor do �ngulo usando como refer�ncia o �ngulo 0 do c�rculo trigonom�trico.
********************************/
void GiraCanetaAnguloFixoOffscreen(double angulo){
    jogo->GetOffScreenRender()->GiraAnguloFixo(angulo);
}

/********************************
A fun��o GetAnguloAtualOffScreen() recupera o �ngulo atual que est� sendo usado pela caneta do renderizador offscreen.
Retorno:
n�mero real que representa o valor do �ngulo atual, tendo como refer�ncia o �ngulo 0 do c�rculo trigonom�trico.
********************************/
double GetAnguloAtualOffscreen(){
    return jogo->GetOffScreenRender()->GetAngAtual();
}

/********************************
A fun��o GetXCanetaOffScreen() recupera a posi��o no eixo X na qual est� posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posi��o atual da caneta no eixo X.
********************************/
int GetXCanetaOffscreen(){
    return jogo->GetOffScreenRender()->GetXCaneta();
}

/********************************
A fun��o GetYCanetaOffScreen() recupera a posi��o no eixo Y na qual est� posicionada atualmente a caneta do renderizador offscreen.
Retorno:
inteiro que representa a posi��o atual da caneta no eixo Y.
********************************/
int GetYCanetaOffscreen(){
    return jogo->GetOffScreenRender()->GetYCaneta();
}

/********************************
A fun��o PintaFundoOffScreen() serve para "limpar" o bitmap offscreen, mudando completamente para cor indicada.
Par�metros:
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura completa do bitmap offscreen.
********************************/
void PintaFundoOffScreen(PIG_Cor cor){
    jogo->GetOffScreenRender()->PintarFundo(cor);
}

/********************************
A fun��o DesenhaRetanguloOffScreen() � respons�vel por desenhar um ret�ngulo cem preenchimento s�lido no bitmap offscreen em uma posi��o desejada pelo usu�rio.
O sistema de coordenadas � o mesmo da tela, com o eixo Y aumentando para cima.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o preenchimento do ret�ngulo.
********************************/
void DesenhaRetanguloOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenharRetangulo(x1,y1,altura,largura,cor);
}

/********************************
A fun��o DesenhaRetanguloVazadoOffScreen() � respons�vel por desenhar um ret�ngulo sem preenchimento no bitmap offscreen em uma posi��o desejada pelo usu�rio.
O sistema de coordenadas � o mesmo da tela, com o eixo Y aumentando para cima.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do ret�ngulo.
********************************/
void DesenhaRetanguloVazadoOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenharRetanguloVazado(x1,y1,altura,largura,cor);
}

/********************************
A fun��o DesenhaLinhasSimplesOffScreen() � respons�vel por desenhar no bitmap offscreen uma �nica linha, cuja in�cio � o ponto (x1,y1) e o fim � o ponto (x2,y2).
Par�metros:
pontoX1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhaSimplesOffScreen(int x1,int y1,int x2,int y2,PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenharLinha(x1,y1,x2,y2,cor);
}

/********************************
A fun��o DesenhaLinhasDisjuntasOffScreen() � respons�vel por desenhar no bitmap offscreen linhas separadamente, ou seja, os ponto iniciais de cada linha est�o nas posi��es pares e
os pontos finais est�o nas posi��es �mpares. Assim, os vetores precisam ter tamanho qtdPontos*2.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos*2, contendo os valores Y (inicias e finais) de cada linha.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhasDisjuntasOffScreen(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenhaLinhasDisjuntas(pontosX,pontosY,qtdPontos,cor);
}

/********************************
A fun��o DesenhaLinhasSequenciaOffScreen() � respons�vel por desenhar no bitmap offscreen linhas em sequ�ncia, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores X de cada linha da sequ�ncia.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos+1, contendo os valores Y de cada linha da sequ�ncia.
qtdPontos (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas.
********************************/
void DesenhaLinhasSequenciaOffScreen(int pontosX[],int pontosY[],int qtdPontos, PIG_Cor cor){
    jogo->GetOffScreenRender()->DesenhaLinhasSequencia(pontosX,pontosY,qtdPontos,cor);
}


///escrever

/********************************
Se��o de fontes
********************************/

/********************************
A fun��o CriaFonteNormal() � respons�vel por disponibilizar uma nova fonte com preenchimento s�lido.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte ter�. Caso n�o seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para it�lico;
PIG_ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a fonte. Uma fonte s� pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,contorno,corContorno,idJanela);
}

/********************************
A fun��o CriaFonteNormal() � respons�vel por disponibilizar uma nova fonte com preenchimento s�lido.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte. Caso a cor n�o seja informada, ser� utilizada a cor padr�o (BRANCO).
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para it�lico;
PIG_ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a fonte. Uma fonte s� pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra=PIG_FONTE_PADRAO_COR,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteNormal(nome,tamanho,estilo,corLetra,idJanela);
}

/********************************
A fun��o CriaFonteDinamica() � respons�vel por disponibilizar uma nova fonte din�mica com preenchimento s�lido. As fontes din�micas s�o capazes
de escrever strings com diferentes formata��es (negrito, it�lico, sublinhado, cortado) e cores nas letras. A string a ser utilizada pela fonte
pode conter ou n�o os marcadores de formta��o. Caso n�o contenham, ser� utilizada uma letra branca, sem formata��o.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a fonte. Uma fonte s� pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteDinamica(char *nome,int tamanho,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteDinamica(nome,tamanho,idJanela);
}

/********************************
A fun��o CriaFonteFundo() � respons�vel por disponibilizar uma nova fonte com preenchimento de um bitmap espec�fico.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por refer�ncia): indica o nome do arquivo de imagem que servir� de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte ter�. Caso n�o seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para it�lico;
PIG_ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a fonte. Uma fonte s� pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,idJanela);
}

/********************************
A fun��o CriaFonteFundo() � respons�vel por disponibilizar uma nova fonte com preenchimento de um bitmap espec�fico.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por refer�ncia): indica o nome do arquivo de imagem que servir� de fundo para a fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para it�lico;
PIG_ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a fonte. Uma fonte s� pode ser usada na janela na qual foi criada.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int idJanela=0){
    return CPIGGerenciadorFontes::CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,idJanela);
}


/********************************
A fun��o CriaFonteNormalOffscreen() � respons�vel por disponibilizar uma nova fonte com preenchimento s�lido.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte ter�. Caso n�o seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para it�lico;
PIG_ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteNormalOffscreen(char *nome,int tamanho,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteNormalOffScreen(nome,tamanho,estilo,corLetra,contorno,corContorno,jogo->GetOffScreenRender(),0);
}

/********************************
A fun��o CriaFonteNormalOffscreen() � respons�vel por disponibilizar uma nova fonte com preenchimento s�lido.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte. Caso a cor n�o seja informada, ser� utilizada a cor padr�o (BRANCO).
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para it�lico;
PIG_ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteNormalOffscreen(char *nome,int tamanho,PIG_Cor corLetra=PIG_FONTE_PADRAO_COR,PIG_Estilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteNormalOffScreen(nome,tamanho,estilo,jogo->GetOffScreenRender(),corLetra,0);
}


/********************************
A fun��o CriaFonteFundoOffscreen() � respons�vel por disponibilizar uma nova fonte com preenchimento de um bitmap espec�fico.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por refer�ncia): indica o nome do arquivo de imagem que servir� de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte ter�. Caso n�o seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para it�lico;
PIG_ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteFundoOffscreen(char *nome,int tamanho,char *arquivoFundo,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteFundoOffScreen(nome,tamanho,estilo,arquivoFundo,contorno,corContorno,jogo->GetOffScreenRender(),0);
}

/********************************
A fun��o CriaFonteFundoOffscreen() � respons�vel por disponibilizar uma nova fonte com preenchimento de um bitmap espec�fico.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por refer�ncia): indica o nome do arquivo de imagem que servir� de fundo para a fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: PIG_ESTILO_NEGRITO, para negrito; PIG_ESTILO_SUBLINHADO, para sublinhado; PIG_ESTILO_ITALICO, para it�lico;
PIG_ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado PIG_ESTILO_NORMAL.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteFundoOffscreen(char *nome,int tamanho,char *arquivoFundo,PIG_Estilo estilo=PIG_ESTILO_NORMAL){
    return CPIGGerenciadorFontes::CriaFonteFundoOffScreen(nome,tamanho,estilo,arquivoFundo,jogo->GetOffScreenRender(),0);
}

/********************************
A fun��o CalculaLarguraPixels() � respons�vel por realizar a soma das larguras de cada letra da string informada.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necess�rios para escrever a string.
********************************/
int CalculaLarguraPixels(char *str,int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLarguraPixelsString(str);
}

/********************************
A fun��o EscreverDireita() � respons�vel por exibir uma string na tela de jogo, com alinhamento � direita do valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o da string.
********************************/
void EscreverDireita(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A fun��o EscreverEsquerda() � respons�vel por exibir uma string na tela de jogo, com alinhamento � esquerda do valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o da string.
********************************/
void EscreverEsquerda(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A fun��o EscreverCentralizada() � respons�vel por exibir uma string na tela de jogo, com alinhamento em rela��o ao valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o da string.
********************************/
void EscreverCentralizada(char *str,int posicaoX,int posicaoY,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str,posicaoX,posicaoY,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A fun��o EscreverLongaEsquerda() � respons�vel por exibir uma string longa na tela de jogo, com alinhamento � esquerda do valor de X.
A string se expande palavra por palavra at� a largura m�xima definida (maxLarg). Se ainda houver palavras, elas ser�o escritas na linha abaixo,
tendo um espa�amento entre as linhas (espacoEntreLinhas) tamb�m definido por par�metro.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
largMax (entrada, passagem por valor): largura m�xima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes s�o escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): dist�ncia em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o das strings.
********************************/
void EscreverLongaEsquerda(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A fun��o EscreverLongaDireita() � respons�vel por exibir uma string longa na tela de jogo, com alinhamento � direita do valor de X.
A string se expande palavra por palavra at� a largura m�xima definida (maxLarg). Se ainda houver palavras, elas ser�o escritas na linha abaixo,
tendo um espa�amento entre as linhas (espacoEntreLinhas) tamb�m definido por par�metro.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
largMax (entrada, passagem por valor): largura m�xima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes s�o escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): dist�ncia em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o das strings.
********************************/
void EscreverLongaDireita(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A fun��o EscreverLongaCentralizada() � respons�vel por exibir uma string longa na tela de jogo, com alinhamento em rela��o ao valor de X.
A string se expande palavra por palavra at� a largura m�xima definida (maxLarg). Se ainda houver palavras, elas ser�o escritas na linha abaixo,
tendo um espa�amento entre as linhas (espacoEntreLinhas) tamb�m definido por par�metro.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
largMax (entrada, passagem por valor): largura m�xima em pixels que pode ser utilizada para escrever as palavras em cada linha do texto. ao atingir esse limite, as palavras seguintes s�o escritas na linha abaixo.
espacoEntreLinhas (entrada, passagem por valor): dist�ncia em pixels entre o valor Y de uma linha e o valor Y da linha abaixo.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o das strings.
********************************/
void EscreverLongaCentralizada(char *str,int posicaoX,int posicaoY,int largMax,int espacoEntreLinhas,PIG_Cor cor=BRANCO,int numFonte=0,float angulo=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(str,posicaoX,posicaoY,largMax,espacoEntreLinhas,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A fun��o EscreverInteiroEsquerda() � respons�vel por exibir um n�mero inteiro na tela de jogo, com alinhamento � esquerda em rela��o ao valor de X.
Par�metros:
valor (entrada, passagem por refer�ncia): n�mero inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever o n�mero.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever o n�mero.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o do n�mero inteiro.
********************************/
void EscreveInteiroEsquerda(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A fun��o EscreverInteiroDireita() � respons�vel por exibir um n�mero inteiro na tela de jogo, com alinhamento � direita em rela��o ao valor de X.
Par�metros:
valor (entrada, passagem por refer�ncia): n�mero inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever o n�mero.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever o n�mero.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o do n�mero inteiro.
********************************/
void EscreveInteiroDireita(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A fun��o EscreverInteiroCentralizado() � respons�vel por exibir um n�mero inteiro na tela de jogo, com alinhamento em rela��o ao valor de X.
Par�metros:
valor (entrada, passagem por refer�ncia): n�mero inteiro a ser escrito na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever o n�mero.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever o n�mero.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o do n�mero inteiro.
********************************/
void EscreveInteiroCentralizado(int valor, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A fun��o EscreverDoubleEsquerda() � respons�vel por exibir um n�mero real na tela de jogo, com alinhamento � esquerda em rela��o ao valor de X.
Par�metros:
valor (entrada, passagem por refer�ncia): n�mero inteiro a ser escrito na tela.
casas (entrada, passagem por refer�ncia): n�mero de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever o n�mero.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever o n�mero.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o do n�mero real.
********************************/
void EscreveDoubleEsquerda(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_ESQUERDA,angulo);
}

/********************************
A fun��o EscreverDoubleDireita() � respons�vel por exibir um n�mero real na tela de jogo, com alinhamento � direita em rela��o ao valor de X.
Par�metros:
valor (entrada, passagem por refer�ncia): n�mero inteiro a ser escrito na tela.
casas (entrada, passagem por refer�ncia): n�mero de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever o n�mero.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever o n�mero.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o do n�mero real.
********************************/
void EscreveDoubleDireita(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_DIREITA,angulo);
}

/********************************
A fun��o EscreverDoubleCentralizado() � respons�vel por exibir um n�mero real na tela de jogo, com alinhamento em rela��o ao valor de X.
Par�metros:
valor (entrada, passagem por refer�ncia): n�mero inteiro a ser escrito na tela.
casas (entrada, passagem por refer�ncia): n�mero de casas decimais a ser usado na escrita.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever o n�mero.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever o n�mero.
cor (entrada, passagem por valor): cor a ser aplicada � fonte no momento da escrita. Essa cor � misturada � cor original da fonte, se essa tiver sido informada na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
angulo (entrada, passagem por valor): �ngulo, em graus, para a rota��o do n�mero real.
********************************/
void EscreveDoubleCentralizado(double valor, int casas, int x, int y,PIG_Cor cor=BRANCO, int numFonte=0,float angulo=0){
    std::stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str<<std::setprecision(casas)<<valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(str.str(),x,y,cor,PIG_TEXTO_CENTRO,angulo);
}

/********************************
A fun��o GetMetricas() recupera as principais m�tricas de uma letra em um estilo espec�fico.
As m�tricas incluem as posi��es m�nimas e m�ximas nos eixos X e Y, onde a letra � desenhada.
Se a fonte n�o for din�mica, qualquer valor de estilo passado ser� descartado e ser� utilizado o estilo indicado na cria��o da fonte.
Par�metros:
letra (entrada, passagem por valor): caractere cuja largura ser� calculada.
estilo (entrada, passagem por valor): estilo desejado no c�lculo da largura. O valor s� ser� utilizado em fontes din�micas. Em fontes n�o-din�micas, o valor de estilo ser� o mesmo do informado na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
struct que representa as m�tricas principais ao escrever a letra.
********************************/
PIG_Metricas_Fonte GetMetricas(char letra, PIG_Estilo estilo=PIG_ESTILO_NORMAL,int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetMetricasLetra(letra,estilo);
}

/********************************
A fun��o CalculaLarguraLetra() � respons�vel por calcular a largura espec�fica de uma letra com um estilo.
Se a fonte n�o for din�mica, qualquer valor de estilo passado ser� descartado e ser� utilizado o estilo indicado na cria��o da fonte.
Par�metros:
letra (entrada, passagem por valor): caractere cuja largura ser� calculada.
estilo (entrada, passagem por valor): estilo desejado no c�lculo da largura. O valor s� ser� utilizado em fontes din�micas. Em fontes n�o-din�micas, o valor de estilo ser� o mesmo do informado na cria��o da fonte.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necess�rios para escrever a letra.
********************************/
int GetLarguraLetra(char letra,PIG_Estilo estilo=PIG_ESTILO_NORMAL,int numFonte = 0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLarguraLetra(letra,estilo);
}

/********************************
A fun��o GetTamanhoBaseFonte() � respons�vel por recuperar o tamanho da fonte informado na cria��o da mesma.
Par�metros:
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o tamanho base da fonte, ou seja, a quantidade de pixels no eixo Y para desenhar qualquer caractere da fonte (exceto vogais mai�suclas acentuadas: �, �, �, �, �.
********************************/
int GetTamanhoBaseFonte(int numFonte = 0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetTamanhoBaseFonte();
}

/********************************
A fun��o GetFonteDescent() calcula a quantidade de pixels que podem ser utilizados por partes de letras que fiquem abaixo da linha horizontal de base da fonte.
Essa parte inferior � usada para desenhar a cedilha, a parte inferior da letra 'g', 'q', 'y', por exemplo.
Par�metros:
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels abaixo da linha horizontal de base da fonte.
********************************/
int GetFonteDescent(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetFonteDescent();
}

/********************************
A fun��o GetFonteAscent() calcula a quantidade de pixels necess�rios acima da linha horizontal de base da fonte. Essa medida exclui os pixels utilizados
nas partes inferiores das letras 'g', 'q', 'y', por exemplo. Tamb�m n�o s�o considerados acentos em vogais mai�sculas como '�', '�', '�', por exemplo.
Par�metros:
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels acima da linha horizontal de base da fonte.
********************************/
int GetFonteAscent(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetFonteAscent();
}

/********************************
A fun��o GetFonteLineSkip() calcula a quantidade de pixels necess�rios para um espa�amento vertical ideal, ou seja, para que duas frases possam
ser escritas sem se sobreporem verticalmente.
Par�metros:
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o espa�amento vertical ideal para que duas frases n�o se sobreponham verticalmente.
********************************/
int GetFonteLineSkip(int numFonte=0){
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLineSkip();
}

/********************************
A fun��o SubstituiCaractere() substitui a imagem original de um caractere por um frame de um imagem personalizada de um arquivo de imagem. O frame � definido
pelos par�metros x, y, altura e largura, de acordo com o sistema de coordenadas dos arquivos de imagem digital (eixo Y crescendo para baixo). O frame especificado
ser� desenhado na tela toda vez que o caractere original for passado dentro de uma string. O frame ter� a mesma altura padr�o da fote original, mas pdoer� ter uma largura
personalizada por meio do par�metro largNova.
Par�metros:
caractere (entrada, passagem por valor): caractere (ou n�mero inteiro) que ser� substitu�do e n�o ser� mais desenhado posteriormente.
nomeArquivo (entrada, passagem por refer�ncia): nome do arquivo contendo o frame desejado.
largNova: (entrada, passagem por valor): largura nova a ser utilizada para desenhar o frame na tela. N�o � obrigatoriamente o mesmo valor do par�metro "larg".
x (entrada, passagem por valor): coordenada X do arquivo de imagem, onde come�a o frame desejado.
y (entrada, passagem por valor): coordenada Y do arquivo de imagem, onde come�a o frame desejado (sistema de coordenada com eixo Y crescendo para baixo).
altura (entrada, passagem por valor): altura do frame desejado.
largura (entrada, passagem por valor): largura do frame desejado.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o espa�amento vertical ideal para que duas frases n�o se sobreponham verticalmente.
********************************/
void SubstituiCaractere(char caractere, char *nomeArquivo, int largNova, int x, int y, int altura,int largura,int numFonte=0){
    CPIGGerenciadorFontes::GetFonte(numFonte)->SubstituiGlyph(nomeArquivo,caractere,largNova,x,y,altura,largura);
}



/********************************
Se��o de sprites
********************************/

/********************************
A fun��o CriaSprite() � respons�vel por criar um sprite. Qualquer sprite que for necess�rio,
pode ser criado atrav�s dessa fun��o. O sprite ainda n�o ser� desenhado, apenas criado dentro do jogo.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo da imagem do sprite a ser criado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o sprite.
Retorno:
inteiro que representa o identificador �nico do sprite. Todas as opera��es subsequentes com este sprite dever�o receber este identificador como par�metro.
********************************/
int CriaSprite(char* nomeArquivo,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaSprite(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o CriaSprite() � respons�vel por criar um sprite. Qualquer sprite que for necess�rio,
pode ser criado atrav�s dessa fun��o. O sprite ainda n�o ser� desenhado, apenas criado dentro do jogo.
Par�metros:
idSprite(entrada, passagem por valor): identificador do sprite original que ser� copiado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o sprite.
Retorno:
inteiro que representa o identificador �nico do sprite. Todas as opera��es subsequentes com este sprite dever�o receber este identificador como par�metro.
********************************/
int CriaSprite(int idSprite,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaSprite(idSprite,retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o CriaSpriteOffScreen() � respons�vel por criar um sprite a partir da imagem que est� sendo montanda pelo
renderizador Offscreen. O renderizador precisa ter sido preparado anteriormente.
Par�metros:
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
Retorno:
inteiro que representa o identificador �nico do sprite. Todas as opera��es subsequentes com este sprite dever�o receber este identificador como par�metro.
********************************/
int CriaSpriteOffScreen(int retiraFundo=1,PIG_Cor *corFundo=NULL){
    return CPIGGerenciadorSprites::CriaSpriteOffScreen(jogo->GetOffScreenRender(),retiraFundo,corFundo);
}

/********************************
A fun��o DestroiSprite() � respons�vel por eliminar o sprite em quest�o do jogo.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser exclu�do.
********************************/
void DestroiSprite(int idSprite){
    CPIGGerenciadorSprites::DestroiSprite(idSprite);
}

/********************************
A fun��o CarregaArquivoFramesSprite() � respons�vel por ler de arquivo texto os frames de um sprite.
Cada linha do arquivo texto deve conter 5 n�meros inteiros: o n�mero do frame, a posi��o do frame no eixo X do arquivo de imagem,
a posi��o do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
nomeArq (entrada, passagem por refer�ncia): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesSprite(int idSprite, char *nomeArq){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CarregaArquivoFrames(nomeArq);
}

/********************************
A fun��o CarregaFramesPorLinhaSprite() � respons�vel por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivis�o representar� um frame que ser� automaticamente criado para a anima��o, com numera��o incremental a partir do par�metro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a defini��o dos frames continua na linha inferior.
A fun��o pode ser utilizada em spritesheets regulares.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
frameInicial (entrada, passagem por valor): numera��o do primeiro frame a ser criado pela fun��o. Os demais frames ter�o numera��o consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem ser� dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem ser� dividido.
********************************/
void CarregaFramesPorLinhaSprite(int idSprite, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A fun��o CarregaFramesPorColunaSprite() � respons�vel por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivis�o representar� um frame que ser� automaticamente criado para a anima��o, com numera��o incremental a partir do par�metro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a defini��o dos frames continua na coluna seguinte.
A fun��o pode ser utilizada em spritesheets regulares.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
frameInicial (entrada, passagem por valor): numera��o do primeiro frame a ser criado pela fun��o. Os demais frames ter�o numera��o consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem ser� dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem ser� dividido.
********************************/
void CarregaFramesPorColunaSprite(int idSprite, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetSprite(idSprite)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A fun��o GetXYSprite() � respons�vel recuperar o valor da posi��o (X,Y) do sprite de acordo com o sistema de coordenadas do jogo.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (sa�da, passagem por referencia): indica a posicao no eixo X do sprite.
posicaoY (sa�da, passagem por referencia): indica a posicao no eixo Y do sprite.
********************************/
void GetXYSprite(int idSprite,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetSprite(idSprite)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o MoveSprite() � respons�vel por movimentar um determinado sprite para uma nova posi��o informada.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja reposicionar o sprite.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja reposicionar o sprite.
********************************/
void MoveSprite(int idSprite,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Move(posicaoX,posicaoY);
}

/********************************
A fun��o DeslocaSprite() � respons�vel por deslocar um determinado sprite em rela��o � sua posi��o atual.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser movido.
deltaX (entrada, passagem por valor): valor a ser somado ou subtra�do na componente X da posi��o do sprite.
deltaY (entrada, passagem por valor): valor a ser somado ou subtra�do na componente Y da posi��o do sprite.
********************************/
void DeslocaSprite(int idSprite,int deltaX,int deltaY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Desloca(deltaX,deltaY);
}

/********************************
A fun��o SetAnguloSprite() � respons�vel pela angula��o de determinado sprite. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O sprite ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaSprite(). A detec��o de colis�o n�o funciona com sprites fora da angula��o padr�o (0 graus).
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
angulo (entrada, passagem por valor): valor para indicar a angula��o do sprite em graus.
********************************/
void SetAnguloSprite(int idSprite, float angulo){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetAngulo(angulo);
}

/********************************
A fun��o GetAnguloSprite() � respons�vel por recuperar o �ngulo de rota��o de determinado sprite. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O sprite ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaSprite(). A detec��o de colis�o n�o funciona com sprites fora da angula��o padr�o (0 graus).
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
Retorna o valor do �ngulo em graus.
********************************/
float GetAnguloSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetAngulo();
}

/********************************
A fun��o SetPivoAbsolutoSprite() define um ponto (X,Y) em rela��o ao ponto (0,0) do sprite, sobre o qual o sprite ser�
rotacionado quando a fun��o SetAnguloSprite() for executada.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do sprite.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do sprite.
********************************/
void SetPivoAbsolutoSprite(int idSprite,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetPivoAbsoluto({posicaoX,posicaoY});
}

/********************************
A fun��o SetPivoProporcionalSprite() define um ponto (X,Y) proporcional ao tamanho do sprite, sobre o qual o sprite ser�
rotacionado quando a fun��o SetAnguloSprite() for executada.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
relX (entrada, passagem por valor): porcentagem da largura do sprite onde ficar� o piv�.
relY (entrada, passagem por valor): porcentagem da altura do sprite onde ficar� o piv�.
********************************/
void SetPivoProporcionalSprite(int idSprite,float relX,float relY){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetPivoProporcional({relX,relY});
}

/********************************
A fun��o GetPivoSprite() define um ponto (X,Y) em rela��o ao ponto (0,0) do sprite, sobre o qual o sprite ser�
rotacionado quando a fun��o SetAnguloSprite() for executada.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
posicaoX (sa�da, passagem por refer�ncia): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do sprite.
posicaoY (sa�da, passagem por refer�ncia): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do sprite.
********************************/
void GetPivoSprite(int idSprite,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetSprite(idSprite)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o SetFlipSprite() � respons�vel por virar o sprite, invertendo-o em alguma dire��o. O sprite somente ser�
desenhado na nova orienta��o no pr�ximo comando DesenhaSprite().
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de invers�o),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipSprite(int idSprite,PIG_Flip valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetFlip(valor);
}

/********************************
A fun��o GetFlipSprite() � respons�vel por recuperar o valor da manipula��o causada pela fun��o SetFlipSprite().
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de invers�o),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetFlip();
}

/********************************
A fun��o SetDimensoesSprite() � respons�vel por delimitar a altura e a largura do sprite que ser� desenhado na tela,
independentemente do tamanho original do arquivo de imagem.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesSprite(int idSprite, int altura, int largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetDimensoes(altura,largura);
}

/********************************
A fun��o GetDimensoesSprite() � respons�vel por recuperar a altura e a largura da �rea a ser usada
para desenhar o sprite na tela. Em outras palavras, representa o tamanho atual do sprite.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
altura (sa�da, passagem por refer�ncia): altura atual em pixels do sprite.
largura (sa�da, passagem por refer�ncia): largura atual em pixels do sprite.
********************************/
void GetDimensoesSprite(int idSprite, int *altura, int *largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->GetDimensoes(*altura,*largura);
}

/********************************
A fun��o GetDimensoesOriginaisSprite() � respons�vel por recuperar a altura e a largura originais da imagem
que foi usada para criar o sprite. Qualquer utiliza��o da fun��o SetDimensoesSprite() � ignorada para
o c�lculo desta fun��o.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
altura (sa�da, passagem por refer�ncia): altura original em pixels do sprite.
largura (sa�da, passagem por refer�ncia): largura original em pixels do sprite.
********************************/
void GetDimensoesOriginaisSprite(int idSprite, int *altura, int *largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->GetDimensoesOriginais(*altura,*largura);
}

/********************************
A fun��o RestauraDimensoesOriginaisSprite() � respons�vel por restaurar o sprite com o tamanho original da image.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void RestauraDimensoesOriginaisSprite(int idSprite, int altura, int largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->RestauraDimensoesOriginais();
}

/********************************
A fun��o CriaFrameSprite() � respons�vel por delimitar o posicionamento dos pixels do arquivo de imagem que ser�o
utilizados para representar o sprite na tela. Desta forma, nem toda a imagem ser� automaticamente utilizada para
representar o sprite. O sistema de coordenadas deve ser o padr�o dos arquivos de imagem, com o eixo Y aumentando para baixo.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
idFrame (entrada, passagem por valor): identificador do frame a ser criado.
xBitmap (entrada, passagem por valor): indica a posi��o de eixo X onde come�a o frame.
yBitmap (entrada, passagem por valor): indica a posi��o de eixo Y onde come�a o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameSprite(int idSprite, int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineFrame(idFrame, {xBitmap,yBitmap,largura,altura});
}

/********************************
A fun��o MudaFrameSprite() � respons�vel por modificar o frame (j� definido pela fun��o DefineFrameSprite) de um sprite
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
idFrame (entrada, passagem por valor): identificador do frame j� criado.
Retorno:
Se o identifador do frame informado n�o corresponder a um frame j� criado, o valor de retorno � igual a 0. Caso contr�rio, � igual a 1.
********************************/
int MudaFrameSprite(int idSprite, int idFrame){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->MudaFrameAtual(idFrame);
}

/********************************
A fun��o GetFrameAtualSprite() recupera o valor do frame atual exibido no sprite.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
N�mero do frame atual do sprite.
********************************/
int GetFrameAtualSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetFrameAtual();
}

/********************************
A fun��o SetColoracaoSprite() � respons�vel por mesclar uma determinada cor com os pixels do arquivo de imagem.
Ap�s a modifica��o, todos os desenhos deste sprite ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoSprite(int idSprite, PIG_Cor cor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetColoracao(cor);
}

/********************************
A fun��o SetOpacidadeSprite() � respons�vel por modificar o n�vel de opacidade do sprite.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
valor (entrada,passagem por valor): n�vel de opacidade do sprite na faixa 0-255.
********************************/
void SetOpacidadeSprite(int idSprite,int valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetOpacidade(valor);
}

/********************************
A fun��o GetOpacidadeSprite() � respons�vel por recuperar o n�vel de opacidade de determinado sprite.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
Retorna o n�vel de opacidade do sprite na faixa 0-255.
********************************/
int GetOpacidadeSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetOpacidade();
}

/********************************
A fun��o DesenhaSprite() � respons�vel por desenhar um sprite na tela. O sprite ser� desenhado de acordo com todas as defini��es
de posi��o e �ngulo informado at� o momento. Al�m disso, se o sprite estiver virado (flipping), isso tamb�m ser� levado em considera��o.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->Desenha();
}

/********************************
A fun��o DesenhaSpriteOffScreen() � respons�vel por desenhar um sprite no Renderizador Offscreen. O sprite ser� desenhado de acordo com todas as defini��es
de posi��o e �ngulo informado at� o momento. Al�m disso, se o sprite estiver virado (flipping), isso tamb�m ser� levado em considera��o.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSpriteOffScreen(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DesenhaOffScreen(jogo->GetOffScreenRender());
}

/********************************
A fun��o DesenhaSprite() � respons�vel por desenhar um sprite na tela. O sprite ser� desenhado contendo toda a imagem, na posi��o indica.
N�o ser� aplicada nenhuma modifica��o, como �ngulo, colora��o, ou opacidade, por exemplo.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite a ser desenhado.
********************************/
void DesenhaSpriteSimples(char *nomeArq,int x, int y, int retiraFundo=1,int idJanela=0){
    CPIGGerenciadorSprites::DesenhaSprite(nomeArq, x, y, retiraFundo,idJanela);
}

/********************************
A fun��o InsereTransicaoSprite() � respons�vel por criar e inserir uma nova transi��o ao final de sequ�ncia de transi��es do sprite.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
tempo (entrada, passagem por valor): duracao (em segundos) da transi��o.
deltaX (entrada, passagem por valor): diferen�a da posi��o no eixo X em rela��o � posi��o do sprite no in�cio da transi��o.
deltaY (entrada, passagem por valor): diferen�a da posi��o no eixo Y em rela��o � posi��o do sprite no in�cio da transi��o.
deltaAltura (entrada, passagem por valor): diferen�a da altura do sprite em rela��o ao in�cio da transi��o.
deltaLargura (entrada, passagem por valor): diferen�a da largura do sprite em rela��o ao in�cio da transi��o.
deltaAngulo (entrada, passagem por valor): diferen�a de �ngulo (em graus) do sprite em rela��o ao in�cio da transi��o.
corFinal (entrada, passagem por valor): colora��o do sprite ao final da transi��o.
deltaOpacidade (entrada, passagem por valor): diferen�a do n�vel de opacidade do sprite em rela��o ao in�cio da transi��o.
********************************/
void InsereTransicaoSprite(int idSprite,double tempo,int deltaX,int deltaY,int deltaAltura,int deltaLargura,double deltaAngulo,PIG_Cor corFinal,int deltaOpacidade){
    CPIGGerenciadorSprites::GetSprite(idSprite)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A fun��o ExecutandoTransicaoSprite() retorna a informa��o sobre a execu��o (neste momento) de transi��es do sprite.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
Retorno:
inteiro que indica se o sprite est� executando alguma transi��o no momento (valor diferente de 0) ou n�o (valor igual a 0).
********************************/
int ExecutandoTransicaoSprite(int idSprite){
    return CPIGGerenciadorSprites::GetSprite(idSprite)->ExecutandoTransicao();
}

/********************************
A fun��o LeArquivoTransicaoSprite() � respons�vel por ler, criar e inserir as transi��es para um sprite, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transi��o (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transi��o.
2) um inteiro repreentando a diferen�a da posi��o no eixo X em rela��o � posi��o do sprite no in�cio da transi��o.
3) um inteiro repreentando a diferen�a da posi��o no eixo Y em rela��o � posi��o do sprite no in�cio da transi��o.
4) um inteiro repreentando a diferen�a da altura do sprite em rela��o ao in�cio da transi��o.
5) um inteiro repreentando a diferen�a da largura do sprite em rela��o ao in�cio da transi��o.
6) um double repreentando a diferen�a de �ngulo (em graus) do sprite em rela��o ao in�cio da transi��o.
7) um inteiro repreentando a componente R (vermelho) da colora��o do sprite ao final da transi��o.
8) um inteiro repreentando a componente G (verde) da colora��o do sprite ao final da transi��o.
9) um inteiro repreentando a componente B (azul) da colora��o do sprite ao final da transi��o.
10) um inteiro repreentando a componente A (canal alfa) da colora��o do sprite ao final da transi��o.
11) um inteiro repreentando a diferen�a do n�vel de opacidade do sprite em rela��o ao in�cio da transi��o.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
nomeArq (entrada, passagem por refer�ncia): nome com extens�o do arquivo texto contendo as transi��es.
********************************/
void LeArquivoTransicaoSprite(int idSprite,char *nomeArq){
    CPIGGerenciadorSprites::GetSprite(idSprite)->LeTransicoes(nomeArq);
}

/********************************
A fun��o IniciaAutomacaoSprite() � respons�vel por iniciar as transi��es j� inseridas no sprite, de acordo como o tipo de transi��o informada.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void IniciaAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->IniciaAutomacao();
}

/********************************
A fun��o TrataAutomacaoSprite() � respons�vel por calcular o estado da transi��o corrente do sprite e aplicar essas modifica��o a ela.
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void TrataAutomacaoSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->TrataAutomacao();
}

/********************************
A fun��o DefineTipoTransicaoSprite() � respons�vel por determinar como a sequ�ncia de transi��es ser� executada.
� poss�vel faz�-la uma �nica vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo at� o final da sequ�ncia e retornando, em vai-v�m (PIG_TRANSICAO_VAIVEM).
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void DefineTipoTransicaoSprite(int idSprite,PIG_TipoTransicao valor){
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineTipoTransicao(valor);
}

/********************************
A fun��o LimpaTransicoesSprite() � respons�vel por remover a sequ�ncia de transi��es do sprite.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
********************************/
void LimpaTransicoesSprite(int idSprite){
    CPIGGerenciadorSprites::GetSprite(idSprite)->LimpaTransicoes();
}

/********************************
A fun��o InsereAcaoSprite() � respons�vel por inserir na linha de tempo de automa��o do sprite uma a��o a ser executada.
A a��o � composta por uma fun��o "acao" que ser� executada quando a linha de tempo atingir o par�metro "tempo" e ser� repetida a cada "repeticao" segundos.
A a��o pode armazenar um ponteiro gen�rico "param" que ser� utilizado na chamada da fun��o.
Par�metros:
idSprite (entrada, passagem por valor): identificador do sprite.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da fun��o.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a pr�xima. O valor -1 indica que a fun��o n�o ser� repetida.
param (entrada, passagem por refer�ncia): ponteiro gen�rico para um valor que ser� utilizado na chamada da fun��o.
********************************/
void InsereAcaoSprite(int idSprite,double tempo,double repeticao,PIG_FuncaoSimples acao,void *param){
    CPIGGerenciadorSprites::GetSprite(idSprite)->InsereAcao(tempo,repeticao,acao,param);
}



/********************************
Se��o de objetos
********************************/

/********************************
A fun��o CriaObjeto() � respons�vel por criar um objeto. Qualquer objeto que for necess�rio,
pode ser criado atrav�s dessa fun��o. O objeto ainda n�o ser� desenhado, apenas criado dentro do jogo.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo da imagem do objeto a ser criado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o objeto.
Retorno:
inteiro que representa o identificador �nico do objeto. Todas as opera��es subsequentes com este objeto dever�o receber este identificador como par�metro.
********************************/
int CriaObjeto(char* nomeArquivo,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjeto(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o CriaObjeto() � respons�vel por criar um objeto. Qualquer objeto que for necess�rio,
pode ser criado atrav�s dessa fun��o. O objeto ainda n�o ser� desenhado, apenas criado dentro do jogo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto original que ser� copiado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o objeto.
Retorno:
inteiro que representa o identificador �nico do objeto. Todas as opera��es subsequentes com este objeto dever�o receber este identificador como par�metro.
********************************/
int CriaObjeto(int idObjeto,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjeto(idObjeto,retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o CriaObjetoOffScreen() � respons�vel por criar um objeto a partir da imagem que est� sendo montanda pelo
renderizador Offscreen. O renderizador precisa ter sido preparado anteriormente.
Par�metros:
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
Retorno:
inteiro que representa o identificador �nico do objeto. Todas as opera��es subsequentes com este objeto dever�o receber este identificador como par�metro.
********************************/
int CriaObjetoOffScreen(int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorSprites::CriaObjetoOffScreen(jogo->GetOffScreenRender(),retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o GetFrameAtualObjeto() recupera o valor do frame atual exibido no objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
N�mero do frame atual do objeto.
********************************/
int GetFrameAtualObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetFrameAtual();
}

/********************************
A fun��o DestroiObjeto() � respons�vel por eliminar o objeto em quest�o do jogo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser exclu�do.
********************************/
void DestroiObjeto(int idObjeto){
    CPIGGerenciadorSprites::DestroiObjeto(idObjeto);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto,int indice,int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorInt(indice,valor);
}

/********************************
A fun��o SetValorFloatObjeto() � respons�vel incorporar a um objeto um atributo float.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto,int indice,float valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorFloat(indice,valor);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto,int indice,char *valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorString(indice,valor);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int idObjeto,char *indice,int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorInt(indice,valor);
}

/********************************
A fun��o SetValorFloatObjeto() � respons�vel incorporar a um objeto um atributo float.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int idObjeto,char *indice,float valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorFloat(indice,valor);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado ao objeto.
********************************/
void SetValorStringObjeto(int idObjeto,char *indice,char *valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorString(indice,valor);
}

/********************************
A fun��o GetValorIntObjeto() � respons�vel recuperar o valor de um atributo inteiro relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntObjeto(int idObjeto,int indice,int *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorInt(indice,*valor);
}

/********************************
A fun��o GetValorFloatObjeto() � respons�vel recuperar o valor de um atributo float relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatObjeto(int idObjeto,int indice,float *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorFloat(indice,*valor);
}

/********************************
A fun��o GetValorStringObjeto() � respons�vel recuperar o valor de um atributo string relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringObjeto(int idObjeto,int indice,char *valor){
    std::string str;
    bool resp = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A fun��o GetValorIntObjeto() � respons�vel recuperar o valor de um atributo inteiro relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por refer�ncia): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntObjeto(int idObjeto,char *indice,int *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorInt(indice,*valor);
}

/********************************
A fun��o GetValorFloatObjeto() � respons�vel recuperar o valor de um atributo float relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatObjeto(int idObjeto,char *indice,float *valor){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorFloat(indice,*valor);
}

/********************************
A fun��o GetValorStringObjeto() � respons�vel recuperar o valor de um atributo string relacionado a um objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringObjeto(int idObjeto,char *indice,char *valor){
    std::string str;
    bool resp = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A fun��o GetXYObjeto() � respons�vel recuperar o valor da posi��o (X,Y) do objeto de acordo com o sistema de coordenadas do jogo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (sa�da, passagem por referencia): indica a posicao no eixo X do objeto.
posicaoY (sa�da, passagem por referencia): indica a posicao no eixo Y do objeto.
********************************/
void GetXYObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o MoveObjeto() � respons�vel por movimentar um determinado objeto para uma nova posi��o informada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja reposicionar o objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja reposicionar o objeto.
********************************/
void MoveObjeto(int idObjeto,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Move(posicaoX,posicaoY);
}

/********************************
A fun��o DeslocaObjeto() � respons�vel por deslocar um determinado objeto em rela��o � sua posi��o atual.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser movido.
deltaX (entrada, passagem por valor): valor a ser somado ou subtra�do na componente X da posi��o do objeto.
deltaY (entrada, passagem por valor): valor a ser somado ou subtra�do na componente Y da posi��o do objeto.
********************************/
void DeslocaObjeto(int idObjeto,int deltaX,int deltaY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Desloca(deltaX,deltaY);
}

/********************************
A fun��o SetAnguloObjeto() � respons�vel pela angula��o de determinado objeto. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O objeto ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaObjeto(). A detec��o de colis�o n�o funciona com objetos fora da angula��o padr�o (0 graus).
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
angulo (entrada, passagem por valor): valor para indicar a angula��o do objeto em graus.
********************************/
void SetAnguloObjeto(int idObjeto, float angulo){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetAngulo(angulo);
}

/********************************
A fun��o GetAnguloObjeto() � respons�vel por recuperar o �ngulo de rota��o de determinado objeto. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O objeto ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaObjeto(). A detec��o de colis�o n�o funciona com objetos fora da angula��o padr�o (0 graus).
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Retorna o valor do �ngulo em graus.
********************************/
float GetAnguloObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetAngulo();
}

/********************************
A fun��o SetPivoAbsolutoObjeto() define um ponto (X,Y) em rela��o ao ponto (0,0) do objeto, sobre o qual o objeto ser�
rotacionado quando a fun��o SetAnguloObjeto() for executada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do objeto.
********************************/
void SetPivoAbsolutoObjeto(int idObjeto,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetPivoAbsoluto({posicaoX,posicaoY});
}

/********************************
A fun��o SetPivoProporcionalObjeto() define um ponto (X,Y) proporcional ao tamanho do objeto, sobre o qual o objeto ser�
rotacionado quando a fun��o SetAnguloObjeto() for executada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
relX (entrada, passagem por valor): porcentagem da largura do objeto onde ficar� o piv�.
relY (entrada, passagem por valor): porcentagem da altura do objeto onde ficar� o piv�.
********************************/
void SetPivoProporcionalObjeto(int idObjeto,float relX,float relY){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetPivoProporcional({relX,relY});
}

/********************************
A fun��o GetPivoObjeto() define um ponto (X,Y) em rela��o ao ponto (0,0) do objeto, sobre o qual o objeto ser�
rotacionado quando a fun��o SetAnguloObjeto() for executada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
posicaoX (sa�da, passagem por refer�ncia): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do objeto.
posicaoY (sa�da, passagem por refer�ncia): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do objeto.
********************************/
void GetPivoObjeto(int idObjeto,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o SetFlipObjeto() � respons�vel por virar o objeto, invertendo-o em alguma dire��o. O objeto somente ser�
desenhado na nova orienta��o no pr�ximo comando DesenhaObjeto().
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de invers�o),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipObjeto(int idObjeto,PIG_Flip valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetFlip(valor);
}

/********************************
A fun��o GetFlipObjeto() � respons�vel por recuperar o valor da manipula��o causada pela fun��o SetFlipObjeto().
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de invers�o),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetFlip();
}

/********************************
A fun��o SetDimensoesObjeto() � respons�vel por delimitar a altura e a largura do objeto que ser� desenhado na tela,
independentemente do tamanho original do arquivo de imagem.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesObjeto(int idObjeto, int altura, int largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetDimensoes(altura,largura);
}

/********************************
A fun��o GetDimensoesObjeto() � respons�vel por recuperar a altura e a largura da �rea a ser usada
para desenhar o objeto na tela. Em outras palavras, representa o tamanho atual do objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (sa�da, passagem por refer�ncia): altura atual em pixels do objeto.
largura (sa�da, passagem por refer�ncia): largura atual em pixels do objeto.
********************************/
void GetDimensoesObjeto(int idObjeto, int *altura, int *largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetDimensoes(*altura,*largura);
}

/********************************
A fun��o GetDimensoesOriginaisObjeto() � respons�vel por recuperar a altura e a largura originais da imagem
que foi usada para criar o objeto. Qualquer utiliza��o da fun��o SetDimensoesObjeto() � ignorada para
o c�lculo desta fun��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
altura (sa�da, passagem por refer�ncia): altura original em pixels do objeto.
largura (sa�da, passagem por refer�ncia): largura original em pixels do objeto.
********************************/
void GetDimensoesOriginaisObjeto(int idObjeto, int *altura, int *largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetDimensoesOriginais(*altura,*largura);
}

/********************************
A fun��o RestauraDimensoesOriginaisObjeto() � respons�vel por restaurar o objeto com o tamanho original da imagem.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void RestauraDimensoesOriginaisObjeto(int idObjeto, int altura, int largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->RestauraDimensoesOriginais();
}


/********************************
A fun��o CriaFrameObjeto() � respons�vel por delimitar o posicionamento dos pixels do arquivo de imagem que ser�o
utilizados para representar o objeto na tela. Desta forma, nem toda a imagem ser� automaticamente utilizada para
representar o objeto. O sistema de coordenadas deve ser o padr�o dos arquivos de imagem, com o eixo Y aumentando para baixo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
idFrame (entrada, passagem por valor): identificador do frame a ser criado.
xBitmap (entrada, passagem por valor): indica a posi��o de eixo X onde come�a o frame.
yBitmap (entrada, passagem por valor): indica a posi��o de eixo Y onde come�a o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameObjeto(int idObjeto, int idFrame, int xBitmap, int yBitmap, int altura, int largura){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DefineFrame(idFrame, {xBitmap,yBitmap,largura,largura});
}


/********************************
A fun��o CarregaArquivoFramesObjeto() � respons�vel por ler de arquivo texto os frames de um objeto.
Cada linha do arquivo texto deve conter 5 n�meros inteiros: o n�mero do frame, a posi��o do frame no eixo X do arquivo de imagem,
a posi��o do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
nomeArq (entrada, passagem por refer�ncia): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesObjeto(int idObjeto, char *nomeArq){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CarregaArquivoFrames(nomeArq);
}

/********************************
A fun��o CarregaFramesPorLinhaObjeto() � respons�vel por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivis�o representar� um frame que ser� automaticamente criado para a anima��o, com numera��o incremental a partir do par�metro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a defini��o dos frames continua na linha inferior.
A fun��o pode ser utilizada em spritesheets regulares.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
frameInicial (entrada, passagem por valor): numera��o do primeiro frame a ser criado pela fun��o. Os demais frames ter�o numera��o consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem ser� dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem ser� dividido.
********************************/
void CarregaFramesPorLinhaObjeto(int idObjeto, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A fun��o CarregaFramesPorColunaObjeto() � respons�vel por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivis�o representar� um frame que ser� automaticamente criado para a anima��o, com numera��o incremental a partir do par�metro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a defini��o dos frames continua na coluna seguinte.
A fun��o pode ser utilizada em spritesheets regulares.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
frameInicial (entrada, passagem por valor): numera��o do primeiro frame a ser criado pela fun��o. Os demais frames ter�o numera��o consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem ser� dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem ser� dividido.
********************************/
void CarregaFramesPorColunaObjeto(int idObjeto, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A fun��o MudaFrameObjeto() � respons�vel por modificar o frame (j� definido pela fun��o DefineFrameObjeto) de um objeto
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
idFrame (entrada, passagem por valor): identificador do frame j� criado.
Retorno:
Se o identifador do frame informado n�o corresponder a um frame j� criado, o valor de retorno � igual a 0. Caso contr�rio, � igual a 1.
********************************/
int MudaFrameObjeto(int idObjeto, int idFrame){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->MudaFrameAtual(idFrame);
}

/********************************
A fun��o SetColoracaoObjeto() � respons�vel por mesclar uma determinada cor com os pixels do arquivo de imagem.
Ap�s a modifica��o, todos os desenhos deste objeto ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoObjeto(int idObjeto, PIG_Cor cor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetColoracao(cor);
}

/********************************
A fun��o SetOpacidadeObjeto() � respons�vel por modificar o n�vel de opacidade do objeto.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
valor (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255.
********************************/
void SetOpacidadeObjeto(int idObjeto,int valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetOpacidade(valor);
}

/********************************
A fun��o GetOpacidadeObjeto() � respons�vel por recuperar o n�vel de opacidade de determinado objeto.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Retorna o n�vel de opacidade do objeto na faixa 0-255.
********************************/
int GetOpacidadeObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetOpacidade();
}

/********************************
A fun��o DesenhaObjeto() � respons�vel por desenhar um objeto na tela. O objeto ser� desenhado de acordo com todas as defini��es
de posi��o e �ngulo informado at� o momento. Al�m disso, se o objeto estiver virado (flipping), isso tamb�m ser� levado em considera��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
********************************/
void DesenhaObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Desenha();
}

/********************************
A fun��o DesenhaObjetoOffScreen() � respons�vel por desenhar um objeto no Renderizador Offscreen. O objeto ser� desenhado de acordo com todas as defini��es
de posi��o e �ngulo informado at� o momento. Al�m disso, se o objeto estiver virado (flipping), isso tamb�m ser� levado em considera��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
offScreen (entrada, passagem por valor): indica se o objeto deve ser desenhado no Renderizador Offscreen.
********************************/
void DesenhaObjetoOffScreen(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DesenhaOffScreen(jogo->GetOffScreenRender());
}

/********************************
A fun��o TestaColisaoObjetos() � respons�vel por testar se dois objetos se colidiram ou n�o, ao passar
os identificadores dos objetos por par�metro.
Par�metros:
idObjeto1 (entrada, passagem por valor): identificador do primeiro objeto.
idObjeto2 (entrada, passagem por valor): identificador do segundo objeto.
Retorno:
Inteiro indicando se houve colis�o (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int TestaColisaoObjetos(int idObjeto1,int idObjeto2){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto1)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto2))
           &&CPIGGerenciadorSprites::GetObjeto(idObjeto2)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto1));
}

/********************************
A fun��o DefineAreaColisaoObjeto() � respons�vel estabelecer um pol�gono que ser� utilizado como �rea de colis�o do objeto com os demais.
Os vetores X e Y deve ter pelo menos qtdPontos elementos.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos, contendo os valores X de cada ponto do pol�gono.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos, contendo os valores Y de cada ponto do pol�gono.
qtdPontos (entrada, passagem por valor): quantidade de pontos do pol�gono.
********************************/
void DefineAreaColisaoObjeto(int idObjeto, int pontosX[], int pontosY[], int qtdPontos) {
    std::vector<PIGPonto2D> vertices;

    for (int i = 0; i < qtdPontos; i++) {
        vertices.push_back({pontosX[i], pontosY[i]});
    }

    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetVertices(vertices);
}

/********************************
A fun��o DefineRaioColisaoObjeto() � respons�vel por estabelecer um raio, em rela��o ao piv� do objeto, que ser� utilizado para teste de colis�o circular deste objeto com os demais.
A defini��o do raio s� ser� �til se o tipode colis�o deste objeto for circular, definido pela fun��o DefineTipoColisaoObjeto().
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
raio (entrada, passagem por valor): tamanho do raio que formar� a �rea de colis�o deste objeto.
********************************/
void DefineRaioColisaoObjeto(int idObjeto, float raio){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetRaioColisaoCircular(raio);
}

/********************************
A fun��o DefineTipoColisaoObjeto() � respons�vel por definir o tipod e colis�o que ser� utilizada por este objeto com os demais.
� poss�vel ter 3 tipos de colis�o: por bouding-box (PIG_COLISAO_OOBB - �rea de colis�o delimitada pelo ponto X,Y do objeto, sua altura e largura e rota��o),
por pol�gono (PIG_COLISAO_POLIGONO) �rea de colis�o formada por pontos gen�ricos) e circular (PIG_COLISAO_CIRCULAR) �rea de colis�o em forma de c�rculo, com raio definido a partir do ponto piv�)
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
modo (entrada, passagem por valor): modo de colis�o a ser utilizado por este objeto.
********************************/
void DefineTipoColisaoObjeto(int idObjeto, PIG_ModoColisao modo){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetModoColisao(modo);
}

/********************************
A fun��o GetPixelsObjeto() � respons�vel por extrair os pixels da imagem que originou o objeto, devolvendo-os como
uma matriz de pixels (PIG_Cor). Mudan�as nessa matriz s� ser�o validadas ap�s a chamada da fun��o AtualizaPixelsObjeto().
O linha 0 corresponde � primeira linha da imagem, ou seja, � linha superior, pois o sistema de coordenadas
das imagens tem o eixo Y aumentando para baixo.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
matriz de pixels (PIG_Cor) da imagem que gerou o objeto. O total de linhas da matriz � dado pela altura original do objeto e o
total de colunas � dado pela largura original do objeto. Ambos os valores podem ser obtidos pela fun��o GetDimensoesOriginaisObjeto().
********************************/
PIG_Cor **GetPixelsObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetPixels();
}

/********************************
A fun��o AtualizaPixelsObjeto() � respons�vel por efetivar quaisquer mudan�as nos pixels do objeto obtidos pela fun��o GetPixelsObjeto().
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
********************************/
void AtualizaPixelsObjeto(int idObjeto,int retiraFundo=1){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->AtualizaPixels(retiraFundo);
}

/********************************
A fun��o InsereTransicaoObjeto() � respons�vel por criar e inserir uma nova transi��o ao final de sequ�ncia de transi��es do objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
tempo (entrada, passagem por valor): duracao (em segundos) da transi��o.
deltaX (entrada, passagem por valor): diferen�a da posi��o no eixo X em rela��o � posi��o do objeto no in�cio da transi��o.
deltaY (entrada, passagem por valor): diferen�a da posi��o no eixo Y em rela��o � posi��o do objeto no in�cio da transi��o.
deltaAltura (entrada, passagem por valor): diferen�a da altura do objeto em rela��o ao in�cio da transi��o.
deltaLargura (entrada, passagem por valor): diferen�a da largura do objeto em rela��o ao in�cio da transi��o.
deltaAngulo (entrada, passagem por valor): diferen�a de �ngulo (em graus) do objeto em rela��o ao in�cio da transi��o.
corFinal (entrada, passagem por valor): colora��o do objeto ao final da transi��o.
deltaOpacidade (entrada, passagem por valor): diferen�a do n�vel de opacidade do objeto em rela��o ao in�cio da transi��o.
********************************/
void InsereTransicaoObjeto(int idObjeto,double tempo,int deltaX,int deltaY,int deltaAltura,int deltaLargura,double deltaAngulo,PIG_Cor corFinal,int deltaOpacidade){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A fun��o ExecutandoTransicaoObjeto() retorna a informa��o sobre a execu��o (neste momento) de transi��es do objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
Retorno:
inteiro que indica se o objeto est� executando alguma transi��o no momento (valor diferente de 0) ou n�o (valor igual a 0).
********************************/
int ExecutandoTransicaoObjeto(int idObjeto){
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->ExecutandoTransicao();
}

/********************************
A fun��o LeArquivoTransicaoObjeto() � respons�vel por ler, criar e inserir as transi��es para um objeto, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transi��o (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transi��o.
2) um inteiro representando a diferen�a da posi��o no eixo X em rela��o � posi��o do objeto no in�cio da transi��o.
3) um inteiro representando a diferen�a da posi��o no eixo Y em rela��o � posi��o do objeto no in�cio da transi��o.
4) um inteiro representando a diferen�a da altura do objeto em rela��o ao in�cio da transi��o.
5) um inteiro representando a diferen�a da largura do objeto em rela��o ao in�cio da transi��o.
6) um double representando a diferen�a de �ngulo (em graus) do objeto em rela��o ao in�cio da transi��o.
7) um inteiro representando a componente R (vermelho) da colora��o do objeto ao final da transi��o.
8) um inteiro representando a componente G (verde) da colora��o do objeto ao final da transi��o.
9) um inteiro representando a componente B (azul) da colora��o do objeto ao final da transi��o.
10) um inteiro representando a componente A (canal alfa) da colora��o do objeto ao final da transi��o.
11) um inteiro representando a diferen�a do n�vel de opacidade do objeto em rela��o ao in�cio da transi��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
nomeArq (entrada, passagem por refer�ncia): nome com extens�o do arquivo texto contendo as transi��es.
********************************/
void LeArquivoTransicaoObjeto(int idObjeto,char *nomeArq){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LeTransicoes(nomeArq);
}

/********************************
A fun��o IniciaAutomacaoObjeto() � respons�vel por iniciar as transi��es j� inseridas no objeto, de acordo como o tipo de transi��o informada.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void IniciaAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->IniciaAutomacao();
}

/********************************
A fun��o TrataAutomacaoObjeto() � respons�vel por calcular o estado da transi��o corrente do objeto e aplicar essas modifica��o a ela.
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void TrataAutomacaoObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->TrataAutomacao();
}

/********************************
A fun��o DefineTipoTransicaoObjeto() � respons�vel por determinar como a sequ�ncia de transi��es ser� executada.
� poss�vel faz�-la uma �nica vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo at� o final da sequ�ncia e retornando, em vai-v�m (PIG_TRANSICAO_VAIVEM).
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void DefineTipoTransicaoObjeto(int idObjeto,PIG_TipoTransicao valor){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DefineTipoTransicao(valor);
}

/********************************
A fun��o LimpaTransicoesObjeto() � respons�vel por remover a sequ�ncia de transi��es do objeto.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
********************************/
void LimpaTransicoesObjeto(int idObjeto){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LimpaTransicoes();
}

/********************************
A fun��o InsereAcaoObjeto() � respons�vel por inserir na linha de tempo de automa��o do objeto uma a��o a ser executada.
A a��o � composta por uma fun��o "acao" que ser� executada quando a linha de tempo atingir o par�metro "tempo" e ser� repetida a cada "repeticao" segundos.
A a��o pode armazenar um ponteiro gen�rico "param" que ser� utilizado na chamada da fun��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador do objeto.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da fun��o.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a pr�xima. O valor -1 indica que a fun��o n�o ser� repetida.
param (entrada, passagem por refer�ncia): ponteiro gen�rico para um valor que ser� utilizado na chamada da fun��o.
********************************/
void InsereAcaoObjeto(int idObjeto,double tempo,double repeticao,PIG_FuncaoSimples acao,void *param){
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->InsereAcao(tempo,repeticao,acao,param);
}


/********************************
Se��o de gerador de part�culas
********************************/

/********************************
A fun��o CriaGeradorParticulas() cria um novo gerador de part�culas (GDP). As part�culas em si precisam ser criadas
posteriormente atrav�s da fun��o CriaParticula(), passando o identificador do GDP como par�metro.
Par�metros:
maxParticulas (entrada, passagem por valor): informa o maior n�mero de part�culas que o gerador ter� simultaneamente. O maior valor aceito � PIG_MAX_PARTICULAS part�culas.
nomeArquivo (entrada, passagem por refer�ncia): indica o caminho relativo ou absoluto do arquivo de imagem,
que ser� utilizado para cada part�cula do GDP.
audioCriacao (entrada, passagem por valor n�o-obrigat�rio): indica qual audio previamente criado deve ser tocado quando uma part�cula for efetivamente criada.
audioEncerramento (entrada, passagem por valor n�o-obrigat�rio): indica qual audio previamente criado deve ser tocado quando uma part�cula for destruida por acabar o tempo de vida ou por sair da �rea de ativa��o.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulas(int maxParticulas,char* nomeArquivo,int audioCriacao=-1,int audioEncerramento=-1,int retiraFundo=1,PIG_Cor *corFundo=NULL, int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,nomeArquivo,audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o CriaGeradorParticulasPorAnimacao() cria um novo gerador de part�culas (GDP). As part�culas em si precisam ser criadas
posteriormente atrav�s da fun��o CriaParticula(), passando o identificador do GDP como par�metro. As part�culas ser�o semelhantes a uma anima��o j� criada anteriormente
que � indicada pelo par�metro idAnima��o.
Par�metros:
maxParticulas (entrada, passagem por valor): informa o maior n�mero de part�culas que o gerador ter� simultaneamente. O maior valor aceito � PIG_MAX_PARTICULAS part�culas.
idAnimacao (entrada, passagem por refer�ncia): identificador da anima��o (j� criada anteriormente) que ser� utilizada
para cada part�cula do GDP.
audioCriacao (entrada, passagem por valor n�o-obrigat�rio): indica qual audio previamente criado deve ser tocado quando uma part�cula for efetivamente criada.
audioEncerramento (entrada, passagem por valor n�o-obrigat�rio): indica qual audio previamente criado deve ser tocado quando uma part�cula for destruida por acabar o tempo de vida ou por sair da �rea de ativa��o.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulasPorAnimacao(int maxParticulas,int idAnimacao,int audioCriacao=-1,int audioEncerramento=-1,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,CPIGGerenciadorSprites::GetAnimacao(idAnimacao),audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o CriaGeradorParticulasPorObjeto() cria um novo gerador de part�culas (GDP). As part�culas em si precisam ser criadas
posteriormente atrav�s da fun��o CriaParticula(), passando o identificador do GDP como par�metro. As part�culas ser�o semelhantes a um objeto j� criado anteriormente
que � indicado pelo par�metro idObjeto.
Par�metros:
maxParticulas (entrada, passagem por valor): informa o maior n�mero de part�culas que o gerador ter� simultaneamente. O maior valor aceito � PIG_MAX_PARTICULAS part�culas.
idObjeto (entrada, passagem por refer�ncia): identificador do objeto (j� criado anteriormente) que ser� utilizado
para cada part�cula do GDP.
audioCriacao (entrada, passagem por valor n�o-obrigat�rio): indica qual audio previamente criado deve ser tocado quando uma part�cula for efetivamente criada.
audioEncerramento (entrada, passagem por valor n�o-obrigat�rio): indica qual audio previamente criado deve ser tocado quando uma part�cula for destruida por acabar o tempo de vida ou por sair da �rea de ativa��o.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber o GDP.
********************************/
int CriaGeradorParticulasPorObjeto(int maxParticulas,int idObjeto,int audioCriacao=-1,int audioEncerramento=-1,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorGDP::CriaGeradorParticulas(maxParticulas,CPIGGerenciadorSprites::GetObjeto(idObjeto),audioCriacao,audioEncerramento,retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o DestroiGeradorParticulas() encerra um gerador de part�culas (GDP). Todas as part�culas relacionadas a ele tamb�m s�o finalizadas
neste momento.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
********************************/
void DestroiGeradorParticulas(int idGerador){
    CPIGGerenciadorGDP::DestroiGeradorParticulas(idGerador);
}

/********************************
A fun��o MoveGeradorParticulas() reposiciona um gerador de part�culas (GDP). Na pr�tica, isto significa que as novas part�culas que
forem criadas posteriormente ter�o esse ponto de origem.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): informa a nova posi��o X do GDP, em rela��o ao sistema de coordenadas do jogo.
posicaoY (entrada, passagem por valor): informa a nova posi��o Y do GDP, em rela��o ao sistema de coordenadas do jogo.
********************************/
void MoveGeradorParticulas(int idGerador,int posicaoX,int posicaoY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Move(posicaoX,posicaoY);
}

/********************************
A fun��o DeslocaGeradorParticulas() � respons�vel por deslocar uma determinado gerador de part�culas (GDP) em rela��o � sua posi��o atual.
Par�metros:
idGerador (entrada, passagem por valor): identificador do GDP a ser deslocada.
deltaX (entrada, passagem por valor): valor a ser somado ou subtra�do na componente X da posi��o do GDP.
deltaY (entrada, passagem por valor): valor a ser somado ou subtra�do na componente Y da posi��o do GDP.
********************************/
void DeslocaGeradorParticulas(int idGerador,int deltaX,int deltaY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Desloca(deltaX,deltaY);
}

/*
/********************************
A fun��o MudaDirecaoParticulas() modifica a dire��o na qual as part�culas se movimentar�o ap�s serem criadas.
Somente as part�culas criadas posteriormente seguir�o a dire��o especificada.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
valorX (entrada, passagem por valor): informa a componente X da dire��o a ser definida para as part�culas.
valorY (entrada, passagem por valor): informa a componente Y da dire��o a ser definida para as part�culas.
********************************/
//void MudaDirecaoParticulas(int idGerador,int valorX,int valorY){
    //CPIGGerenciadorParticulas::GetGerador(idGerador)->MudaDirecao(valorX,valorY);
//}

/********************************
A fun��o InsereTransicaoParticulas() � respons�vel por criar e inserir uma nova transi��o ao final de sequ�ncia de transi��es das part�culas do gerador.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): duracao (em segundos) da transi��o das part�culas.
deltaX (entrada, passagem por valor): diferen�a da posi��o no eixo X em rela��o � posi��o das part�culas no in�cio da transi��o.
deltaY (entrada, passagem por valor): diferen�a da posi��o no eixo Y em rela��o � posi��o das part�culas no in�cio da transi��o.
deltaAltura (entrada, passagem por valor): diferen�a da altura das part�culas em rela��o ao in�cio da transi��o.
deltaLargura (entrada, passagem por valor): diferen�a da largura das part�culas em rela��o ao in�cio da transi��o.
deltaAngulo (entrada, passagem por valor): diferen�a de �ngulo (em graus) das part�culas em rela��o ao in�cio da transi��o.
corFinal (entrada, passagem por valor): colora��o das part�culas ao final da transi��o.
deltaOpacidade (entrada, passagem por valor): diferen�a do n�vel de opacidade das part�culas em rela��o ao in�cio da transi��o.
********************************/
void InsereTransicaoParticulas(int idGerador,double tempo,int deltaX,int deltaY,int deltaAlt,int deltaLarg,double deltaAng,PIG_Cor corFinal, int deltaOpacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereTransicao(tempo,{deltaX,deltaY,deltaAlt,deltaLarg,deltaAng,corFinal,deltaOpacidade});
}

/********************************
A fun��o DefineTipoTransicaoParticulas() � respons�vel por determinar como a sequ�ncia de transi��es das part�culas do gerador ser� executada.
� poss�vel faz�-la uma �nica vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo at� o final da sequ�ncia e retornando, em vai-v�m (PIG_TRANSICAO_VAIVEM).
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void DefineTipoTransicaoParticulas(int idGerador,PIG_TipoTransicao valor){
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineTipoTransicao(valor);
}

/********************************
A fun��o LimpaTransicoesParticulas() � respons�vel por remover a sequ�ncia de transi��es das part�culas do gerador.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador de part�culas.
********************************/
void LimpaTransicoesParticulas(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaTransicoes();
}

/********************************
A fun��o InsereTransicaoGDP() � respons�vel por criar e inserir uma nova transi��o ao final de sequ�ncia de transi��es do gerador em si.
Essa transi��o modifica as caracter�sticas do gerador, que podem se refletir tamb�m nas caracter�sticas das part�culas que ser�o posteriormente criadas usando o pr�prio gerador como modelo.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): duracao (em segundos) da transi��o do gerador.
deltaX (entrada, passagem por valor): diferen�a da posi��o no eixo X em rela��o � posi��o do gerador no in�cio da transi��o.
deltaY (entrada, passagem por valor): diferen�a da posi��o no eixo Y em rela��o � posi��o do gerador no in�cio da transi��o.
deltaAltura (entrada, passagem por valor): diferen�a da altura que o modelo ter� em rela��o ao in�cio da transi��o.
deltaLargura (entrada, passagem por valor): diferen�a da largura que o modelo ter� em rela��o ao in�cio da transi��o.
deltaAngulo (entrada, passagem por valor): diferen�a de �ngulo (em graus) que o modelo ter� em rela��o ao in�cio da transi��o.
corFinal (entrada, passagem por valor): colora��o que o modelo ter� ao final da transi��o.
deltaOpacidade (entrada, passagem por valor): diferen�a do n�vel de opacidade que o modelo ter� em rela��o ao in�cio da transi��o.
********************************/
void InsereTransicaoGDP(int idGerador,double tempo,int deltaX,int deltaY,int deltaAlt,int deltaLarg,double deltaAng,PIG_Cor corFinal, int deltaOpacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereTransicaoGDP(tempo,{deltaX,deltaY,deltaAlt,deltaLarg,deltaAng,corFinal,deltaOpacidade});
}

/********************************
A fun��o LeArquivoTransicaoGDP() � respons�vel por ler, criar e inserir as transi��es para um gerador, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transi��o (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transi��o.
2) um inteiro representando a diferen�a da posi��o no eixo X em rela��o � posi��o do gerador no in�cio da transi��o.
3) um inteiro representando a diferen�a da posi��o no eixo Y em rela��o � posi��o do gerador no in�cio da transi��o.
4) um inteiro representando a diferen�a da altura do modelo em rela��o ao in�cio da transi��o.
5) um inteiro representando a diferen�a da largura do modelo em rela��o ao in�cio da transi��o.
6) um double representando a diferen�a de �ngulo (em graus) do modelo em rela��o ao in�cio da transi��o.
7) um inteiro representando a componente R (vermelho) da colora��o do modelo ao final da transi��o.
8) um inteiro representando a componente G (verde) da colora��o do modelo ao final da transi��o.
9) um inteiro representando a componente B (azul) da colora��o do modelo ao final da transi��o.
10) um inteiro representando a componente A (canal alfa) da colora��o do modelo ao final da transi��o.
11) um inteiro representando a diferen�a do n�vel de opacidade do modelo em rela��o ao in�cio da transi��o.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
nomeArq (entrada, passagem por refer�ncia): nome com extens�o do arquivo texto contendo as transi��es.
********************************/
void LeTransicoesGDP(int idGerador,string nomeArq){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LeTransicoesGDP(nomeArq);
}

/********************************
A fun��o IniciaAutomacaoGDP() � respons�vel por iniciar as transi��es j� inseridas no gerador, de acordo como o tipo de transi��o informada.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void IniciaAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->IniciaAutomacaoGDP();
}

/********************************
A fun��o LimpaTransicoesGDP() � respons�vel por remover a sequ�ncia de transi��es do gerador de part�culas em si.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador de part�culas.
********************************/
void LimpaTransicoesGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaTransicoesGDP();
}

/********************************
A fun��o ExecutandoTransicaoGDP() retorna a informa��o sobre a execu��o (neste momento) de transi��es do gerador.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
Retorno:
inteiro que indica se o gerador est� executando alguma transi��o no momento (valor diferente de 0) ou n�o (valor igual a 0).
********************************/
bool ExecutandoTransicaoGDP(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->ExecutandoTransicaoGDP();
}

/********************************
A fun��o TrataAutomacaoGDP() � respons�vel por calcular o estado da transi��o corrente do gerador e aplicar essas modifica��o a ela.
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void TrataAutomacaoGDP(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->TrataAutomacaoGDP();
}

/********************************
A fun��o InsereAcaoGDP() � respons�vel por inserir na linha de tempo de automa��o do gerador uma a��o a ser executada.
A a��o � composta por uma fun��o "acao" que ser� executada quando a linha de tempo atingir o par�metro "tempo" e ser� repetida a cada "repeticao" segundos.
A a��o pode armazenar um ponteiro gen�rico "param" que ser� utilizado na chamada da fun��o.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da fun��o.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a pr�xima. O valor -1 indica que a fun��o n�o ser� repetida.
param (entrada, passagem por refer�ncia): ponteiro gen�rico para um valor que ser� utilizado na chamada da fun��o.
********************************/
void InsereAcaoGDP(int idGerador,double tempo, double repeticao, PIG_FuncaoSimples acao, void *param){
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereAcaoGDP(tempo,repeticao,acao,param);
}

/********************************
A fun��o DefineTipoTransicaoGDP() � respons�vel por determinar como a sequ�ncia de transi��es do gerador de part�culas ser� executada.
� poss�vel faz�-la uma �nica vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo at� o final da sequ�ncia e retornando, em vai-v�m (PIG_TRANSICAO_VAIVEM).
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador.
********************************/
void DefineTipoTransicaoGDP(int idGerador,PIG_TipoTransicao tipo){
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineTipoTransicaoGDP(tipo);
}

/********************************
A fun��o SetAnguloParticulas() modifica o �ngulo de desenho das part�culas ap�s serem criadas.
Somente as part�culas criadas posteriormente ter�o o �ngulo especificada.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
angulo (entrada, passagem por valor): informa o angulo das part�culas.
********************************/
void SetAnguloParticulas(int idGerador,double angulo){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetAngulo(angulo);
}

/********************************
A fun��o MudaCorParticulas() � respons�vel por mesclar uma determinada cor com os pixels do arquivo de imagem da part�cula.
Ap�s a modifica��o, todos os desenhos desta part�cula ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem da part�cula.
********************************/
void SetCorParticulas(int idGerador,PIG_Cor cor){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetColoracao(cor);
}

/********************************
A fun��o SetOpacidadeParticulas() modifica a opacidade das part�culas ap�s serem criadas.
Somente as part�culas criadas posteriormente ter�o a opacidade especificada.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
opacidade (entrada, passagem por valor): informa a opacidade das part�culas.
********************************/
void SetOpacidadeParticulas(int idGerador,int opacidade){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetOpacidade(opacidade);
}

/********************************
A fun��o SetDimensoesParticulas() modifica o tamanho das part�culas ap�s serem criadas.
Somente as part�culas criadas posteriormente ter�o o tamanho definido.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
altura (entrada, passagem por valor): informa a altura da part�cula ao ser criada.
largura (entrada, passagem por valor): informa a largura da part�cula ao ser criada.
********************************/
void SetDimensoesParticulas(int idGerador,int altura, int largura){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetDimensoes(altura,largura);
}

/********************************
A fun��o SetPivoAbsolutoParticulas() determina o ponto a ser considerado como pivo da part�cula.
Somente as part�culas criadas posteriormente ter�o o piv� especificado.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) da part�cula.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) da part�cula.
********************************/
void SetPivoAbsolutoParticulas(int idGerador,int posicaoX,int posicaoY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetPivoAbsoluto({posicaoX,posicaoY});
}

/********************************
A fun��o SetPivoProporcionalParticula() define um ponto (X,Y) proporcional ao tamanho da part�cula, sobre o qual o part�cula ser�
rotacionado quando a fun��o SetAnguloParticula() for executada.
Par�metros:
idGerador (entrada, passagem por valor): identificador do gerador de part�culas.
relX (entrada, passagem por valor): porcentagem da largura da part�cula onde ficar� o piv�.
relY (entrada, passagem por valor): porcentagem da altura da part�cula onde ficar� o piv�.
********************************/
void SetPivoProporcionalParticulas(int idGerador,float relX,float relY){
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetPivoProporcional({relX,relY});
}

/********************************
A fun��o CriaParticula() adiciona uma nova part�cula ao jogo relacionada com o GDP passado como par�metro.
A part�culas � criada com todas as caracter�sticas (�ngulo, cor, tamanho, posi��o, transi��es etc) que forem correntes ao gerador neste momento.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
Retorno:
inteiro indicando a quantidade atual de part�culas do gerador (valor maior ou igual a zero).
Se a part�cula n�o tiver sido criada por excesso de part�culas ativas, o valor retornado � -1.
********************************/
int CriaParticula(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->CriaParticula();
}

/********************************
A fun��o DefineLimitesParticula() � respons�vel por definir um espa�o no cen�rio onde a part�cula ser� considerada ativa.
Tamb�m � definido um tempo de vida m�ximo, ap�s o qual a part�cula n�o ser� mais considerada ativa.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
minX (entrada, passagem por valor): valor m�nimo de X para que a part�cula seja considerada ativa
minY (entrada, passagem por valor): valor m�nimo de Y para que a part�cula seja considerada ativa
maxX (entrada, passagem por valor): valor m�ximo de X para que a part�cula seja considerada ativa
maxY (entrada, passagem por valor): valor m�ximo de Y para que a part�cula seja considerada ativa
maxTempo (entrada, passagem por valor): tempo m�ximo de vida da part�cula
********************************/
void DefineLimitesParticula(int idGerador,int minX,int minY,int maxX,int maxY,double maxTempo){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->DefineLimites({minX,minY,maxX,maxY},maxTempo);
}

/********************************
A fun��o QuantidadeParticulasAtivas() indica quantas part�culas do GDP em quest�o ainda est�o ativas. As part�culas deixam de
ser ativas quando saem da tela do jogo, quando colidem com algum objeto ou quando esgotam seu tempo de vida.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
Retorno:
inteiro que indica o n�mero de part�culas ativas.
********************************/
int QuantidadeParticulasAtivas(int idGerador){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->GetQtdAtivas();
}

/********************************
A fun��o DesenhaParticulas() desenha todas as part�culas ativas do GDP na posi��o que estiverem.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
********************************/
void DesenhaParticulas(int idGerador){
    CPIGGerenciadorGDP::GetGerador(idGerador)->Desenha();
}

/********************************
A fun��o TestaColisaoParticulasObjeto() indica se houve colis�o de alguma part�cula ativa do GDP com um outro objeto espec�fico, atrav�s do seu identificador.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com as part�culas do GDP.
Retorno:
inteiro que indica se houve colis�o de alguma part�cula ativa do GDP (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int TestaColisaoParticulasObjeto(int idGerador,int idObjeto){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto));
}

/********************************
A fun��o TestaColisaoParticulasAnimacao() indica se houve colis�o de alguma part�cula ativa do GDP com uma outra anim��o espec�fica, atrav�s do seu identificador.
Par�metros:
idGerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o CriaGeradorParticulas().
idAnimacao (entrada, passagem por valor): identificador da anima��o que pode ter colidido com as part�culas do GDP.
Retorno:
inteiro que indica se houve colis�o de alguma part�cula ativa do GDP (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int TestaColisaoParticulasAnimacao(int idGerador,int idAnimacao){
    return CPIGGerenciadorGDP::GetGerador(idGerador)->Colisao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao));
}


/********************************
Se��o dos temporizadores
********************************/

/********************************
A fun��o CriaTimer() � respons�vel por criar um timer (temporizador). Ap�s a cria��o o tempo decorrido
poder� ser obtido a partir da fun��o TempoDecorrido(), informando o identificador que � passado na resposta.
Par�metros:
congelado (entrada, passagem por valor): valor l�gico que indica se o timer deve ser criado sem iniciar de imediato a contagem de tempo ou n�o.
Retorno:
inteiro que identifica o timer criado.
********************************/
int CriaTimer(int congelado=false){
    return CPIGGerenciadorTimers::CriaTimer(congelado);
}

/********************************
A fun��o TempoDecorrido() � respons�vel por informar o tempo decorrido desde a cria��o do timer
at� a hora em que a fun��o for chamada.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
Retorno:
n�mero real indicando o tempo (em segundos) desde a cria��o do timer.
********************************/
double TempoDecorrido(int idTimer){
    return CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido();
}

/********************************
A fun��o PausaTimer() � respons�vel por realizar uma pausa na contagem do tempo de um timer. Ap�s a despausa,
o timer continuar� a contar o tempo normalmente.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void PausaTimer(int idTimer){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Pausa();
}

/********************************
A fun��o PausaTudo() � respons�vel por realizar uma pausa na contagem do tempo de todos os timers
criados pela fun��o CriaTimer();
********************************/
void PausaTudo(){
    CPIGGerenciadorTimers::PausaTodos();
}

/********************************
A fun��o DespausaTimer() � respons�vel por retomar a contagem do tempo de todos os timers ap�s uma pausa.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DespausaTimer(int idTimer){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Despausa();
}

/********************************
A fun��o DespausaTudo() � respons�vel por retomar a contagem do tempo de todos os timers
criados pela fun��o CriaTimer();
********************************/
void DespausaTudo(){
    CPIGGerenciadorTimers::DespausaTodos();
}

/********************************
A fun��o ReiniciaTimer() � respons�vel por zerar a contagem do tempo de um timer, idependente do tempo j� decorrido.
Na pr�tica, � equivalente a encerrer um temporizador e recri�-lo em seguida.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
congelado (entrada, passagem por valor): valor l�gico que indica se o timer deve ser zerado sem iniciar de imediato a contagem de tempo ou n�o.
********************************/
void ReiniciaTimer(int idTimer, int congelado=false){
    CPIGGerenciadorTimers::GetTimer(idTimer)->Reinicia(congelado);
}

/********************************
A fun��o DestroiTimer() � respons�vel por encerrar a utiliza��o de timer.
Seu identificador n�o poder� ser utilizado ap�s a fun��o ser executada.
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
********************************/
void DestroiTimer(int idTimer){
    CPIGGerenciadorTimers::DestroiTimer(idTimer);
}

/********************************
A fun��o AssociaGrupoTimer() � respons�vel por associar um timer a um grupo espec�fico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma fun��o s�).
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
n�mero inteiro que indica se o grupo � v�lido (1) ou n�o (0).
********************************/
int AssociaGrupoTimer(int idTimer, int idGrupo){
    return CPIGGerenciadorTimers::AssociaTimerGrupo(idTimer,idGrupo);
}

/********************************
A fun��o DesassociaGrupoTimer() � respons�vel por desassociar um timer de um grupo espec�fico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma fun��o s�).
Par�metros:
idTimer (entrada, passagem por valor): identificador do timer.
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
n�mero inteiro que indica se o grupo � v�lido (1) ou n�o (0).
********************************/
int DesassociaGrupoTimer(int idTimer, int idGrupo){
    return CPIGGerenciadorTimers::DesassociaTimerGrupo(idTimer,idGrupo);
}

/********************************
A fun��o PausaGrupoTimers() � respons�vel por pausar todos os timers de um grupo espec�fico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma fun��o s�).
Par�metros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
n�mero inteiro que indica se o grupo � inv�lido (-1) ou quantos timers foram pausados no grupo (maior ou igual a 0).
********************************/
int PausaGrupoTimers(int idGrupo){
    return CPIGGerenciadorTimers::PausaGrupo(idGrupo);
}

/********************************
A fun��o DespausaGrupoTimers() � respons�vel por despausar todos os timers de um grupo espec�fico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma fun��o s�).
Par�metros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
Retorno:
n�mero inteiro que indica se o grupo � inv�lido (-1) ou quantos timers foram despausados no grupo (maior ou igual a 0).
********************************/
int DespausaGrupoTimers(int idGrupo){
    return CPIGGerenciadorTimers::DespausaGrupo(idGrupo);
}

/********************************
A fun��o ReiniciaGrupoTimers() � respons�vel por reiniciar todos os timers de um grupo espec�fico.
Os timers de um mesmo grupo pode ser tratados simultaneamente
(ex: diversos timers de um prsonagem/objeto podem ser pausados/despausados/reiniciados com uma fun��o s�).
Par�metros:
idGrupo (entrada, passagem por valor): identificador do grupos (qualquer valor entre 0 e PIG_MAX_GRUPOS_TIMERS-1).
congelado (entrada, passagem por valor): valor l�gico que indica se o timer deve ser zerado sem iniciar de imediato a contagem de tempo ou n�o.
Retorno:
n�mero inteiro que indica se o grupo � inv�lido (-1) ou quantos timers foram reiniciados no grupo (maior ou igual a 0).
********************************/
int ReiniciaGrupoTimers(int idGrupo, int congelado=false){
    return CPIGGerenciadorTimers::ReiniciaGrupo(idGrupo,congelado);
}



/********************************
Se��o das anima��es
********************************/

/********************************
A fun��o CriaAnimacao() � respons�vel por criar uma animacao. A anima��o pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequ�ncia completa de
sprites � chamada de modo. Uma mesma anima��o pode apresentar v�rios modos diferentes.
Para que a anima��o funcione corretamente, ser� necess�rio: definir cada frame (peda�o do arquivo bitmap que cont�m o sprite desejado),
criar um ou mais modos, inserir os frames criados no modo correspondente e dizer qual modo dever� ser exibido inicialmente.
Tudo isso pode ser feito por outras fun��es que manipulam as anima��es.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo da imagem (spritesheet) da anima��o.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a anima��o.
Retorno:
inteiro que representa o identificador �nico da anima��o. Todas as opera��es subsequentes com esta anima��o dever�o receber este identificador como par�metro.
********************************/
int CriaAnimacao(char* nomeArquivo,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(nomeArquivo,retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o CriaAnimacao() � respons�vel por criar uma animacao a partir de outra j� existente. A anima��o pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequ�ncia completa de
sprites � chamada de modo. Uma mesma anima��o pode apresentar v�rios modos diferentes.
Esta forma de criar uma anima��o, copia todos os frames e modos de outra anima��o j� existente, evitando assim
que toda esta prepara��o precise ser feita novamente. O usu�rio deve ter cuidado de n�o destruir a anima��o
original enquanto as c�pias estiverem ativas ou haver� erros de execu��o. Da mesma forma, n�o se deve alterar os
frames ou os modos da c�pia, pois pode provocar erros na anima��o original.
Par�metros:
idAnimacao (entrada, passagem por valor): indica o identificador da anima��o original que ser� copiada.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a anima��o.
Retorno:
inteiro que representa o identificador �nico da anima��o. Todas as opera��es subsequentes com esta anima��o dever�o receber este identificador como par�metro.
********************************/
int CriaAnimacao(int idAnimacao,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao),retiraFundo,corFundo,idJanela);
}

/********************************
A fun��o CriaAnimacaoDeObjeto() � respons�vel por criar uma animacao a partir de um objeto j� existente. A anima��o pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequ�ncia completa de
sprites � chamada de modo. Uma mesma anima��o pode apresentar v�rios modos diferentes.
Esta forma de criar uma anima��o, copia todos os frames e modos de outra anima��o j� existente, evitando assim
que toda esta prepara��o precise ser feita novamente. O usu�rio deve ter cuidado de n�o destruir a anima��o
original enquanto as c�pias estiverem ativas ou haver� erros de execu��o. Da mesma forma, n�o se deve alterar os
frames ou os modos da c�pia, pois pode provocar erros na anima��o original.
Par�metros:
idObjeto (entrada, passagem por valor): indica o identificador do objeto original que servir� de base para a cria��o da anima��o.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
corFundo (entrada, passagem por refer�ncia n�o-obrigat�rio): indica se h� uma cor espec�fica para ser considerada como cor de fundo da imagem. Caso, o valor seja NULL, mas o par�metro retiraFundo seja diferente de 0, o pixel (0,0) da imagem ser� considerado como cor de fundo.
idJanela (entrada, passagem por valor n�o-obrigat�rio): indica qual janela vai receber a anima��o.
Retorno:
inteiro que representa o identificador �nico da anima��o. Todas as opera��es subsequentes com esta anima��o dever�o receber este identificador como par�metro.
********************************/
int CriaAnimacaoDeObjeto(int idObjeto,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0){
    return CPIGGerenciadorSprites::CriaAnimacao(CPIGGerenciadorSprites::GetObjeto(idObjeto),retiraFundo,corFundo,idJanela);
}


/********************************
A fun��o DestroiAnimacao() � respons�vel por eliminar a anima��o em quest�o do jogo.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser exclu�da.
********************************/
void DestroiAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::DestroiSprite(idAnimacao);
}

/********************************
A fun��o CriaFrameAnimacao() � respons�vel por estabelecar uma parte do sprisheet da anima��o que cont�m um sprite espec�fico.
O frame criado deve ser posteriormente inserido em um ou mais modos da anima��o. O posicionamento do frame
respeita o sistema de coordenadas dos arquivos de imagem, com o eixo Y aumentando para baixo.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ter um novo frame.
codigoFrame (entrada, passagem por valor): numero do frame a ser criado. Pode ser usado qualquer n�mero de 0..MAX_FRAMES-1.
xBitmap (entrada, passagem por valor): indica a posi��o de eixo X onde come�a o frame.
yBitmap (entrada, passagem por valor): indica a posi��o de eixo Y onde come�a o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameAnimacao(int idAnimacao,int codigoFrame,int xBitmap,int yBitmap,int altura,int largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DefineFrame(codigoFrame,{xBitmap,yBitmap,largura,altura});
}

/********************************
A fun��o CarregaArquivoFramesAnimacao() � respons�vel por ler de arquivo texto os frames de uma anima��o.
Cada linha do arquivo texto deve conter 5 n�meros inteiros: o n�mero do frame, a posi��o do frame no eixo X do arquivo de imagem,
a posi��o do frame no eixo Y do arquivo de imagem, a altura do frame e a largura do frame (todas as unidades em pixels).
Par�metros:
idObjeto (entrada, passagem por valor): identificador da anima��o.
nomeArq (entrada, passagem por refer�ncia): nome do arquivo texto contendo os frames.
********************************/
void CarregaArquivoFramesAnimacao(int idAnimacao, char *nomeArq){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CarregaArquivoFrames(nomeArq);
}

/********************************
A fun��o CarregaFramesPorLinhaAnimacao() � respons�vel por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivis�o representar� um frame que ser� automaticamente criado para a anima��o, com numera��o incremental a partir do par�metro "frameInicial".
Ao final das "qtdColunas" da primeira linha, a defini��o dos frames continua na linha inferior.
A fun��o pode ser utilizada em spritesheets regulares.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
frameInicial (entrada, passagem por valor): numera��o do primeiro frame a ser criado pela fun��o. Os demais frames ter�o numera��o consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem ser� dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem ser� dividido.
********************************/
void CarregaFramesPorLinhaAnimacao(int idAnimacao, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaFramesAutomaticosPorLinha(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A fun��o CarregaFramesPorColunaAnimacao() � respons�vel por subdividir o arquivo de imagem em linhas (de mesmo tamanho) e colunas (de mesmo tamanho).
Cada subdivis�o representar� um frame que ser� automaticamente criado para a anima��o, com numera��o incremental a partir do par�metro "frameInicial".
Ao final das "qtdLinhas" da primeira coluna, a defini��o dos frames continua na coluna seguinte.
A fun��o pode ser utilizada em spritesheets regulares.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
frameInicial (entrada, passagem por valor): numera��o do primeiro frame a ser criado pela fun��o. Os demais frames ter�o numera��o consecutiva.
qtdLinhas (entrada, passagem por valor): quantidade de linhas na qual o arquivo de imagem ser� dividido.
qtdColunas (entrada, passagem por valor): quantidade de colunas na qual o arquivo de imagem ser� dividido.
********************************/
void CarregaFramesPorColunaAnimacao(int idAnimacao, int frameInicial, int qtdLinhas, int qtdColunas){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaFramesAutomaticosPorColuna(frameInicial,qtdLinhas,qtdColunas);
}

/********************************
A fun��o CriaModoAnimacao() � respons�vel por criar um modo, ou seja, uma sequ�ncia de sprites.
Ap�s a cria��o do modo, os frames deve ser inseridos um a um. O modo pode ser criado antes dos frames
e vice-versa, mas os frames s� podem ser associados ao modo, ap�s as respectivas cria��es.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ter um novo modo.
codigoModo (entrada, passagem por valor): numero do modo a ser criado. Pode ser usado qualquer n�mero de 0..MAX_MODOS-1.
loop (entrada, passagem por valor): valor l�gico que indica se este modo deve recome�ar do primeiro frame ap�s a execu��o do �ltimo.
********************************/
void CriaModoAnimacao(int idAnimacao,int codigoModo,int loop){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaModo(codigoModo,loop);
}

/********************************
A fun��o InsereFrameAnimacao() � respons�vel por associar os frames aos modos correspondentes.
Um mesmo frame pode fazer parte de diversos modos.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o em quest�o.
codigoModo (entrada, passagem por valor): numero do modo a ter um frame inserido.
codigoFrame (entrada, passagem por valor): numero do frame a ser inserido no modo.
tempo (entrada, passagem por valor): dura��o (em segundos) da exibi��o autom�tica do frame neste modo espec�fico.
idAudio (entrada, passagem por valor n�o-obrigat�rio): identificador do audio (j� criado anteriormente) que deve ser tocado quando o frame for exibido. O valor -1 deve ser utilizado se nenhum audio deve ser tocado.
alturaAnimacao (entrada, passagem por valor n�o-obrigat�rio): tamanho em pixels altura da anima��o quando estiver exibindo este frame. Um valor negativo neste par�metro ou no pr�ximo (larguraAnimacao) indica que n�o haver� altera��o de dimens�es da anima��o.
larguraAnimacao (entrada, passagem por valor n�o-obrigat�rio): tamanho em pixels largura da anima��o quando estiver exibindo este frame. Um valor negativo neste par�metro ou no anterior (alturaAnimacao) indica que n�o haver� altera��o de dimens�es da anima��o.
********************************/
void InsereFrameAnimacao(int idAnimacao,int codigoModo, int codigoFrame, float tempo, int idAudio=-1, int alturaAnimacao=-1, int larguraAnimacao=-1){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereFrame(codigoModo,codigoFrame,tempo,idAudio,alturaAnimacao,larguraAnimacao);
}


/********************************
A fun��o InsereAudioFrameAnimacao() � respons�vel por acrescentar um audio a um dos frames.
O audio � tocado assim que o frame � desenhado pela primeira vez.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o em quest�o.
codigoModo (entrada, passagem por valor): n�mero do modo a ter um frame inserido.
indiceFrame (entrada, passagem por valor): �ndice (posi��o) do frame no modo em quest�o.
idAudio (entrada, passagem por valor n�o-obrigat�rio): identificador do audio (j� criado anteriormente) que deve ser tocado quando o frame for exibido. O valor -1 deve ser utilizado se nenhum audio deve ser tocado.
********************************/
void InsereAudioFrameAnimacao(int idAnimacao, int codigoModo, int indiceFrame, int idAudio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAudioFrame(codigoModo,indiceFrame,idAudio);
}

/********************************
A fun��o MudaModoAnimacao() � respons�vel por alterar a anima��o para um outro modo.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o em quest�o.
codigoModo (entrada, passagem por valor): numero do novo modo.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
forcado (entrada, passagem por valor): valor l�gico que indica se a mudan�a de modo deve ser feita for�osamente ou n�o. Se n�o for for�ada, a mudan�a s� ocorrer� se o modo atual j� tiver terminado de ser animado.
********************************/
void MudaModoAnimacao(int idAnimacao,int codigoModo,int indiceFrame,int forcado=1){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->MudaModo(codigoModo,indiceFrame,forcado);
}

/********************************
A fun��o GetModoAtualAnimacao() � respons�vel por recuperar o valor do modo atual da anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o em quest�o.
Retorno:
inteiro que representa o modo atual da anima��o.
********************************/
int GetModoAtualAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetModoAtual();
}

/********************************
A fun��o GetFrameAtualAnimacao() recupera o valor do frame atual exibido na anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
Retorno:
N�mero do frame atual da anima��o.
********************************/
int GetFrameAtualAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetFrameAtual();
}

/********************************
A fun��o TestaColisaoAnimacoes() indica se houve colis�o entre duas anima��es, de forma semelhante aos objetos.
Par�metros:
idAnimacao1 (entrada, passagem por valor): identificador da primeira anima��o.
idAnimacao2 (entrada, passagem por valor): identificador da segunda anima��o.
Retorno:
inteiro que indica se houve colis�o entre as anima��es.
********************************/
int TestaColisaoAnimacoes(int idAnimacao1,int idAnimacao2){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao1)->Colisao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao2));
}

/********************************
A fun��o TestaColisaoAnimacaoObjeto() indica se houve colis�o de alguma animacao com algum outro objeto espec�fico, atrav�s do seu identificador.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o que pode ter colidido com o objeto.
idObjeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com a anima��o.
Retorno:
inteiro que indica se houve colis�o da anima��o com o objeto.
********************************/
int TestaColisaoAnimacaoObjeto(int idAnimacao,int idObjeto){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto));
}


/********************************
A fun��o DefineAreaColisaoObjeto() � respons�vel estabelecer um pol�gono que ser� utilizado como �rea de colis�o da anima��o com as demais.
Os vetores X e Y deve ter pelo menos qtdPontos elementos.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos, contendo os valores X de cada ponto do pol�gono.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtdPontos, contendo os valores Y de cada ponto do pol�gono.
qtdPontos (entrada, passagem por valor): quantidade de pontos da anima��o.
********************************/
void DefineAreaColisaoAnimacao(int idAnimacao, int pontosX[], int pontosY[], int qtdPontos) {
    std::vector<PIGPonto2D> vertices;

    for (int i = 0; i < qtdPontos; i++) {
        vertices.push_back({pontosX[i], pontosY[i]});
    }

    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetVertices(vertices);
}

/********************************
A fun��o DefineRaioColisaoAnimacao() � respons�vel por estabelecer um raio, em rela��o ao piv� da anima��o, que ser� utilizado para teste de colis�o circular desta anima��o com as demais.
A defini��o do raio s� ser� �til se o tipode colis�o deste objeto for circular, definido pela fun��o DefineTipoColisaoObjeto().
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
raio (entrada, passagem por valor): tamanho do raio que formar� a �rea de colis�o desta anima��o.
********************************/
void DefineRaioColisaoAnimacao(int idAnimacao, float raio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetRaioColisaoCircular(raio);
}

/********************************
A fun��o DefineTipoColisaoAnimacao() � respons�vel por definir o tipod e colis�o que ser� utilizada por esta anima��o com as demais.
� poss�vel ter 3 tipos de colis�o: por bouding-box (PIG_COLISAO_OOBB - �rea de colis�o delimitada pelo ponto X,Y da anima��o, sua altura e largura e rota��o),
por pol�gono (PIG_COLISAO_POLIGONO) �rea de colis�o formada por pontos gen�ricos) e circular (PIG_COLISAO_CIRCULAR) �rea de colis�o em forma de c�rculo, com raio definido a partir do ponto piv�)
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
modo (entrada, passagem por valor): modo de colis�o a ser utilizado por esta anima��o.
********************************/
void DefineTipoColisaoAnimacao(int idAnimacao, PIG_ModoColisao modo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetModoColisao(modo);
}

/********************************
A fun��o DesenhaAnimacao() � respons�vel por desenhar uma anima��o na tela. A anima��o ser� desenhada de acordo com o modo atual da anima��o,
fazendo com que os frames sejam automaticamente ajustados de acordo com o tempo estipulado. Caso o modo atual esteja em loop, o primeiro frame ser�
desenhado novamente logo ap�s o t�rmino do �ltimo frame.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser desenhada.
Retorno:
inteiro que indica se a anima��o encerrou ou n�o. O valor s� ser� diferente de zero, se o modo atual tamb�m n�o estiver em loop.
********************************/
int DesenhaAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Desenha();
}

/********************************
A fun��o MoveAnimacao() � respons�vel por movimentar uma determinada anima��o para uma nova posi��o informada.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser movida.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja reposicionar a anima��o.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja reposicionar a anima��o.
********************************/
void MoveAnimacao(int idAnimacao,int x,int y){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Move(x,y);
}

/********************************
A fun��o DeslocaAnimcao() � respons�vel por deslocar uma determinada animacao em rela��o � sua posi��o atual.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
deltaX (entrada, passagem por valor): valor a ser somado ou subtra�do na componente X da posi��o da anima��o.
deltaY (entrada, passagem por valor): valor a ser somado ou subtra�do na componente Y da posi��o da anima��o.
********************************/
void DeslocaAnimacao(int idAnimacao,int deltaX,int deltaY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Desloca(deltaX,deltaY);
}

/********************************
A fun��o SetLoopModoAnimacao() � respons�vel por definir a exist�ncia ou n�o de loop em um modo de uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em quest�o.
loop (entrada, passagem por valor): valor que indica a exist�ncia (diferente de zero) ou n�o (igual a zero) de loop no modo em quest�o.
********************************/
void SetLoopModoAnimacao(int idAnimacao,int modo,int loop){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetLoopModo(modo,loop);
}

/********************************
A fun��o SetTempoFrameAnimacao() � respons�vel por definir uma nova dura��o para exibi��o do frame.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em quest�o.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
tempo (entrada, passagem por valor): valor que indica a nova dura��o de exibi��o do frame, em segundos.
********************************/
void SetTempoFrameAnimacao(int idAnimacao,int modo,int indiceFrame,float tempo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetTempoFrame(modo,indiceFrame,tempo);
}

/********************************
A fun��o SetAudioFrameAnimacao() � respons�vel por definir um novo audio a ser executado quando o frame em quest�o come�ar a ser exibido.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em quest�o.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
idAudio (entrada, passagem por valor): identificador do audio (j� criado) a ser tocado quando o frame come�ar a ser exibido.
********************************/
void SetAudioFrameAnimacao(int idAnimacao,int modo,int indiceFrame,int idAudio){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAudioFrame(modo,indiceFrame,idAudio);
}

/********************************
A fun��o GetLoopModoAnimacao() � respons�vel por recuperar a exist�ncia ou n�o de loop em um modo de uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em quest�o.
Retorno:
inteiro que indica a exist�ncia (diferente de zero) ou n�o (igual a zero) de loop no modo em quest�o.
********************************/
int GetLoopModoAnimacao(int idAnimacao,int modo){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetLoopModo(modo);
}

/********************************
A fun��o GetAudioFrameAnimacao() � respons�vel por recuprar o identificador do audio a ser executado quando o frame em quest�o come�ar a ser exibido.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em quest�o.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
Retorno:
inteiro que representa o identificador do audio (j� criado) a ser tocado quando o frame come�ar a ser exibido.
********************************/
int GetAudioFrameAnimacao(int idAnimacao,int modo,int indiceFrame){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetAudioFrame(modo,indiceFrame);
}

/********************************
A fun��o GetTempoFrameAnimacao() � respons�vel por recuperar a dura��o da exibi��o do frame.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
codigoModo (entrada, passagem por valor): numero do modo em quest�o.
indiceFrame (entrada, passagem por valor): indica a partir de qual frame o modo deve ser exibido. O valor 0 significa aprtir do primeiro frame.
Retorno:
float que indica a nova dura��o de exibi��o do frame, em segundos.
********************************/
float GetTempoFrameAnimacao(int idAnimacao,int modo,int indiceFrame){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetTempoFrame(modo,indiceFrame);
}

/********************************
A fun��o PausaAnimacao() � respons�vel por pausar a exibi��o dos frames da anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
********************************/
void PausaAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Pausa();
}

/********************************
A fun��o DespausaAnimacao() � respons�vel por despausar a exibi��o dos frames da anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da animacao a ser deslocada.
********************************/
void DesausaAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Despausa();
}

/********************************
A fun��o SetOpacidadeAnimacao() � respons�vel por modificar o n�vel de opacidade da anima��o.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
valor (entrada,passagem por valor): n�vel de opacidade da anima��o na faixa 0-255.
********************************/
void SetOpacidadeAnimacao(int idAnimacao,int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetOpacidade(valor);
}

/********************************
A fun��o GetOpacidadeAnimacao() � respons�vel por recuperar o n�vel de opacidade da anima��o.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
Retorno:
Retorna o n�vel de opacidade da anima��o na faixa 0-255.
********************************/
int GetOpacidadeAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetOpacidade();
}

/********************************
A fun��o SetColoracaoAnimacao() � respons�vel por mesclar uma determinada cor com os pixels do arquivo de imagem.
Ap�s a modifica��o, todos os desenhos desta anima��o ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoAnimacao(int idAnimacao,PIG_Cor cor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetColoracao(cor);
}

/********************************
A fun��o SetFlipAnimacao() � respons�vel por virar a anima��o, invertendo-a em alguma dire��o. A anima��o somente ser�
desenhada na nova orienta��o no pr�ximo comando DesenhaAnimacao().
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser virada.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de invers�o),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipAnimacao(int idAnimacao,PIG_Flip valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetFlip(valor);
}

/********************************
A fun��o GetFlipAnimacao() � respons�vel por recuperar o valor da manipula��o causada pela fun��o SetFlipAnimacao().
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o a ser virada.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de invers�o),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetFlip();
}

/********************************
A fun��o SetAnguloAnimacao() � respons�vel pela angula��o de determinada animacao. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). A anima��o ser� desenhada com a angula��o informada no pr�ximo comando
DesenhaAnimcao(). A detec��o de colis�o n�o funciona com anima��es fora da angula��o padr�o (0 graus).
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
angulo (entrada, passagem por valor): valor para indicar a angula��o da anima��o em graus.
********************************/
void SetAnguloAnimacao(int idAnimacao, double angulo){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAngulo(angulo);
}

/********************************
A fun��o GetAnguloAnimacao() � respons�vel por recuperar o �ngulo de rota��o de determinada anima��o. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). A anima��o ser� desenhada com a angula��o informada no pr�ximo comando
DesenhaAnimacao(). A detec��o de colis�o n�o funciona com anima��es fora da angula��o padr�o (0 graus).
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
Retorno:
Retorna o valor do �ngulo em graus.
********************************/
double GetAnguloAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetAngulo();
}

/********************************
A fun��o SetPivoAbsolutoAnimacao() define um ponto (X,Y) em rela��o ao ponto (0,0) da anima��o, sobre o qual a anima��o ser�
rotacionado quando a fun��o SetAnguloAnimacao() for executada.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) da anima��o.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) da anima��o.
********************************/
void SetPivoAbsolutoAnimacao(int idAnimacao,int posicaoX,int posicaoY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetPivoAbsoluto({posicaoX,posicaoY});
}

/********************************
A fun��o SetPivoProporcionalAnimacao() define um ponto (X,Y) proporcional ao tamanho da anima��o, sobre o qual a anima��o ser�
rotacionado quando a fun��o SetAnguloAnimacao() for executada.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
relX (entrada, passagem por valor): porcentagem da largura da anima��o onde ficar� o piv�.
relY (entrada, passagem por valor): porcentagem da altura da anima��o onde ficar� o piv�.
********************************/
void SetPivoProporcionalAnimacao(int idAnimacao,float relX,float relY){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetPivoProporcional({relX,relY});
}

/********************************
A fun��o GetPivoAnimacao() define um ponto (X,Y) em rela��o ao ponto (0,0) da animacao, sobre o qual a anima��o ser�
rotacionado quando a fun��o SetAnguloAnimacao() for executada.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (sa�da, passagem por refer�ncia): Valor da coordenada X do piv� em rela��o ao ponto (0,0) da anima��o.
posicaoY (sa�da, passagem por refer�ncia): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) da anima��o.
********************************/
void GetPivoAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o SetDimensoesAnimacao() � respons�vel por delimitar a altura e a largura da anima��o que ser� desenhada na tela,
independentemente do tamanho original do arquivo de imagem.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesAnimacao(int idAnimacao, int altura, int largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetDimensoes(altura,largura);
}

/********************************
A fun��o GetDimensoesAnimacao() � respons�vel por recuperar a altura e a largura da �rea a ser usada
para desenhar a anima��o na tela. Em outras palavras, representa o tamanho atual da anima��o.
Par�metros:
idObjeto (entrada, passagem por valor): identificador da anima��o.
altura (sa�da, passagem por refer�ncia): altura atual em pixels da anima��o.
largura (sa�da, passagem por refer�ncia): largura atual em pixels da anima��o.
********************************/
void GetDimensoesAnimacao(int idAnimacao, int *altura, int *largura){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetDimensoes(*altura,*largura);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo inteiro.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado � anima��o.
********************************/
void SetValorIntAnimacao(int idAnimacao,int indice,int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorInt(indice,valor);
}

/********************************
A fun��o SetValorFloatAnimacao() � respons�vel incorporar a uma anima��o um atributo float.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado � anima��o.
********************************/
void SetValorFloatAnimacao(int idAnimacao,int indice,float valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorFloat(indice,valor);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo inteiro.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado � anima��o.
********************************/
void SetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorString(indice,valor);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo inteiro.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado � anima��o.
********************************/
void SetValorIntAnimacao(int idAnimacao,char *indice,int valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorInt(indice,valor);
}

/********************************
A fun��o SetValorFloatAnimacao() � respons�vel incorporar a uma anima��o um atributo float.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado � anima��o.
********************************/
void SetValorFloatAnimacao(int idAnimacao,char *indice,float valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorFloat(indice,valor);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo inteiro.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por refer�ncia): relaciona uma string ao atributo.
valor (entrada, passagem por refer�ncia): valor do atributo string a ser associado � anima��o.
********************************/
void SetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorString(indice,valor);
}

/********************************
A fun��o GetValorIntAnimacao() � respons�vel recuperar o valor de um atributo inteiro relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntAnimacao(int idAnimacao,int indice,int *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorInt(indice,*valor);
}

/********************************
A fun��o GetValorFloatAnimacao() � respons�vel recuperar o valor de um atributo float relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatAnimacao(int idAnimacao,int indice,float *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorFloat(indice,*valor);
}

/********************************
A fun��o GetValorStringAnimacao() � respons�vel recuperar o valor de um atributo string relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringAnimacao(int idAnimacao,int indice,char *valor){
    std::string str;
    bool resp = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A fun��o GetValorIntAnimacao() � respons�vel recuperar o valor de um atributo inteiro relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por refer�ncia): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorIntAnimacao(int idAnimacao,char *indice,int *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorInt(indice,*valor);
}

/********************************
A fun��o GetValorFloatAnimacao() � respons�vel recuperar o valor de um atributo float relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorFloatAnimacao(int idAnimacao,char *indice,float *valor){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorFloat(indice,*valor);
}

/********************************
A fun��o GetValorStringAnimacao() � respons�vel recuperar o valor de um atributo string relacionado a uma anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o nome do atributo que se deseja recuperar.
valor (sa�da, passagem por refer�ncia): indica o valor do atributo, se a fun��o retornar um resultado diferente de zero.
Retorno:
Retorna um valor diferente de 0 (zero), se o atributo existir. Se o atributo n�o existir, a fun��o retorna o valor 0 (zero).
********************************/
int GetValorStringAnimacao(int idAnimacao,char *indice,char *valor){
    std::string str;
    bool resp = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorString(indice,str);
    strcpy(valor,str.c_str());
    return resp;
}

/********************************
A fun��o GetXYAnimacao() � respons�vel por recuperar o valor da posi��o (X,Y) da animacao de acordo com o sistema de coordenadas do jogo.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (sa�da, passagem por referencia): indica a posicao no eixo X da anima��o.
posicaoY (sa�da, passagem por referencia): indica a posicao no eixo Y da anima��o.
********************************/
void GetXYAnimacao(int idAnimacao,int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o InsereTransicaoAnimacao() � respons�vel por criar e inserir uma nova transi��o ao final de sequ�ncia de transi��es da anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
tempo (entrada, passagem por valor): duracao (em segundos) da transi��o.
deltaX (entrada, passagem por valor): diferen�a da posi��o no eixo X em rela��o � posi��o da anima��o no in�cio da transi��o.
deltaY (entrada, passagem por valor): diferen�a da posi��o no eixo Y em rela��o � posi��o da anima��o no in�cio da transi��o.
deltaAltura (entrada, passagem por valor): diferen�a da altura da anima��o em rela��o ao in�cio da transi��o.
deltaLargura (entrada, passagem por valor): diferen�a da largura da anima��o em rela��o ao in�cio da transi��o.
deltaAngulo (entrada, passagem por valor): diferen�a de �ngulo (em graus) da anima��o em rela��o ao in�cio da transi��o.
corFinal (entrada, passagem por valor): colora��o da anima��o ao final da transi��o.
deltaOpacidade (entrada, passagem por valor): diferen�a do n�vel de opacidade da anima��o em rela��o ao in�cio da transi��o.
********************************/
void InsereTransicaoAnimacao(int idAnimacao,double tempo,int deltaX,int deltaY,int deltaAltura,int deltaLargura,double deltaAngulo,PIG_Cor corFinal,int deltaOpacidade){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereTransicao(tempo,{deltaX,deltaY,deltaAltura,deltaLargura,deltaAngulo,corFinal,deltaOpacidade});
}

/********************************
A fun��o ExecutandoTransicaoAnimacao() retorna a informa��o sobre a execu��o (neste momento) de transi��es da anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
Retorno:
inteiro que indica se a anima��o est� executando alguma transi��o no momento (valor diferente de 0) ou n�o (valor igual a 0).
********************************/
int ExecutandoTransicaoAnimacao(int idAnimacao){
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->ExecutandoTransicao();
}

/********************************
A fun��o LeArquivoTransicaoAnimacao() � respons�vel por ler, criar e inserir as transi��es para uma anima��o, provenientes de um arquivo texto.
Cada linha do arquivo texto corresponde a uma transi��o (em ordem) e deve possuir 11 valores:
1) um double representando a duracao (em segundos) da transi��o.
2) um inteiro repreentando a diferen�a da posi��o no eixo X em rela��o � posi��o da anima��o no in�cio da transi��o.
3) um inteiro repreentando a diferen�a da posi��o no eixo Y em rela��o � posi��o da anima��o no in�cio da transi��o.
4) um inteiro repreentando a diferen�a da altura da anima��o em rela��o ao in�cio da transi��o.
5) um inteiro repreentando a diferen�a da largura da anima��o em rela��o ao in�cio da transi��o.
6) um double repreentando a diferen�a de �ngulo (em graus) da anima��o em rela��o ao in�cio da transi��o.
7) um inteiro repreentando a componente R (vermelho) da colora��o da anima��o ao final da transi��o.
8) um inteiro repreentando a componente G (verde) da colora��o da anima��o ao final da transi��o.
9) um inteiro repreentando a componente B (azul) da colora��o da anima��o ao final da transi��o.
10) um inteiro repreentando a componente A (canal alfa) da colora��o da anima��o ao final da transi��o.
11) um inteiro repreentando a diferen�a do n�vel de opacidade da anima��o em rela��o ao in�cio da transi��o.
Par�metros:
idSprite (entrada, passagem por valor): identificador da anima��o.
nomeArq (entrada, passagem por refer�ncia): nome com extens�o do arquivo texto contendo as transi��es.
********************************/
void LeArquivoTransicaoAnimacao(int idAnimacao,char *nomeArq){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LeTransicoes(nomeArq);
}

/********************************
A fun��o IniciaAutomacaoAnimacao() � respons�vel por iniciar as transi��es j� inseridas na anima��o, de acordo como o tipo de transi��o informada.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
********************************/
void IniciaAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->IniciaAutomacao();
}

/********************************
A fun��o TrataAutomacaoAnimacao() � respons�vel por calcular o estado da transi��o corrente da anima��o e aplicar essas modifica��o a ela.
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
********************************/
void TrataAutomacaoAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->TrataAutomacao();
}

/********************************
A fun��o DefineTipoTransicaoAnimacao() � respons�vel por determinar como a sequ�ncia de transi��es da anima��o ser� executada.
� poss�vel faz�-la uma �nica vez (PIG_TRANSICAO_NORMAL), em loop (PIG_TRANSICAO_LOOP) ou indo at� o final da sequ�ncia e retornando, em vai-v�m (PIG_TRANSICAO_VAIVEM).
A fun��o deve ser chamada a cada frame, para ter resultados mais precisos.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
********************************/
void DefineTipoTransicaoAnimacao(int idAnimacao,PIG_TipoTransicao valor){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DefineTipoTransicao(valor);
}

/********************************
A fun��o LimpaTransicoesAnimacao() � respons�vel por remover a sequ�ncia de transi��es do anima��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
********************************/
void LimpaTransicoesAnimacao(int idAnimacao){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LimpaTransicoes();
}

/********************************
A fun��o InsereAcaoAnimacao() � respons�vel por inserir na linha de tempo de automa��o do anima��o uma a��o a ser executada.
A a��o � composta por uma fun��o "acao" que ser� executada quando a linha de tempo atingir o par�metro "tempo" e ser� repetida a cada "repeticao" segundos.
A a��o pode armazenar um ponteiro gen�rico "param" que ser� utilizado na chamada da fun��o.
Par�metros:
idAnimacao (entrada, passagem por valor): identificador da anima��o.
tempo (entrada, passagem por valor): tempo (em segundos) da primeira chamada da fun��o.
repeticao (entrada, passagem por valor): tempo (em segundos) entre a chamada anterior e a pr�xima. O valor -1 indica que a fun��o n�o ser� repetida.
param (entrada, passagem por refer�ncia): ponteiro gen�rico para um valor que ser� utilizado na chamada da fun��o.
********************************/
void InsereAcaoAnimacao(int idAnimacao,double tempo,double repeticao,PIG_FuncaoSimples acao,void *param){
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereAcao(tempo,repeticao,acao,param);
}



/********************************
Se��o dos �udios
********************************/

/********************************
A fun��o CriaAudio() � respons�vel por ler e preparar um arquivo de audio.
Os formatos permitidos s�o WAVE, AIFF, RIFF, OGG, VOC.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo de �udio.
nLoops (entrada, passagem por valor): indica o n�mero de repeti��es do �udio. O valor 0 indica que ser� tocado apenas uma vez. O valor -1 indica que o audio deve ser tocado indefinidamente.
tempoExecucao (entrada, passage por valor): indica uma quantidade de milissegundos do arquivo de audio que dem ser tocados. O valor de -1 indica que todo o arquivo deve ser tocado.
Retorno:
Retorna o identificador do audio para ser utilizado por outras fun��es.
********************************/
int CriaAudio(char *nomeArquivo,int nLoops,int tempoExecucao=-1){
    return CPIGGerenciadorAudios::CriaAudio(nomeArquivo,nLoops,tempoExecucao);
}

/********************************
A fun��o DestroiAudio() � respons�vel por eliminar um �udio do jogo.
Par�metros:
idAudio (entrada, passagem por valor): identificador do �udio a ser exclu�do.
********************************/
void DestroiAudio(int idAudio){
    CPIGGerenciadorAudios::DestroiAudio(idAudio);
}

/********************************
A fun��o CarregaBackground() � respons�vel por ler e preparar um arquivo de audio para ser tocado em background.
Apenas um �nico arquivo de �udio para background � permitido. Os formatos permitidos s�o WAVE, MOD, MIDI, OGG, MP3, FLAC.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo de �udio.
********************************/
void CarregaBackground(char *nomeArquivo){
    CPIGGerenciadorAudios::CarregaBackground(nomeArquivo);
}

/********************************
A fun��o PlayBackground() � respons�vel por tocar um �udio de background previamente carregado.
Par�metros:
nVezes (entrada, passagem por valor): indica o n�mero de vezes que o background deve ser executado.
O valor -1 indica que deve ser tocado indefinidamente.
********************************/
void PlayBackground(int nVezes=-1){
    CPIGGerenciadorAudios::PlayBackground(nVezes);
}

/********************************
A fun��o StopBackground() � respons�vel por parar um �udio de background previamente carregado.
********************************/
void StopBackground(){
    CPIGGerenciadorAudios::StopBackground();
}

/********************************
A fun��o PauseBackground() � respons�vel por pausar um �udio de background previamente carregado.
********************************/
void PauseBackground(){
    CPIGGerenciadorAudios::PauseBackground();
}

/********************************
A fun��o ResumeBackground() � respons�vel por continuar a tocar um �udio de background previamente carregado.
********************************/
void ResumeBackground(){
    CPIGGerenciadorAudios::ResumeBackground();
}

/********************************
A fun��o GetStatusBackground() recupera o status do audio de background.
Retorno:
Retorna: o valor do status do �udio de background(AUDIO_TOCANDO, AUDIO_PARADO ou AUDIO_PAUSADO)
********************************/
PIG_StatusAudio GetStatusBackground(){
    return CPIGGerenciadorAudios::GetStatusBackground();
}

/********************************
A fun��o SetVolumeBackground() define o valor do volume do �udio de background.
Par�metro:
valor (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
void SetVolumeBackground(int valor){
    CPIGGerenciadorAudios::SetVolumeBackground(valor);
}

/********************************
A fun��o GetVolumeBackground() recupera o valor do volume do �udio de background.
Retorno:
Retorna o valor do volume do audio de background. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
int GetVolumeBackground(){
    return CPIGGerenciadorAudios::GetVolumeBackground();
}

/********************************
A fun��o SetVolumeBackground() define o valor do volume do �udio em quest�o.
Par�metro:
idAudio (entrada, passagem por valor): identificador do �udio.
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
void SetVolume(int idAudio,int volume){
    CPIGGerenciadorAudios::GetAudio(idAudio)->SetVolume(volume);
}

/********************************
A fun��o SetVolumeBackground() recupera o valor do volume do �udio em quest�o.
Par�metro:
idAudio (entrada, passagem por valor): identificador do �udio.
Retorno:
Retorna o valor do volume do audio. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
int GetVolume(int idAudio){
    return CPIGGerenciadorAudios::GetAudio(idAudio)->GetVolume();
}

/********************************
A fun��o SetVolumeBackground() define o valor do volume de todos os �udios.
Par�metro:
volume (entrada, passagem por valor): valor do novo volume a ser utilizado. Os valores devem ser entre 0 (mudo) e 128 (volume m�ximo).
********************************/
void SetVolumeTudo(int volume){
    CPIGGerenciadorAudios::SetVolumeTudo(volume);
}

/********************************
A fun��o PlayAudio() � respons�vel por tocar um �udio previamente criado.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
********************************/
void PlayAudio(int idAudio){
    CPIGGerenciadorAudios::Play(idAudio);
}

/********************************
A fun��o PauseAudio() � respons�vel por pausar um �udio que esteja tocandoo.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
********************************/
void PauseAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Pause();
}

/********************************
A fun��o ResumeAudio() � respons�vel por continuar a tocar um �udio pausado.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
********************************/
void ResumeAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Resume();
}

/********************************
A fun��o StopAudio() � respons�vel por parar um �udio pausado ou tocando.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
********************************/
void StopAudio(int idAudio){
    CPIGGerenciadorAudios::GetAudio(idAudio)->Stop();
}

/********************************
A fun��o GetStatusAudio() recupera o status do audio em quest�o.
Par�metro:
idAudio (entrada, passagem por valor): indentificador do �udio.
Retorno:
Retorna: o valor do status do �udio (AUDIO_TOCANDO, AUDIO_PARADO ou AUDIO_PAUSADO)
********************************/
PIG_StatusAudio GetStatusAudio(int idAudio){
    return CPIGGerenciadorAudios::GetAudio(idAudio)->GetStatus();
}

/********************************
A fun��o ResumeTudoAudio() � respons�vel por parar todos os �udios pausados ou tocando.
********************************/
void StopTudoAudio(){
    CPIGGerenciadorAudios::StopTudo();
}

/********************************
A fun��o PauseTudoAudio() � respons�vel por pausar todos os �udios que estiverem tocando.
********************************/
void PauseTudoAudio(){
    CPIGGerenciadorAudios::PauseTudo();
}

/********************************
A fun��o ResumeTudoAudio() � respons�vel por continuar a tocar todos os �udios pausados.
********************************/
void ResumeTudoAudio(){
    CPIGGerenciadorAudios::ResumeTudo();
}

/********************************
Se��o dos sockets
********************************/

/********************************
A fun��o CriaSocketCliente() � respons�vel por abrir uma conex�o TCP com um servidor por meio do seu hostname, que pode ser o nome do computador
em uma rede local ou seu endere�o IP, e uma porta. O servidor precisa estar online ou a conex�o n�o ser� estabelecida.
Par�metros:
hostname (entrada, passagem por valor): nome do computador (servidor) na rede local ou endere�o IP
porta (entrada, passagem por valor): n�mero da porta aberta no servidor
maxBytesPacote (entrada, passagem por valor): tamanho m�ximo de bytes enviados e/ou recebidos de cada vez
Retorno:
Identificador do socket cliente que foi criado.
********************************/
int CriaSocketCliente(char *hostname, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
    return CPIGGerenciadorSockets::CriaCliente(hostname,porta,maxBytesPacote);
}

/********************************
A fun��o CriaSocketServidor() � respons�vel por abrir um canal de comunica��o para transmiss�es entrantes (ingoing).
A cria��o do socket pode ser impedida por pol�ticas de acesso do firewall instalado.
Par�metros:
maxClientes (entrada, passagem por valor): n�mero m�ximo de clientes que poder�o se comunicar concomitantemente com o servidor.
porta (entrada, passagem por valor): n�mero da porta a ser aberta. Deve ser utilizado um valor na faixa 0-65535 que n�o esteja sendo utilizado por nenhum outro processo.
maxBytesPacote (entrada, passagem por valor): tamanho m�ximo de bytes enviados e/ou recebidos de cada vez.
Retorno:
Identificador do socket servidor que foi criado.
********************************/
int CriaSocketServidor(int maxClientes, int porta, int maxBytesPacote=PIG_MAX_MENSAGEM_REDE_TCP){
    return CPIGGerenciadorSockets::CriaServidor(maxClientes,porta,maxBytesPacote);
}

/********************************
A fun��o CriaSocketUDP() � respons�vel por abrir um canal de comunica��o transmiss�es de acordo com o protocolo UDP.
O mesmo socket � utilizado para envio e recebimento das inform��es, n�o havendo papel de cliente e servidor distintos.
Par�metros:
porta (entrada, passagem por valor): n�mero da porta a ser aberta. Deve ser utilizado um valor na faixa 0-65535 que n�o esteja sendo utilizado por nenhum outro processo.
Retorno:
Identificador do socket UDP que foi criado.
********************************/
int CriaSocketUDP(int porta){
    return CPIGGerenciadorSockets::CriaSocketUDP(porta);
}

/********************************
A fun��o DestroiSocketCliente() � respons�vel por fechar o socket cliente aberto, impossibilitando novos envios e recebimentos por ele.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketCliente(int idSocket){
    CPIGGerenciadorSockets::DestroiCliente(idSocket);
}

/********************************
A fun��o DestroiSocketServidor() � respons�vel por fechar o socket servidor aberto, impossibilitando novos envios e recebimentos por ele.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketServidor(int idSocket){
    CPIGGerenciadorSockets::DestroiServidor(idSocket);
}

/********************************
A fun��o DestroiSocketUDP() � respons�vel por fechar o socket UDP aberto, impossibilitando novos envios e recebimentos por ele.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket a ser fechado.
********************************/
void DestroiSocketUDP(int idSocket){
    CPIGGerenciadorSockets::DestroiSocketUDP(idSocket);
}

/********************************
A fun��o GetAtivoSocketCliente() � respons�vel por verificar se o socket cliente ainda est� ativo e conectado ao servidor ou n�o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket cliente ainda est� ativo e conectado (valor diferente de zero) ou n�o (valor zero)
********************************/
int GetAtivoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetAtivo();
}

/********************************
A fun��o GetAtivoSocketServidor() � respons�vel por verificar se o socket servidor ainda est� ativo ou n�o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket servidor ainda est� ativo (valor diferente de zero) ou n�o (valor zero)
********************************/
int GetAtivoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetAtivo();
}

/********************************
A fun��o GetAtivoSocketUDP() � respons�vel por verificar se o socket UDP ainda est� ativo ou n�o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que determina se o socket UDP ainda est� ativo (valor diferente de zero) ou n�o (valor zero)
********************************/
int GetAtivoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetAtivo();
}

/********************************
A fun��o GetBytesEnviadosSocketCliente() � respons�vel por recuperar a quantidade de bytes j� enviados atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados atrav�s do socket.
********************************/
long GetBytesEnviadosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetBytesEnviados();
}

/********************************
A fun��o GetBytesRecebidosSocketCliente() � respons�vel por recuperar a quantidade de bytes j� recebidos atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos atrav�s do socket.
********************************/
long GetBytesRecebidosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetBytesRecebidos();
}

/********************************
A fun��o GetPacotesEnviadosSocketCliente() � respons�vel por recuperar a quantidade de pacotes (mensagens) j� enviados atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados atrav�s do socket.
********************************/
long GetPacotesEnviadosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesEnviados();
}

/********************************
A fun��o GetPacotesRecebidosSocketCliente() � respons�vel por recuperar a quantidade de pacotes (mensagens) j� recebidos atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos atrav�s do socket.
********************************/
long GetPacotesRecebidosSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesRecebidos();
}

/********************************
A fun��o GetTempoUltimoRecebidoSocketCliente() � respons�vel por recuperar o momento em que o �ltimo pacote foi recebido pelo socket.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do �ltimo pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A fun��o GetTempoUltimoEnviadoSocketCliente() � respons�vel por recuperar o momento em que o �ltimo pacote foi enviado pelo socket.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do �ltimo pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A fun��o GetBytesEnviadosSocketServidor() � respons�vel por recuperar a quantidade de bytes j� enviados atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados atrav�s do socket.
********************************/
long GetBytesEnviadosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetBytesEnviados();
}

/********************************
A fun��o GetBytesRecebidosSocketServidor() � respons�vel por recuperar a quantidade de bytes j� recebidos atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos atrav�s do socket.
********************************/
long GetBytesRecebidosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetBytesRecebidos();
}

/********************************
A fun��o GetPacotesEnviadosSocketServidor() � respons�vel por recuperar a quantidade de pacotes (mensagens) j� enviados atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados atrav�s do socket.
********************************/
long GetPacotesEnviadosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesEnviados();
}

/********************************
A fun��o GetPacotesRecebidosSocketServidor() � respons�vel por recuperar a quantidade de pacotes (mensagens) j� recebidos atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos atrav�s do socket.
********************************/
long GetPacotesRecebidosSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesRecebidos();
}

/********************************
A fun��o GetTempoUltimoRecebidoSocketServidor() � respons�vel por recuperar o momento em que o �ltimo pacote foi recebido pelo socket.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do �ltimo pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A fun��o GetTempoUltimoEnviadoSocketServidor() � respons�vel por recuperar o momento em que o �ltimo pacote foi enviado pelo socket.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do �ltimo pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A fun��o GetBytesEnviadosSocketUDP() � respons�vel por recuperar a quantidade de bytes j� enviados atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes enviados atrav�s do socket.
********************************/
long GetBytesEnviadosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetBytesEnviados();
}

/********************************
A fun��o GetBytesRecebidosSocketUDP() � respons�vel por recuperar a quantidade de bytes j� recebidos atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de bytes recebidos atrav�s do socket.
********************************/
long GetBytesRecebidosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetBytesRecebidos();
}

/********************************
A fun��o GetPacotesEnviadosSocketUDP() � respons�vel por recuperar a quantidade de pacotes (mensagens) j� enviados atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes enviados atrav�s do socket.
********************************/
long GetPacotesEnviadosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPacotesEnviados();
}

/********************************
A fun��o GetPacotesRecebidosSocketUDP() � respons�vel por recuperar a quantidade de pacotes (mensagens) j� recebidos atrav�s do socket cliente desde a sua cria��o.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica a quantidade de pacotes recebidos atrav�s do socket.
********************************/
long GetPacotesRecebidosSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPacotesRecebidos();
}

/********************************
A fun��o GetTempoUltimoRecebidoSocketUDP() � respons�vel por recuperar o momento em que o �ltimo pacote foi recebido pelo socket.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do recebimento do �ltimo pacote pelo socket.
********************************/
long GetTempoUltimoRecebidoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetTempoUltimoRecebido();
}

/********************************
A fun��o GetTempoUltimoEnviadoSocketUDP() � respons�vel por recuperar o momento em que o �ltimo pacote foi enviado pelo socket.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro longo que indica o tempo do envio do �ltimo pacote pelo socket.
********************************/
long GetTempoUltimoEnviadoSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetTempoUltimoEnviado();
}

/********************************
A fun��o GetPortaRemotaSocketCliente() � respons�vel por recuperar o n�mero da porta remota (do servidor) � qual est� conectado o socket.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o n�mero da porta remota (do servidor) � qual est� conectado o socket.
********************************/
int GetPortaRemotaSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPortaRemota();
}

/********************************
A fun��o GetPortaLocalSocketServidor() � respons�vel por recuperar o n�mero da porta local que est� sendo utilizada pelo socket servidor.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o n�mero da porta local do socket servidor.
********************************/
int GetPortaLocalSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetPortaLocal();
}

/********************************
A fun��o GetPortaLocalSocketUDP() � respons�vel por recuperar o n�mero da porta local que est� sendo utilizada pelo socket UDP.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o n�mero da porta local do socket UDP.
********************************/
int GetPortaLocalSocketUDP(int idSocket){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPortaLocal();
}

/********************************
A fun��o GetHostRemotoSocketCliente() � respons�vel por recuperar o nome do computador (da rede local) ou do endere�o IP ao qual est� conectado o socket cliente, ou seja, o servidor.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (sa�da, passagem por refer�ncia): nome do computador (da rede local) ou do endere�o IP ao qual est� conectado o socket cliente.
********************************/
void GetHostRemotoSocketCliente(int idSocket,char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetCliente(idSocket)->GetHostRemoto().c_str());
}

/********************************
A fun��o GetHostLocalSocketCliente() � respons�vel por recuperar o nome do computador (na rede local) ou do endere�o IP da m�quina est� aberto o socket cliente.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (sa�da, passagem por refer�ncia): nome do computador (na rede local) ou do endere�o IP da m�quina no qual est� aberto o socket cliente.
********************************/
void GetHostLocalSocketCliente(int idSocket,char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetCliente(idSocket)->GetHostLocal().c_str());
}

/********************************
A fun��o GetHostLocalSocketServidor() � respons�vel por recuperar o nome do computador (na rede local) ou do endere�o IP da m�quina est� aberto o socket servidor.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (sa�da, passagem por refer�ncia): nome do computador (na rede local) ou do endere�o IP da m�quina no qual est� aberto o socket servidor.
********************************/
void GetHostLocalSocketServidor(int idSocket,char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetServidor(idSocket)->GetHostLocal().c_str());
}

/********************************
A fun��o GetHostLocalSocketUDP() � respons�vel por recuperar o nome do computador (na rede local) ou do endere�o IP da m�quina est� aberto o socket UDP.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
hostname (sa�da, passagem por refer�ncia): nome do computador (na rede local) ou do endere�o IP da m�quina no qual est� aberto o socket UDP.
********************************/
void GetHostLocalSocketUDP(int idSocket,char *hostname){
    strcpy(hostname,CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetHostLocal().c_str());
}

/********************************
A fun��o GetTamanhoPacoteSocketCliente() � respons�vel por recuperar o tamanho m�ximo de bytes utilizado pelo socket para envio ou recebimento de mensagens.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o tamanho m�ximo, em bytes, das mensagens enviadas ou recebidas pelo socket.
********************************/
int GetTamanhoPacoteSocketCliente(int idSocket){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTamanhoPacote();
}

/********************************
A fun��o GetTamanhoPacoteSocketServidor() � respons�vel por recuperar o tamanho m�ximo de bytes utilizado pelo socket para envio ou recebimento de mensagens.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica o tamanho m�ximo, em bytes, das mensagens enviadas ou recebidas pelo socket.
********************************/
int GetTamanhoPacoteSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTamanhoPacote();
}

/********************************
A fun��o GetMaximoConexoesSocketServidor() � respons�vel por recuperar a quantidade m�xima de conex�es que podem ser estabelecidas pelo socket servidor com outros sockets clientes.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica a quantidade m�xima de conex�es concomitantes que podem ser estabelecidas pelo socket servidor com outros sockets clientes.
********************************/
int GetMaximoConexoesSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetMaximoConexoes();
}

/********************************
A fun��o GetQuantidadeConexoesSocketServidor() � respons�vel por recuperar a quantidade de conex�es atualmente abertas pelo socket servidor com outros sockets clientes.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
Retorno:
Inteiro que indica a quantidade de conex�es atualmente abertas pelo socket servidor com outros sockets clientes.
********************************/
int GetQuantidadeConexoesSocketServidor(int idSocket){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetQuantidadeConexoes();
}

/********************************
A fun��o EnviaDadosSocketCliente() � respons�vel por efetivamente enviar bytes armazenados em mem�ria principal atrav�s do socket cliente, para o servidor.
O recebimento de dados atrav�s da rede pode ser detectado pela gera��o de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endere�o) para o local da mem�ria onde est�o armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endere�o indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketCliente(int idSocket,void *buffer, int tamanhoBuffer){
    return CPIGGerenciadorSockets::GetCliente(idSocket)->EnviaDados(buffer,tamanhoBuffer);
}

/********************************
A fun��o EnviaDadosSocketServidor() � respons�vel por efetivamente enviar bytes armazenados em mem�ria principal atrav�s do socket servidor, para o cliente.
O recebimento de dados atrav�s da rede pode ser detectado pela gera��o de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endere�o) para o local da mem�ria onde est�o armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endere�o indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketServidor(int idSocket,int socketSecundario,void *buffer, int tamanhoBuffer){
    return CPIGGerenciadorSockets::GetServidor(idSocket)->EnviaDados(buffer,tamanhoBuffer,socketSecundario);
}

/********************************
A fun��o EnviaDadosSocketUDP() � respons�vel por efetivamente enviar bytes armazenados em mem�ria principal atrav�s do socket UDP, para outro socket UDP.
O recebimento de dados atrav�s da rede pode ser detectado pela gera��o de um evento de rede. A mensagem transmitida deve ser recuperada a partir desse evento.
Par�metros:
idSocket (entrada, passagem por valor): identificador do socket.
buffer (entrada, passagem por valor): ponteiro (endere�o) para o local da mem�ria onde est�o armazenados os dados a serem transmitidos. Pode ser, inclusive, o nome de uma string ou vetor.
tamanhoBuffer (entrada, passagem por valor): quantidade de bytes que devem ser lidos e transmitidos a partir do endere�o indicado no buffer.
Retorno:
Inteiro que indica a quantidade de bytes efetivamente transmitida.
********************************/
int EnviaDadosSocketUDP(int idSocket,void *buffer,int tamanhoBuffer, char *hostRemoto, int porta){
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->EnviaDados(buffer,tamanhoBuffer,hostRemoto,porta);
}


#ifdef PIGCOMVIDEO

/********************************
Se��o dos v�deos.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Toda a parte de v�deo � considerada experimental e pode n�o funcionar dependendo do v�deo,
dos drives instalados, do sistema operacional ou do formato do v�deo.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
********************************/


/********************************
A fun��o CriaVideo() � respons�vel por ler e preparar um arquivo de v�deo.
Os formatos permitidos s�o AVI, MP4, MOV.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo de v�deo.
idJanela (entrada, passagem por valor): indica em qual janela o v�deo ser� exibido.
Retorno:
Retorna o identificador do v�deo para ser utilizado por outras fun��es.
********************************/
int CriaVideo(char *nomeArquivo,int idJanela=0){
    return CPIGGerenciadorVideos::CriaVideo(nomeArquivo,idJanela);
}

/********************************
A fun��o DestroiVideo() � respons�vel por eliminar um v�deo do jogo.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo a ser exclu�do.
********************************/
void DestroiVideo(int idVideo){
    CPIGGerenciadorVideos::DestroiVideo(idVideo);
}

/********************************
A fun��o SetSeekVideo() � respons�vel por avan�ar ou retroceder o v�deo instantaneamente.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
incremento (entrada, passagem por valor): quantidade de tempo (em segundos) para o avan�ao ou retrocesso do v�deo.
********************************/
void SetSeekVideo(int idVideo, double incremento){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetSeek(incremento);
}

/********************************
A fun��o PlayVideo() � respons�vel por tocar um v�deo previamente criado.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
********************************/
void PlayVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Play();
}

/********************************
A fun��o StopVideo() � respons�vel por parar um v�deo pausado ou tocando.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
********************************/
void StopVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Stop();
}

/********************************
A fun��o PauseVideo() � respons�vel por pausar um v�deo que esteja tocando.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
********************************/
void PauseVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Pause();
}

/********************************
A fun��o ResumeVideo() � respons�vel por continuar a tocar um v�deo pausado.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
********************************/
void ResumeVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Resume();
}

/********************************
A fun��o DesenhaVideo() � respons�vel por desenhar os frames de um v�deo na tela. O v�deo ser� desenhado de acordo com todas as defini��es
de posi��o e �ngulo informado at� o momento. Al�m disso, se o v�deo estiver virado (flipping), isso tamb�m ser� levado em considera��o, bem como a colora��o e a opacidade definidas.
Par�metro:
idVideo (entrada, passagem por valor): identificador do v�deo a ser desenhado.
********************************/
int DesenhaVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->Desenha();
}

/********************************
A fun��o SetVolumeVideo() � respons�vel por definir o volume para o v�deo. O valor informado deve ser positivo ou zero (mudo).
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
valor (entrada, passagem por valor): volume a ser definido. Deve ser positivo ou zero (mudo).
********************************/
void SetVolumeVideo(int idVideo, double valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetVolume(valor);
}

/********************************
A fun��o GetVolumeVideo() � respons�vel por recuperar o valor do volume do v�deo.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
Retorno:
N�vel de volume do v�deo (deve ser sempre um valor positivo).
********************************/
double GetVolumeVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetVolume();
}

/********************************
A fun��o GetNomeArquivoVideo() � respons�vel por recuperar o nome do arquivo que deu origem ao video.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
nome (sa�da, passagem por refer�ncia): nome do arquivo utilizado para criar o video.
********************************/
void GetNomeArquivoVideo(int idVideo, char *nome){
    strcpy(nome,CPIGGerenciadorVideos::GetVideo(idVideo)->GetNomeArquivo().c_str());
}

/********************************
A fun��o GetTempoAtualVideo() � respons�vel por recuperar o valor (em milissegundo) do tempo de v�deo j� exibido, ou seja, o momento atual do v�deo.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
Retorno:
Total de tempo (em milissegundos) da parte j� exibida do v�deo.
********************************/
double GetTempoAtualVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoAtual();
}

/********************************
A fun��o GetTempoAtualVideo() � respons�vel por recuperar uma string contendo a hora, minuto, segundo e milissegundo do frame atual do video.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
str (sa�da, passagem por refer�ncia): posi��o do frame atual, definido em hora, minuto, segundo e milissegundo.
********************************/
void GetTempoAtualVideo(int idVideo, char *str){
    strcpy(str,CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoAtualString().c_str());
}

/********************************
A fun��o GetTempoTotalVideo() � respons�vel por recuperar a drua��o total do v�deo (em milissegundo).
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
Retorno
Tempo total do v�deo em milissegundos.
********************************/
double GetTempoTotalVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoTotal();
}

/********************************
A fun��o GetTempoTotalVideo() � respons�vel por recuperar uma string contendo a dura��o do video em hora, minuto, segundo e milissegundo.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
str (sa�da, passagem por refer�ncia): dura��o do v�deo, definido em hora, minuto, segundo e milissegundo.
********************************/
void GetTempoTotalVideo(int idVideo, char *str){
    strcpy(str,CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoTotalString().c_str());
}

/********************************
A fun��o GetTempoFrameVideo() � respons�vel por recuperar a dura��o esperada para cada frame do video (em milissegundo).
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
Retorno:
Dura��o esperado de cada frame do v�deo (em milissegundo).
********************************/
double GetTempoFrameVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoFrame();
}

/********************************
A fun��o GetFPSVideo() � respons�vel por recuperar a quantidade de frames do v�deo que deveriam ser exibidos a cada segundo.
Par�metro:
idVideo (entrada, passagem por valor): indentificador do v�deo.
Retorno:
Quantidade desejada de frames a cada segundo.
********************************/
double GetFPSVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetFPS();
}

/********************************
A fun��o SetAnguloVideo() � respons�vel pela angula��o de determinado v�deo. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O v�deo ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaVideo().
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
angulo (entrada, passagem por valor): valor para indicar a angula��o do v�deo em graus.
********************************/
void SetAnguloVideo(int idVideo, float angulo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetAngulo(angulo);
}

/********************************
A fun��o GetAnguloVideo() � respons�vel por recuperar o �ngulo de rota��o de determinado v�deo. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O v�deo ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaVideo().
idVideo (entrada, passagem por valor): identificador do v�deo.
Retorno:
Retorna o valor do �ngulo em graus.
********************************/
double GetAnguloVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetAngulo();
}

/********************************
A fun��o SetFlipVideo() � respons�vel por virar o v�deo, invertendo-o em alguma dire��o. O v�deo somente ser�
desenhado na nova orienta��o no pr�ximo comando DesenhaVideo().
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de invers�o),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipVideo(int idVideo, PIG_Flip valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetFlip(valor);
}

/********************************
A fun��o GetFlipVideo() � respons�vel por recuperar o valor da manipula��o causada pela fun��o SetFlipVideo().
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser PIG_FLIP_NENHUM (nenhum tipo de invers�o),
PIG_FLIP_HORIZONTAL (inverte da esquerda para a direita), PIG_FLIP_VERTICAL (inverte de cima para baixo),
ou PIG_FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetFlip();
}

/********************************
A fun��o SetPivoAbsolutoVideo() define um ponto (X,Y) em rela��o ao ponto (0,0) do v�deo, sobre o qual o video ser�
rotacionado quando a fun��o SetAnguloVideo() for executada.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do v�deo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do v�deo.
********************************/
void SetPivoAbsolutoVideo(int idVideo, int posicaoX,int posicaoY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetPivoAbsoluto({posicaoX,posicaoY});
}

/********************************
A fun��o SetPivoProporcionalVideo() define um ponto relativo (X,Y) em rela��o ao video (0,0) e ao tamanho do v�deo, sobre o qual o v�deo ser�
rotacionado quando a fun��o SetAnguloVideo() for executada.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
relX (entrada, passagem por valor): porcentagem da largura do v�deo onde ficar� o piv�.
relY (entrada, passagem por valor): porcentagem da altura do v�deo onde ficar� o piv�.
********************************/
void SetPivoProporcionalVideo(int idVideo, float relX,float relY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetPivoProporcional({relX,relY});
}

/********************************
A fun��o GetPivoVideo() define um ponto (X,Y) em rela��o ao ponto (0,0) do v�deo, sobre o qual o v�deo ser�
rotacionado quando a fun��o SetAnguloVideo() for executada.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
posicaoX (sa�da, passagem por refer�ncia): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do v�deo.
posicaoY (sa�da, passagem por refer�ncia): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do v�deo.
********************************/
void GetPivoVideo(int idVideo, int *posicaoX,int *posicaoY){
    PIGPonto2D p = CPIGGerenciadorVideos::GetVideo(idVideo)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

/********************************
A fun��o MoveVideo() � respons�vel por movimentar um determinado v�deo para uma nova posi��o informada.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja reposicionar o v�deo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja reposicionar o v�deo.
********************************/
void MoveVideo(int idVideo,int posicaoX,int posicaoY){
    CPIGGerenciadorVideos::GetVideo(idVideo)->Move(posicaoX,posicaoY);
}

/********************************
A fun��o SetDimensoesVideo() � respons�vel por delimitar a altura e a largura do v�deo que ser� desenhado na tela,
independentemente do tamanho original do arquivo.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesVideo(int idVideo, int altura,int largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetDimensoes(altura,largura);
}

/********************************
A fun��o GetDimensoesVideo() � respons�vel por recuperar a altura e a largura da �rea a ser usada
para desenhar o v�deo na tela. Em outras palavras, representa o tamanho atual do v�deo.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
altura (sa�da, passagem por refer�ncia): altura atual em pixels do v�deo.
largura (sa�da, passagem por refer�ncia): largura atual em pixels do v�deo.
********************************/
void GetDimensoesVideo(int idVideo, int *altura, int *largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->GetDimensoes(*altura,*largura);
}

/********************************
A fun��o GetDimensoesOriginaisVideo() � respons�vel por recuperar a altura e a largura originais dos frames do v�deo.
Qualquer utiliza��o da fun��o SetDimensoesVideo() � ignorada para o c�lculo desta fun��o.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
altura (sa�da, passagem por refer�ncia): altura original em pixels do v�deo.
largura (sa�da, passagem por refer�ncia): largura original em pixels do v�deo.
********************************/
void GetDimensoesOriginaisVideo(int idVideo, int *altura, int *largura){
    CPIGGerenciadorVideos::GetVideo(idVideo)->GetResolucao(*altura,*largura);
}

/********************************
A fun��o OcupaJanelaInteiraVideo() � respons�vel por redimensionar a exibi��o do video, para que este ocupe todo o tamanho
da janela em que estiver sendo executado.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo a ser desenhado.
********************************/
void OcupaJanelaInteiraVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->OcupaJanelaInteira();
}

/********************************
A fun��o UsaResolucaoOriginalVideo() � respons�vel por redimensionar a exibi��o do video, para que este utilize a resolu��o original
do arquivo de m�dia.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo a ser desenhado.
********************************/
void UsaResolucaoOriginalVideo(int idVideo){
    CPIGGerenciadorVideos::GetVideo(idVideo)->UsaResolucaoOriginal();
}

/********************************
A fun��o SetColoracaoVideo() � respons�vel por mesclar uma determinada cor com os pixels do frame do v�deo.
Ap�s a modifica��o, todos os desenhos deste v�deo ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de v�deo.
********************************/
void SetColoracaoVideo(int idVideo, PIG_Cor cor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetColoracao(cor);
}

/********************************
A fun��o SetOpacidadeVideo() � respons�vel por modificar o n�vel de opacidade do v�deo.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
valor (entrada,passagem por valor): n�vel de opacidade do v�deo na faixa 0-255.
********************************/
void SetOpacidadeVideo(int idVideo, int valor){
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetOpacidade(valor);
}

/********************************
A fun��o GetOpacidadeVideo() � respons�vel por recuperar o n�vel de opacidade de determinado v�deo.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
idVideo (entrada, passagem por valor): identificador do v�deo.
Retorno:
Retorna o n�vel de opacidade do v�deo na faixa 0-255.
********************************/
int GetOpacidadeVideo(int idVideo){
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetOpacidade();
}

#endif

/*******FORM*********/

int PIG_CriaForm(int xForm, int yForm, int altForm, int largForm,int janela = 0){
    return CPIGGerenciadorForms::CriaForm(xForm,yForm,altForm,largForm,janela);
}

int PIG_Form_TrataEvento(int idForm,PIG_Evento evento){
    return CPIGGerenciadorForms::GetForm(idForm)->TrataEvento(evento);
}

int PIG_Form_Desenha(int idForm){
    return CPIGGerenciadorForms::GetForm(idForm)->Desenha();
}

/*******COMPONENTES*********/

int PIG_CriaComponentePorArquivo(int idForm,tipos_Componentes componente,char* nomeArquivo){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaComponentePorArquivo(componente,nomeArquivo);//CPIGGerenciadorForms::CriaComponentePorArquivo(idForm,componente,nomeArquivo);
}

void PIG_Componentes_SetLabel(int idComponente,char* novoLabel){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetLabel(novoLabel);
}

void PIG_Componentes_SetFonteLabel(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetFonteLabel(fonte);
}

void PIG_Componentes_SetCorLabel(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetCorLabel(cor);
}

void PIG_Componentes_SetFonteHint(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetFonteHint(fonte);
}

void PIG_Componentes_SetCorHint(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetCorHint(cor);
}

void PIG_Componentes_SetAudio(int idComponente,int idAudio){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetAudio(idAudio);
}

void PIG_Componentes_GetLabel(int idComponente,char *label){
    strcpy(label,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetLabel()).c_str());
}

void PIG_Componentes_SetHint(int idComponente,char *hint){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetHint(hint);
}

void PIG_Componentes_Move(int idComponente,int x,int y){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->Move(x,y);
}

void PIG_Componentes_SetDimensoes(int idComponente,int altura,int largura){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetDimensoes(altura,largura);
}

void PIG_Componentes_SetPosicaoPadraoLabel(int idComponente,PIG_PosicaoComponente pos){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetPosicaoPadraoLabel(pos);
}

void PIG_Componentes_SetPosicaoPersonalizadaLabel(int idComponente,int x,int y){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetPosicaoPersonalizadaLabel(x,y);
}

void PIG_Componentes_SetPosPadraoExternaComponente(int idComponente,PIG_PosicaoComponente pos,CPIGComponente *componenteAssociado){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetPosPadraoExternaComponente(pos,componenteAssociado);
}

void PIG_Componentes_SetPosPadraoComponenteNaTela(int idComponente,PIG_Ancora pos){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetPosPadraoComponenteNaTela(pos);
}

void PIG_Componentes_SetHabilitado(int idComponente,int valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetHabilitado(valor);
}

void PIG_Componentes_SetVisivel(int idComponente,int valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->SetVisivel(valor);
}

PIG_Cor PIG_Componentes_GetCorLabel(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetCorLabel();
}

void PIG_Componentes_GetHint(int idComponente,char* hint){
    strcpy(hint,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetHint()).c_str());
}

int PIG_Componentes_GetFonteHint(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetFonteHint();
}

int PIG_Componentes_GetVisivel(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetVisivel();
}

int PIG_Componentes_GetHabilitado(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetHabilitado();
}

int PIG_Componentes_GetAcionado(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetAcionado();
}

int PIG_Componentes_GetMouseOver(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetMouseOver();
}

PIG_PosicaoComponente PIG_Componentes_GetPosComponente(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetPosComponente();
}

void PIG_Componentes_GetDimensoes(int idComponente,int &altura, int &largura){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetDimensoes(altura,largura);
}

void PIG_Componentes_GetDimensoesOriginais(int idComponente,int &altura, int &largura){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente(idComponente)->GetDimensoesOriginais(altura,largura);
}

/*******BOTAO*********/

int PIG_CriaBotao(int idForm,int x,int y,int alt,int larg,char* nomeArq,int retiraFundo = 1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotao(x,y,alt,larg,nomeArq,retiraFundo);
}

void PIG_Botao_DefineAcao(int idComponente,PIG_FuncaoSimples funcao,void *parametro){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGBotao>(idComponente)->DefineAcao(funcao,parametro);
}

void PIG_Botao_DefineAtalho(int idComponente,int teclaAtalho){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGBotao>(idComponente)->DefineAtalho(teclaAtalho);
}

void PIG_Botao_DefineTempoRepeticao(int idComponente,double segundos){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGBotao>(idComponente)->DefineTempoRepeticao(segundos);
}

void PIG_Botao_DefineBotaoRepeticao(int idComponente,bool repeticao){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGBotao>(idComponente)->DefineBotaoRepeticao(repeticao);
}

/*******AREADETEXTO*********/

int PIG_CriaAreaDeTexto(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200,int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaAreaDeTexto(x,y,altura,largura,nomeArq,maxCars,retiraFundo);
}

void PIG_AreaDeTexto_SetScrollBarVertical(int idComponente,int larguraTotal,int comprimentoTotal,int larguraHandle,char* imgHandle,char* imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetScrollBarVertical(larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha);
}

void PIG_AreaDeTexto_SetScrollBarHorizontal(int idComponente,int larguraTotal,int comprimentoTotal,int larguraHandle,char* imgHandle,char* imgTrilha,int retiraFundoHandle=1,int retiraFundoTrilha=1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetScrollBarHorizontal(larguraTotal,comprimentoTotal,larguraHandle,imgHandle,imgTrilha,retiraFundoHandle,retiraFundoTrilha);
}

void PIG_AreaDeTexto_SetBotoesScrollBarVertical(int idComponente,int larguraBotoes,char* imgBotao1,char* imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetBotoesScrollBarVertical(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
}

void PIG_AreaDeTexto_SetBotoesScrollBarHorizontal(int idComponente,int larguraBotoes,char* imgBotao1,char* imgBotao2,int retiraFundoB1 = 1,int retiraFundoB2 = 1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetBotoesScrollBarHorizontal(larguraBotoes,imgBotao1,imgBotao2,retiraFundoB1,retiraFundoB2);
}

void PIG_AreaDeTexto_SetPosPadraoScrollHorizontal(int idComponente,PIG_PosicaoComponente pos){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetPosPadraoScrollHorizontal(pos);
}

void PIG_AreaDeTexto_SetPosPadraoScrollVertical(int idComponente,PIG_PosicaoComponente pos){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetPosPadraoScrollVertical(pos);
}

void PIG_AreaDeTexto_MoveScrollBarHorizontal(int idComponente,int x,int y){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->MoveScrollBarHorizontal(x,y);
}

void PIG_AreaDeTexto_MoveScrollBarVertical(int idComponente,int x,int y){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->MoveScrollBarVertical(x,y);
}

void PIG_AreaDeTexto_SetFonteTexto(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetFonteTexto(fonte);
}

void PIG_AreaDeTexto_SetLinhasAbaixoTexto(int idComponente,bool visivel,PIG_Cor cor = PRETO){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetLinhasAbaixoTexto(visivel,cor);
}

void PIG_AreaDeTexto_SetLargMaxTexto(int idComponente,int largMaxTexto){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetLargMaxTexto(largMaxTexto);
}

void PIG_AreaDeTexto_SetEspacoEntreAsLinhas(int idComponente,int espaco){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetEspacoEntreAsLinhas(espaco);
}

void PIG_AreaDeTexto_SetTexto(int idComponente,char* frase){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetTexto(frase);
}

void PIG_AreaDeTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_AreaDeTexto_SetCorCursor(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->SetCorCursor(cor);
}

vector<string> PIG_AreaDeTexto_GetLinhasTexto(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->GetLinhasTexto();
}

void PIG_AreaDeTexto_GetTexto(int idComponente,char* texto){
    strcpy(texto,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGAreaDeTexto>(idComponente)->GetTexto()).c_str());
}

/**********CAMPOTEXTO**************/

int PIG_CriaCampoTexto(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,false);
}

void PIG_CampoTexto_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_CampoTexto_SetTexto(int idComponente,char* frase){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetTexto(frase);
}

void PIG_CampoTexto_SetFonteTexto(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetFonteTexto(fonte);
}

void PIG_CampoTexto_SetCorCursor(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorCursor(cor);
}

void PIG_CampoTexto_GetTexto(int idComponente,char* texto){
    strcpy(texto,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->GetTexto()).c_str());
}

/**********CAMPOSENHA**************/

int PIG_CriaCampoSenha(int idForm,int x, int y, int altura,int largura,char* nomeArq,int maxCars = 200, bool apenasNumeros=false, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(x,y,altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,true);
}

void PIG_CampoSenha_SetMargens(int idComponente,int horEsq,int horDir, int vertBaixo,int vertCima){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetMargens(horEsq,horDir,vertBaixo,vertCima);
}

void PIG_CampoSenha_SetTexto(int idComponente,char* frase){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetTexto(frase);
}

void PIG_CampoSenha_SetFonteTexto(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetFonteTexto(fonte);
}

void PIG_CampoSenha_SetCorCursor(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorCursor(cor);
}

/**********LISTA**************/

int PIG_CriaListBox(int idForm,int x, int y,int larguraTotal,int alturaLinha,int alturaMaxima,int alturaItem,int largItem,char* nomeArq,int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaListBox(x,y,larguraTotal,alturaLinha,alturaMaxima,alturaItem,largItem,nomeArq,retiraFundo);
}

void PIG_ListBox_CriaItem(int idComponente,char* texto,char* imagemIcone = "",char *imagemFundo="",char* hintMsg="",bool itemHabilitado = true, int audio=-1,int retiraFundoImg = 1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->CriaItem(texto,imagemIcone,imagemFundo,false,itemHabilitado,audio,hintMsg,retiraFundoImg);
}

int PIG_ListBox_SetAcionado(int idComponente,int indice, int marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetAcionado(indice,marcado);
}

void PIG_ListBox_DefineDimensaoIconeItem(int idComponente,int alturaImagemIcone, int larguraImagemIcone){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->DefineDimensaoIconeItem(alturaImagemIcone,larguraImagemIcone);
}

void PIG_ListBox_AlinhaLabelDireita(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaLabelDireita();
}

void PIG_ListBox_AlinhaLabelEsquerda(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaLabelEsquerda();
}

void PIG_ListBox_AlinhaLabelCentro(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaLabelCentro();
}

void PIG_ListBox_AlinhaIconeDireita(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaIconeDireita();
}

void PIG_ListBox_AlinhaIconeEsquerda(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->AlinhaIconeEsquerda();
}

void PIG_ListBox_SetFonteItensLista(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetFonteItensLista(fonte);
}

int PIG_ListBox_GetAcionadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->GetAcionadoItem(item);
}

int PIG_ListBox_SetAudioItem(int idComponente,int item, int audio){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetAudioItem(item,audio);
}

int PIG_ListBox_GetHabilitadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->GetHabilitadoItem(item);
}

int PIG_ListBox_SetHabilitadoItem(int idComponente,int item,int valor){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetHabilitadoItem(item,valor);
}

int PIG_ListBox_GetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->GetItemDestaque();
}

int PIG_ListBox_SetAcionadoItem(int idComponente,int indice,int marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGListBox>(idComponente)->SetAcionadoItem(indice,marcado);
}
/**********DROPDOWN**************/

int PIG_CriaDropDown(int idForm,int x, int y, int larguraTotal,int alturaLinha,int alturaMaxima,int alturaItem,int larguraItem,char* nomeArq,int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaDropDown(x,y,larguraTotal,alturaLinha,alturaMaxima,alturaItem,larguraItem,nomeArq,retiraFundo);
}

void PIG_DropDown_CriaItem(int idComponente,char* texto,char* imagemIcone = "",char *imagemFundo="", char* hintMsg="",bool itemHabilitado = true, int audio=-1,int retiraFundoImg = 1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->CriaItem(texto,imagemIcone,imagemFundo,itemHabilitado,audio,hintMsg,retiraFundoImg);
}

void PIG_DropDown_DefineDimensaoIconeItem(int idComponente,int alturaImagemIcone, int larguraImagemIcone){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->DefineDimensaoIconeItem(alturaImagemIcone,larguraImagemIcone);
}

void PIG_DropDown_AlinhaLabelDireita(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaLabelDireita();
}

void PIG_DropDown_AlinhaLabelEsquerda(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaLabelEsquerda();
}

void PIG_DropDown_AlinhaLabelCentro(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaLabelCentro();
}

void PIG_DropDown_AlinhaIconeDireita(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaIconeDireita();
}

void PIG_DropDown_AlinhaIconeEsquerda(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->AlinhaIconeEsquerda();
}

void PIG_DropDown_SetFonteItensLista(int idComponente,int fonte){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetFonteItensLista(fonte);
}

int PIG_DropDown_GetAcionadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->GetAcionadoItem(item);
}

int PIG_DropDown_SetAudioItem(int idComponente,int item, int audio){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetAudioItem(item,audio);
}

int PIG_DropDown_GetHabilitadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->GetHabilitadoItem(item);
}

int PIG_DropDown_SetHabilitadoItem(int idComponente,int item,int valor){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetHabilitadoItem(item,valor);
}

int PIG_DropDown_GetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->GetItemDestaque();
}

int PIG_DropDown_SetAcionadoItem(int idComponente,int indice,int marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGDropDown>(idComponente)->SetAcionadoItem(indice,marcado);
}

/**********GAUGE**************/

int PIG_CriaGauge(int idForm,int x, int y,int altura,int largura,char* imgGauge,int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGauge(x,y,altura,largura,imgGauge,retiraFundo);
}

void PIG_Gauge_SetFrames(int idComponente,SDL_Rect fBase,SDL_Rect fBarra){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->SetFrames(fBase,fBarra);
}

void PIG_Gauge_SetDelta(int idComponente,float valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->SetDelta(valor);
}

void PIG_Gauge_AvancaDelta(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->AvancaDelta();
}

float PIG_Gauge_GetPorcentagemConcluida(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->GetPorcentagemConcluida();
}

void PIG_Gauge_ZeraValor(int idComponente){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->ZeraValor();
}

void PIG_Gauge_SetValorMinMax(int idComponente,int minimo,int maximo){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->SetValorMinMax(minimo,maximo);
}

void PIG_Gauge_AvancaBarra(int idComponente,float valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->AvancaBarra(valor);
}

void PIG_Gauge_SetDistanciaXYBarra(int idComponente,int dx,int dy){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->SetDistanciaXYBarra(dx,dy);
}

void PIG_Gauge_SetPorcentagemConcluida(int idComponente,float porcentagem){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->SetPorcentagemConcluida(porcentagem);
}

void PIG_Gauge_SetOrientacaoBarra(int idComponente,PIG_GaugeCrescimentoBarra orientacao){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->SetOrientacaoBarra(orientacao);
}

float PIG_Gauge_GetValorBarraAtual(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->GetValorBarraAtual();
}

void PIG_Gauge_SetValorBarraAtual(int idComponente,float valor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGauge>(idComponente)->SetValorBarraAtual(valor);
}

/**********GAUGECIRCULAR**************/

int PIG_CriaGaugeCircular(int idForm,int x, int y,int altura,int largura,int raioInterior,char* imgGauge,int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeCircular(x,y,altura,largura,raioInterior,imgGauge,retiraFundo);
}

void PIG_GaugeCircular_SetRaioInterno(int idComponente,int valorRaio){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetRaioInterno(valorRaio);
}

void PIG_GaugeCircular_SetAnguloBase(int idComponente,double novoAng){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetAnguloBase(novoAng);
}

void PIG_GaugeCircular_SetDeltaAngulo(int idComponente,double novoDelta){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetDeltaAngulo(novoDelta);
}

void PIG_GaugeCircular_IncrementaValor(int idComponente,int delta){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->IncrementaValor(delta);
}

void PIG_GaugeCircular_SetValorMax(int idComponente,int novoValor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetValorMax(novoValor);
}

void PIG_GaugeCircular_SetValorMin(int idComponente,int novoValor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetValorMin(novoValor);
}

void PIG_GaugeCircular_SetCorInicial(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetCorInicial(cor);
}

void PIG_GaugeCircular_SetCorFinal(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetCorFinal(cor);
}

void PIG_GaugeCircular_SetCorFundo(int idComponente,PIG_Cor cor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->SetCorFundo(cor);
}

int PIG_GaugeCircular_GetValor(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetValor();
}

void PIG_GaugeCircular_GetValorString(int idComponente,char* valor){
    strcpy(valor,(char*)(CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetValorString()).c_str());
}

int PIG_GaugeCircular_GetValorMax(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetValorMax();
}

int PIG_GaugeCircular_GetValorMin(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->GetValorMin();
}

void PIG_GaugeCircular_AtualizaValor(int idComponente,int novoValor){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGGaugeCircular>(idComponente)->AtualizaValor(novoValor);
}

/**********RADIOBOX**************/

int PIG_CriaRadioBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, int alturaMaxima,char* imagemItem, int alturaItem, int larguraItem,char* imagemFundo, int retiraFundo=1){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaRadioBox(x,y,larguraTotal,alturaLinha,alturaMaxima,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
}

void PIG_RadioBox_CriaItem(int idComponente,char* itemLabel, char *imagemFundo="", char* hintMsg="", bool itemHabilitado = true, int audio=-1, int retiraFundo=1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->CriaItem(itemLabel,imagemFundo,itemHabilitado,audio,hintMsg,retiraFundo);
}

int PIG_RadioBox_GetItemDestaque(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->GetItemDestaque();
}

int PIG_RadioBox_SetItemMarcado(int idComponente,int item, bool marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetAcionadoItem(item,marcado);
}

int PIG_RadioBox_GetEstadoMarcadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->GetAcionadoItem(item);
}

int PIG_RadioBox_SetAudioItem(int idComponente,int item,int audio){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetAudioItem(item,audio);
}

int PIG_RadioBox_GetEstadoHabilitadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->GetHabilitadoItem(item);
}

int PIG_RadioBox_SetEstadoHabilitadoItem(int idComponente,int item,bool habilitado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetHabilitadoItem(item,habilitado);
}

void PIG_RadioBox_SetEstadoHabilitadoItens(int idComponente,bool habilitado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGRadioBox>(idComponente)->SetHabilitado(habilitado);
}

/**********CHECKBOX**************/

int PIG_CriaCheckBox(int idForm,int x, int y,int larguraTotal,int alturaLinha, int alturaMaxima,char* imagemItem, int alturaItem, int larguraItem,char* imagemFundo, int retiraFundo=1, int idJanela=0){
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCheckBox(x,y,larguraTotal,alturaLinha,alturaMaxima,imagemItem,alturaItem,larguraItem,imagemFundo,retiraFundo);
}

void PIG_CheckBox_CriaItem(int idComponente,char* itemLabel,char *imagemFundo="",char* hintMsg="",bool itemMarcado = false, bool itemHabilitado = true, int audio=-1,  int retiraFundo=1){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->CriaItem(itemLabel,imagemFundo,itemMarcado,itemHabilitado,audio,hintMsg,retiraFundo);
}

void PIG_CheckBox_SetMarcadoTodos(int idComponente,bool marcado){
    CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetAcionadoTodos(marcado);
}

int PIG_CheckBox_SetMarcadoItem(int idComponente,int indice,bool marcado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetAcionadoItem(indice,marcado);
}

std::vector <int> PIG_CheckBox_GetItensMarcados(int idComponente){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->GetItensMarcados();
}

int PIG_CheckBox_GetMarcadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->GetAcionadoItem(item);
}

int PIG_CheckBox_SetAudioItem(int idComponente,int item,int audio){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetAudioItem(item,audio);
}

int PIG_CheckBox_GetHabilitadoItem(int idComponente,int item){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->GetHabilitadoItem(item);
}

int PIG_CheckBox_SetHabilitadoItem(int idComponente,int item,bool habilitado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetHabilitadoItem(item,habilitado);
}

void PIG_CheckBox_SetHabilitado(int idComponente,bool habilitado){
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetComponente<PIGCheckBox>(idComponente)->SetHabilitado(habilitado);
}

/********************************/
