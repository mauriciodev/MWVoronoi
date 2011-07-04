/****************************************************************************
** VoronoiDiagramPlugin meta object code from reading C++ file 'voronoidiagramplugin.h'
**
** Created: Thu May 26 18:12:53 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../include/voronoidiagramplugin.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *VoronoiDiagramPlugin::className() const
{
    return "VoronoiDiagramPlugin";
}

QMetaObject *VoronoiDiagramPlugin::metaObj = 0;
static QMetaObjectCleanUp cleanUp_VoronoiDiagramPlugin( "VoronoiDiagramPlugin", &VoronoiDiagramPlugin::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString VoronoiDiagramPlugin::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VoronoiDiagramPlugin", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString VoronoiDiagramPlugin::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VoronoiDiagramPlugin", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* VoronoiDiagramPlugin::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod slot_0 = {"showVoronoiWindow", 0, 0 };
    static const QUMethod slot_1 = {"showDelaunayWindow", 0, 0 };
    static const QUMethod slot_2 = {"showMWVoronoiWindow", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "showVoronoiWindow()", &slot_0, QMetaData::Protected },
	{ "showDelaunayWindow()", &slot_1, QMetaData::Protected },
	{ "showMWVoronoiWindow()", &slot_2, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"VoronoiDiagramPlugin", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_VoronoiDiagramPlugin.setMetaObject( metaObj );
    return metaObj;
}

void* VoronoiDiagramPlugin::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "VoronoiDiagramPlugin" ) )
	return this;
    if ( !qstrcmp( clname, "TViewAbstractPlugin" ) )
	return (TViewAbstractPlugin*)this;
    return QObject::qt_cast( clname );
}

bool VoronoiDiagramPlugin::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: showVoronoiWindow(); break;
    case 1: showDelaunayWindow(); break;
    case 2: showMWVoronoiWindow(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool VoronoiDiagramPlugin::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool VoronoiDiagramPlugin::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool VoronoiDiagramPlugin::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
