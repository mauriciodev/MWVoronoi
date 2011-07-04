/****************************************************************************
** UIVoronoi meta object code from reading C++ file 'UIVoronoi.h'
**
** Created: Thu May 26 18:12:55 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../ui/UIVoronoi.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *UIVoronoi::className() const
{
    return "UIVoronoi";
}

QMetaObject *UIVoronoi::metaObj = 0;
static QMetaObjectCleanUp cleanUp_UIVoronoi( "UIVoronoi", &UIVoronoi::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString UIVoronoi::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "UIVoronoi", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString UIVoronoi::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "UIVoronoi", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* UIVoronoi::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"okPushButton_clicked", 0, 0 };
    static const QUMethod slot_1 = {"generateLinesCheckBox_clicked", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"themeComboBox_activated", 1, param_slot_2 };
    static const QUMethod slot_3 = {"helpPushButton_clicked", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"themeComboBox_clicked", 1, param_slot_4 };
    static const QUMethod slot_5 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "okPushButton_clicked()", &slot_0, QMetaData::Public },
	{ "generateLinesCheckBox_clicked()", &slot_1, QMetaData::Public },
	{ "themeComboBox_activated(const QString&)", &slot_2, QMetaData::Public },
	{ "helpPushButton_clicked()", &slot_3, QMetaData::Public },
	{ "themeComboBox_clicked(const QString&)", &slot_4, QMetaData::Public },
	{ "languageChange()", &slot_5, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"UIVoronoi", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_UIVoronoi.setMetaObject( metaObj );
    return metaObj;
}

void* UIVoronoi::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "UIVoronoi" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool UIVoronoi::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: okPushButton_clicked(); break;
    case 1: generateLinesCheckBox_clicked(); break;
    case 2: themeComboBox_activated((const QString&)static_QUType_QString.get(_o+1)); break;
    case 3: helpPushButton_clicked(); break;
    case 4: themeComboBox_clicked((const QString&)static_QUType_QString.get(_o+1)); break;
    case 5: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool UIVoronoi::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool UIVoronoi::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool UIVoronoi::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
