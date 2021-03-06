#include "gitblog.h"
#include "ui_gitblog.h"
#include <QEvent>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
GitBlog::GitBlog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GitBlog)
{
    acd = NULL;
    ui->setupUi(this);
    connect(ui->OkButton,SIGNAL(pressed()),this,SLOT(GetData()));
    connect(ui->addCategory,SIGNAL(pressed()),this,SLOT(ShowACDialog()));


    InitCategory();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCurrentSectionIndex(2);
    ui->statusCombo->addItem("publish");
    ui->statusCombo->addItem("draft");
    ui->authorEdit->SetNext(ui->titleEdit);
    ui->titleEdit->SetNext(ui->tagsEdit);
    ui->tagsEdit->SetNext(ui->summaryEdit);
    ui->summaryEdit->SetNext(ui->authorEdit);
}

GitBlog::~GitBlog()
{
    delete ui;
}

void GitBlog::GetData()
{
    QString settings = "<!--\n";

    QString author;
    QString title;
    QString tags;
    QString category;
    QString status;
    QString summary;
    QString date;

    author = ui->authorEdit->document()->toPlainText();
    title = ui->titleEdit->document()->toPlainText();
    tags = ui->tagsEdit->document()->toPlainText();
    summary = ui->summaryEdit->document()->toPlainText();
    date = ui->dateEdit->date().toString("yyyy-MM-dd");

    category = ui->categoryCombo->currentText();
    status = ui->statusCombo->currentText();

    settings+="author:"+author+"\n";
    settings+="date:"+date+"\n";
    settings+="title:"+title+"\n";
    settings+="tags:"+tags+"\n";
    settings+="category:"+category+"\n";
    settings+="status:"+status+"\n";
    settings+="summary:"+summary+"\n";
    settings+="-->\n";

    emit SendSettings(settings);
}
void GitBlog::InitCategory()
{
    QFile file("categories.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL,"Error!","Can't open the file!");
    }
    QTextStream read(&file);
    QString line;
    line = read.readLine();
    line = line.trimmed();
    while(line!="")
    {
        ui->categoryCombo->addItem(line);
        line = read.readLine();
        line = line.trimmed();
    }
    file.close();
}

void GitBlog::AddCategory(QString cate)
{
    QFile file("categories.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::information(NULL,"Error!","Can't open the file!");
    }
    QTextStream write(&file);
    write.readAll();
    write << cate << endl;
    file.close();
    ui->categoryCombo->clear();
    InitCategory();
}

void GitBlog::ShowACDialog()
{
    acd = new AddCategoryDialog();
    acd->show();
    connect(acd,SIGNAL(CategoryName(QString)),this,SLOT(AddCategory(QString)));
}
