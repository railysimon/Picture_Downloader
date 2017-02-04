#include "window.h"

Window::Window(QWidget *parent): QDialog(parent)
{
    manger = new QNetworkAccessManager(this);
    connect(manger, SIGNAL(finished(QNetworkReply*)), this, SLOT(Finished(QNetworkReply*)));
    connect(this, SIGNAL(done(QUrl,QByteArray)), this, SLOT(slotDone(QUrl,QByteArray)));
    connect(this, SIGNAL(error()), this, SLOT(slotError()));
    connect(this, SIGNAL(progress(qint64,qint64)), this, SLOT(Progress(qint64,qint64)));

    line = new QLineEdit;
    btn = new QPushButton("OK");
    bar = new QProgressBar;
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(Go()));

    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(line);
    lay->addWidget(btn);
    lay->addWidget(bar);
    this->setLayout(lay);
}

Window::~Window()
{

}

void Window::download(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manger->get(request);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
}

void Window::ShowPic(QString &name)
{
    QPixmap pix(name);
    pix = pix.scaled(pix.size() / 10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel *lbl = new QLabel;
    lbl->setPixmap(pix);
    lbl->resize(pix.size());
    lbl->show();
}

void Window::Finished(QNetworkReply *replay)
{
        if(replay->error() != QNetworkReply::NoError) emit error();
        else emit done(replay->url(), replay->readAll());

        replay->deleteLater();
}

void Window::Go()
{
    download(QUrl(line->text()));
}

void Window::Progress(qint64 received, qint64 total)
{
    if(total <= 0)
    {
        slotError();
        return;
    }

    bar->setValue(100 * received / total);
}

void Window::slotDone(const QUrl &url, const QByteArray &ba)
{
    QString str = url.path().section("/", -1);
    QFile file(str);
    file.open(QIODevice::WriteOnly);
    file.write(ba);
    file.close();

    ShowPic(str);
}

void Window::slotError()
{
    QMessageBox::critical(this, "Error", "error");
}

