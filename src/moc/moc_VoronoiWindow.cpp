/****************************************************************************
** VoronoiWindow meta object code from reading C++ file 'VoronoiWindow.h'
**
** Created: Wed Jun 15 03:22:40 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../include/VoronoiWindow.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *VoronoiWindow::className() const
{
    return "VoronoiWindow";
}

QMetaObject *VoronoiWindow::metaObj = 0;
static QMetaObjectCleanUp cleanUp_VoronoiWindow( "VoronoiWindow", &VoronoiWindow::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString VoronoiWindow::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VoronoiWindow", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString VoronoiWindow::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VoronoiWindow", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* VoronoiWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = UIVoronoi::staticMetaObject();
    static const QUMethod slot_0 = {"generateLinesCheckBox_clicked", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "themeName", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"themeComboBox_activated", 1, param_slot_1 };
    static const QUMethod slot_2 = {"okPushButton_clicked", 0, 0 };
    static const QUMethod slot_3 = {"helpPushButton_clicked", 0, 0 };
    static const QUMethod slot_4 = {"showWindow", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "generateLinesCheckBox_clicked()", &slot_0, QMetaData::Public },
	{ "themeComboBox_activated(const QString&)", &slot_1, QMetaData::Public },
	{ "okPushButton_clicked()", &slot_2, QMetaData::Public },
	{ "helpPushButton_clicked()", &slot_3, QMetaData::Public },
	{ "showWindow()", &slot_4, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"VoronoiWindow", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_VoronoiWindow.setMetaObject( metaObj );
    return metaObj;
}

void* VoronoiWindow::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "VoronoiWindow" ) )
	return this;
    return UIVoronoi::qt_cast( clname );
}

bool VoronoiWindow::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: generateLinesCheckBox_clicked(); break;
    case 1: themeComboBox_activated((const QString&)static_QUType_QString.get(_o+1)); break;
    case 2: okPushButton_clicked(); break;
    case 3: helpPushButton_clicked(); break;
    case 4: showWindow(); break;
    default:
	return UIVoronoi::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool VoronoiWindow::qt_emit( int _id, QUObject* _o )
{
    return UIVoronoi::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool VoronoiWindow::qt_property( int id, int f, QVariant* v)
{
    return UIVoronoi::qt_property( id, f, v);
}

bool VoronoiWindow::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
