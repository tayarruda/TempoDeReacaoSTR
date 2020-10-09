#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <stdlib.h>

time_t tempo_inicial = 101, tempo_clique;
int score = 0;
int i = 0;
int somaTempo = 0;
int mediaTempo = 0;
int escolherPosicaoBotoes;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    time(&tempo_inicial);//inicia contagem
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mudarPosicaoCirculo(){
//tempo_inicial-tempo_clique < 100
    if(score > 0){

        if(i>0 && score <= 10){
            ui->textBrowser->setText("Tempo de resposta: " + QString::number(tempo_clique-tempo_inicial) + " segundos");
            somaTempo = somaTempo + (tempo_clique-tempo_inicial);
            mediaTempo = somaTempo/i;
            ui->textBrowserAvg->setText(QString::number(mediaTempo)+"s");
        }else if(i == 0 && score < 10){
            ui->textBrowser->setText("ERROU");
            ui->textBrowserAvg->setText("");
        }
    }


    ui->textBrowserScore->setText(QString::number(score));

    ui->widget->repaint();
    time(&tempo_inicial);//redesenhou

}

void MainWindow::clicouBotao()
{

    time(&tempo_clique);//clicou no botao


    if(!(clicouAzulECirculoAzul() && clicouVerdeECirculoVerde() && clicouVermelhoECirculoVermelho())){
        score--;
        somaTempo = 0;
        mediaTempo = 0;
        i = 0;
    }else{
        score++;
        i++;
    }

    if(score <= 0){
        resetarJogo();
        desabilitarBotoes();
        ui->textBrowser->setText("Você Perdeu!");
    }

    if(score == 10){
        ui->textBrowser->setText("Você Venceu!!!Parabéns");
        //ui->textBrowserScore->setText(QString("WINNER"));
        desabilitarBotoes();
        //score = 0;
        mediaTempo =0;
        somaTempo=0;
        i = 0;
    }

    mudarPosicaoBotoes();
    mudarPosicaoCirculo();
}

void MainWindow::mudarPosicaoBotoes()
{

    escolherPosicaoBotoes = rand()%3 + 1;
    QPalette palVermelha = ui->botao1->palette();
    QPalette palVerde = ui->botao2->palette();
    QPalette palAzul = ui->botao3->palette();

    palVermelha.setColor(QPalette::Button, QColor(Qt::red));
    palVerde.setColor(QPalette::Button, QColor(Qt::green));
    palAzul.setColor(QPalette::Button, QColor(Qt::blue));

    switch (escolherPosicaoBotoes) {
    case 1:
        ui->botao1->setText("Azul");
        ui->botao1->setPalette(palVermelha);

        ui->botao2->setText("Vermelho");
        ui->botao2->setPalette(palVerde);

        ui->botao3->setText("Verde");
        ui->botao3->setPalette(palVermelha);

        break;
    case 2:
        ui->botao1->setText("Verde");
        ui->botao1->setPalette(palAzul);

        ui->botao2->setText("Azul");
        ui->botao2->setPalette(palVermelha);

        ui->botao3->setText("Vermelho");
        ui->botao3->setPalette(palVerde);
        break;
    case 3:
        ui->botao1->setText("Vermelho");
        ui->botao1->setPalette(palVerde);

        ui->botao2->setText("Verde");
        ui->botao2->setPalette(palAzul);

        ui->botao3->setText("Azul");
        ui->botao3->setPalette(palVermelha);

        break;
    default:
        ui->botao1->setText("Azul");
        ui->botao2->setPalette(palVerde);

        ui->botao2->setText("Vermelho");
        ui->botao2->setPalette(palAzul);

        ui->botao3->setText("Verde");
        ui->botao2->setPalette(palVermelha);

    }

    ui->botao1->update();
    ui->botao2->update();
    ui->botao3->update();
}

bool MainWindow::clicouVermelhoECirculoVermelho()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if((buttonSender->text() != QString("Vermelho"))){
            return true;
    }
    return (ui->widget->valorCorMostrada() == 1);
}

bool MainWindow::clicouVerdeECirculoVerde()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if((buttonSender->text() != QString("Verde"))){
            return true;
    }
    return (ui->widget->valorCorMostrada() == 2);

}

bool MainWindow::clicouAzulECirculoAzul()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if((buttonSender->text() != QString("Azul"))){
            return true;
    }
    return (ui->widget->valorCorMostrada() == 3);

}

void MainWindow::desabilitarBotoes()
{
    ui->botao1->setDisabled(true);
    ui->botao2->setDisabled(true);
    ui->botao3->setDisabled(true);
}


void MainWindow::resetarJogo()
{
    time(&tempo_inicial);
    ui->textBrowser->setText("");
    ui->textBrowserScore->setText("");
    ui->textBrowserAvg->setText("");
    score = 0;
    mediaTempo =0;
    somaTempo=0;
    i = 0;
    ui->botao1->setDisabled(false);
    ui->botao2->setDisabled(false);
    ui->botao3->setDisabled(false);


}


