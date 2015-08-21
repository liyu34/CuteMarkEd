#ifndef GITBLOG_H
#define GITBLOG_H

#include <QDialog>
#include <QString>
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
    Ui::GitBlog *ui;
    QString ref;
private slots:
    void GetData();
};

#endif // GITBLOG_H
