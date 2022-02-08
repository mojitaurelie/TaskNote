#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::createNote);
    connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::removeSelected);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutBox);
    connect(ui->noteList, &QListWidget::currentRowChanged, this, &MainWindow::selectionChanged);
    connect(ui->titleEdit, &QLineEdit::textChanged, this, &MainWindow::titleChanged);
    connect(ui->contentEdit, &QPlainTextEdit::textChanged, this, &MainWindow::contentChanged);
    connect(ui->actionEncrypt, &QAction::triggered, this, &MainWindow::encryptNote);
    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    ui->contentEdit->setFont(fixedFont);
    this->savemng = new SaveManager();
    updateListView();
    connect(timer, &QTimer::timeout, this, &MainWindow::save);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete savemng;
    delete ui;
}

void MainWindow::createNote()
{
    Note *n = new Note();
    n->setTitle("untitled note");
    savemng->addNote(n);
    updateListView();
}

void MainWindow::selectionChanged(int i)
{
    this->currentIndex = i;
    if (i == -1)
    {
        clearAndDisableFields();
        return;
    }
    Note *n = this->savemng->getNoteByIndex(i);
    if (n == nullptr)
    {
        QMessageBox::critical(this, tr("TaskNote"), "Failed to get this note, the memory pointer is empty", QMessageBox::Ok, QMessageBox::Ok);
        clearAndDisableFields();
        return;
    }
    ui->actionRemove->setDisabled(false);
    ui->titleEdit->setDisabled(false);
    ui->contentEdit->setDisabled(false);
    ui->titleEdit->setText(n->getTitle());
    if (n->isEncrypted())
    {
      ui->contentEdit->setPlainText(n->getEncryptedContent("azertyuiop"));
    } else {
      ui->contentEdit->setPlainText(n->getContent());
    }
    ui->markdownViewer->setMarkdown(ui->contentEdit->toPlainText());
}

void MainWindow::removeSelected()
{
    if (this->currentIndex > -1)
    {
        this->savemng->removeNoteByIndex(this->currentIndex);
        clearAndDisableFields();
        updateListView();
    }
}

void MainWindow::save()
{
    ui->actionSave->setDisabled(true);
    if (this->currentIndex > -1)
    {
        Note *n = this->savemng->getNoteByIndex(this->currentIndex);
        n->setTitle(ui->titleEdit->text());
        n->setContent(ui->contentEdit->toPlainText());
    }
    this->savemng->flushSave();
}

void MainWindow::titleChanged()
{
    timer->stop();
    if (this->currentIndex > -1)
    {
        Note *n = this->savemng->getNoteByIndex(this->currentIndex);
        n->setTitle(ui->titleEdit->text());
        ui->noteList->item(this->currentIndex)->setText(ui->titleEdit->text());
    }
    ui->actionSave->setDisabled(false);
    timer->start(1000);
}

void MainWindow::showAboutBox()
{
    AboutDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::encryptNote()
{
  if (this->currentIndex > -1)
  {
      Note *n = this->savemng->getNoteByIndex(this->currentIndex);
      n->encrypt("azertyuiop");
      savemng->flushSave();
  }
}

void MainWindow::contentChanged()
{
    timer->stop();
    if (this->currentIndex > -1)
    {
        Note *n = this->savemng->getNoteByIndex(this->currentIndex);
        n->setContent(ui->contentEdit->toPlainText());
        ui->markdownViewer->setMarkdown(ui->contentEdit->toPlainText());
    }
    ui->actionSave->setDisabled(false);
    timer->start(1000);
}

void MainWindow::updateListView()
{
    ui->noteList->clear();
    foreach (Note *n, savemng->getNotes())
    {
        ui->noteList->addItem(n->getTitle());
    }
}

void MainWindow::clearAndDisableFields()
{
    this->currentIndex = -1;
    ui->actionRemove->setDisabled(true);
    ui->titleEdit->setDisabled(true);
    ui->contentEdit->setDisabled(true);
    ui->titleEdit->clear();
    ui->contentEdit->clear();
    ui->markdownViewer->clear();
}

