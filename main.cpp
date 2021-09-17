#include "mainwidget.h"
#include <QApplication>
#include <QMessageBox>
#include "mystylesheet.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
//    QMutex mutex ;
//    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
//    case QtDebugMsg:
//        fprintf(logfile, "[%s Debug   ] : %s  (%s:%u, %s)\n", QTime::currentTime().toString().toLocal8Bit().constData(), localMsg.constData(), context.file, context.line, context.function);
//        break;
//    case QtWarningMsg:
//        fprintf(logfile, "[%s Warning ] : %s  (%s:%u, %s)\n", QTime::currentTime().toString().toLocal8Bit().constData(),localMsg.constData(), context.file, context.line, context.function);
//        break;
    case QtCriticalMsg:
//        fprintf(logfile, "[%s Critical] : %s  (%s:%u, %s)\n", QTime::currentTime().toString().toLocal8Bit().constData(),localMsg.constData(), context.file, context.line, context.function);
//        break;
//    case QtInfoMsg:
////        fprintf(logfile, "[%s Info    ] : %s  (%s:%u, %s)\n", QTime::currentTime().toString().toLocal8Bit().constData(),localMsg.constData(), context.file, context.line, context.function);
//        fprintf(logfile, "%s\n", localMsg.constData());
//        break;
    case QtFatalMsg:
//        fprintf(logfile, "[%s Fatal   ] : %s  (%s:%u, %s)\n", QTime::currentTime().toString().toLocal8Bit().constData(),localMsg.constData(), context.file, context.line, context.function);
//        abort();

        QMessageBox::critical(nullptr, "cirtical", msg, QMessageBox::Ok);
    }

    //OutputDebugString(reinterpret_cast<const wchar_t *>(Message.utf16()));


//    fflush(logfile) ;

//    QTextStream ts(stdout);
//    ts<<msg<<endl;

//    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::addLibraryPath("./PlugIns");

    QFont font("Arial");
    QApplication::setFont(font);

#ifndef QT_DEBUG
    qInstallMessageHandler(myMessageOutput);
#endif

#ifndef GLOBAL_SITE
    a.setStyleSheet(myChinaStyleSheet);
#else
    a.setStyleSheet(myStyleSheet);
#endif

    MainWidget w;
    w.show();

    return a.exec();
}
