#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <QException>
#include <QString>
#include <QDateTime>
//#include <boost/stacktrace/stacktrace.hpp>
class Exception : public QException
{
public:
    Exception(const QString &);
    Exception() : message("") {
  //      backtrace = boost::stacktrace::stacktrace();
    }
    virtual ~Exception() _GLIBCXX_USE_NOEXCEPT;

    void raise() const Q_DECL_OVERRIDE;
    Exception *clone() const Q_DECL_OVERRIDE;
    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;
//    const boost::stacktrace::stacktrace getBacktrace() const _GLIBCXX_USE_NOEXCEPT {
//        return backtrace;
//    }
protected:
    QByteArray message;
//    boost::stacktrace::stacktrace backtrace;
};

#define DEFINE_EXCEPTION(NAME, EXTENDS) class NAME : public EXTENDS {\
    public:\
        NAME(const QString & message) : EXTENDS(message) {}\
        NAME(): EXTENDS() {}\
    }

DEFINE_EXCEPTION(DataBaseException, Exception);
DEFINE_EXCEPTION(UsersException, DataBaseException);
DEFINE_EXCEPTION(UserNotFoundException, UsersException);
DEFINE_EXCEPTION(UserExistsException, UsersException);
DEFINE_EXCEPTION(UserPersistException, UsersException);

#endif // EXCEPTIONS_H
