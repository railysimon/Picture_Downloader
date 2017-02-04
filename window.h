#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>

class Window : public QDialog
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
        QNetworkAccessManager *manger;
        void download(const QUrl&);
        void ShowPic(QString &name);

        QLineEdit *line;
        QPushButton *btn;
        QProgressBar *bar;

signals:
         void done(const QUrl&, const QByteArray&);
         void error();
         void progress(qint64, qint64);

private slots:
         void Finished(QNetworkReply*);
         void Go();
         void Progress(qint64, qint64);
         void slotDone(const QUrl&, const QByteArray&);
         void slotError();


};

#endif // WINDOW_H
