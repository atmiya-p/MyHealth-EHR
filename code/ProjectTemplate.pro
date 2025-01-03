QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = MyHealth

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    RecordBuilder.cpp \
    sqlite3.c \
    DBDoctor.cpp \
    DBManager.cpp \
    DBPatient.cpp \
    Doctor.cpp \
    Patient.cpp \
    Record.cpp \
    SignUp.cpp \
    User.cpp \
    addpatientwindow.cpp \
    addrecordwindow.cpp \
    doctordashboardwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    patientdashboardwindow.cpp \
    recordmanager.cpp \
    searchpatientwindow.cpp \
    signupwindow.cpp

HEADERS += \
    RecordBuilder.h \
    sqlite3.h \
    DBDoctor.h \
    DBManager.h \
    DBPatient.h \
    Doctor.h \
    Patient.h \
    Record.h \
    SignUp.h \
    User.h \
    addpatientwindow.h \
    addrecordwindow.h \
    doctordashboardwindow.h \
    mainwindow.h \
    patientdashboardwindow.h \
    recordmanager.h \
    searchpatientwindow.h \
    signupwindow.h

FORMS += \
    addpatientwindow.ui \
    addrecordwindow.ui \
    doctordashboardwindow.ui \
    mainwindow.ui \
    patientdashboardwindow.ui \
    searchpatientwindow.ui \
    signupwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
