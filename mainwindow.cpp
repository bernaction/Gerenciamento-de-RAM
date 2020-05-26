#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QString>
using namespace std;

struct RAM {
    int conteudo;
    int tamanhoProcesso;
    int temp_proc;
};
int TamMax=1024;
int n_proc=0; // indice do numero do processo;
int temp_total;
RAM memoria[1024]; // vetor da memoria ram;

void clearMem(RAM memoria[], int i){
    for (int j=0; j<memoria[i].tamanhoProcesso; j++){
        memoria[i].conteudo = -1;
    }
}

void firstFit(RAM memoria[]){
    bool cabe;
    for (int i=0; i<TamMax; i++){
        if(memoria[i].conteudo == -1){ //ta livre
            for (int j=0; j<memoria[i].tamanhoProcesso; j++){
                if (memoria[i+j].conteudo != -1){
                    cabe = false;
                    break;
                } else {
                    cabe = true;
                }
                if(cabe == true){
                    for (int j=0; j<memoria[i].tamanhoProcesso; j++){
                        memoria[i].conteudo = j;
                    }
                }
            }
        }
    }
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->label_processo_numero->setText(QString::number(n_proc));
    for (int i=0; i<TamMax; i++){                // laço para inicializar memoria em -1
        memoria[i].conteudo = -1;                // -1 = memoria vazia
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_add_clicked() {
    if (ui->radioButton_ff->isChecked()){
        memoria[n_proc].tamanhoProcesso = ui->lineEdit_tamanho_processo->text().toInt();
        firstFit(memoria);
        ui->label_processo_numero->setText(QString::number(n_proc));
        memoria[n_proc].temp_proc = ui->lineEdit_tempo_processo->text().toInt();
        ui->comboBox_processo->addItem("PID " + QString::number(n_proc));
        n_proc++;

    } else if (ui->radioButton_bf->isChecked()) {
        QMessageBox::about(this, "Simulador MEM", "Opção invalida nesta versão\nAguarde update");
        n_proc++;
        //
    }
        else if (ui->radioButton_wf->isChecked()) {
        QMessageBox::about(this, "Simulador MEM", "Opção invalida nesta versão\nAguarde update");
        n_proc++;
        //
    }
    else {
        QMessageBox::about(this, "Simulador MEM", "Selecione uma alocação");
    }
}

void MainWindow::on_pushButton_avancar_clicked() {
    if (ui->comboBox_processo->currentText() != NULL) {
        for (int i=0; i<n_proc; i++) {
            if(memoria[i].temp_proc <= 0){
                ui->comboBox_processo->removeItem(i);
                clearMem(memoria, i);
                //n_proc--;
            }
            if (memoria[i].temp_proc>0){
               memoria[i].temp_proc--;
            }
        }
        ui->label_tamanho_processo->setText(QString::number(memoria[ui->comboBox_processo->currentIndex()].tamanhoProcesso));
        ui->label_tempo_processo->setText(QString::number(memoria[ui->comboBox_processo->currentIndex()].temp_proc));
        temp_total++;
    }
}


void MainWindow::on_comboBox_processo_currentIndexChanged(const QString &a) {
    ui->label_tamanho_processo->setText(QString::number(memoria[ui->comboBox_processo->currentIndex()].tamanhoProcesso));
    ui->label_tempo_processo->setText(QString::number(memoria[ui->comboBox_processo->currentIndex()].temp_proc));
}
