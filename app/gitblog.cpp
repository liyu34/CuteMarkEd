#include "gitblog.h"
#include "ui_gitblog.h"

GitBlog::GitBlog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GitBlog)
{
    ui->setupUi(this);
    connect(ui->OkButton,SIGNAL(pressed()),this,SLOT(GetData()));
    ui->dateEdit->setDate(QDate::currentDate());
    ui->statusCombo->addItem("publish");
    ui->categoryCombo->addItem("GitBlog");
}

GitBlog::~GitBlog()
{
    delete ui;
}

void GitBlog::GetData()
{
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
    date = ui->dateEdit->date().toString("yyyy-mm-dd");

    category = ui->categoryCombo->currentText();
    status = ui->statusCombo->currentText();
}
