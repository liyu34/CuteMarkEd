#ifndef GITBLOG_H
#define GITBLOG_H

#include <QDialog>
#include <QString>
#include <mytextedit.h>
#include "addcategorydialog.h"
namespace Ui {
class GitBlog;
}

class GitBlog : public QDialog
{
    Q_OBJECT

public:
    explicit GitBlog(QWidget *parent = 0);
    ~GitBlog();
private:
    void InitCategory();

private:
    Ui::GitBlog *ui;
    AddCategoryDialog *acd;
    QString ref;
private slots:
    void GetData();
    void AddCategory(QString cate);
    void ShowACDialog();
signals:
    void SendSettings(QString settings);
};

#endif // GITBLOG_H
