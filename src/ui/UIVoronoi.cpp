/****************************************************************************
** Form implementation generated from reading ui file 'ui/UIVoronoi.ui'
**
** Created: Qui Mai 26 18:12:51 2011
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "UIVoronoi.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qbuttongroup.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a UIVoronoi as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
UIVoronoi::UIVoronoi( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "UIVoronoi" );
    UIVoronoiLayout = new QGridLayout( this, 1, 1, 11, 6, "UIVoronoiLayout"); 

    layout5 = new QGridLayout( 0, 1, 1, 0, 6, "layout5"); 

    helpPushButton = new QPushButton( this, "helpPushButton" );

    layout5->addWidget( helpPushButton, 0, 0 );

    okPushButton = new QPushButton( this, "okPushButton" );

    layout5->addWidget( okPushButton, 0, 2 );
    spacer1 = new QSpacerItem( 80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout5->addItem( spacer1, 0, 1 );

    cancelPushButton = new QPushButton( this, "cancelPushButton" );

    layout5->addWidget( cancelPushButton, 0, 3 );

    UIVoronoiLayout->addLayout( layout5, 1, 0 );

    voronoiTabWidget = new QTabWidget( this, "voronoiTabWidget" );

    inputPage = new QWidget( voronoiTabWidget, "inputPage" );
    inputPageLayout = new QGridLayout( inputPage, 1, 1, 11, 6, "inputPageLayout"); 

    weightGroupBox = new QGroupBox( inputPage, "weightGroupBox" );

    weightComboBox = new QComboBox( FALSE, weightGroupBox, "weightComboBox" );
    weightComboBox->setGeometry( QRect( 10, 20, 461, 22 ) );

    inputPageLayout->addWidget( weightGroupBox, 2, 0 );

    layerNameButtonGroup = new QButtonGroup( inputPage, "layerNameButtonGroup" );
    layerNameButtonGroup->setColumnLayout(0, Qt::Vertical );
    layerNameButtonGroup->layout()->setSpacing( 6 );
    layerNameButtonGroup->layout()->setMargin( 11 );
    layerNameButtonGroupLayout = new QGridLayout( layerNameButtonGroup->layout() );
    layerNameButtonGroupLayout->setAlignment( Qt::AlignTop );

    layerNameLineEdit = new QLineEdit( layerNameButtonGroup, "layerNameLineEdit" );
    layerNameLineEdit->setFrameShape( QLineEdit::LineEditPanel );
    layerNameLineEdit->setFrameShadow( QLineEdit::Sunken );

    layerNameButtonGroupLayout->addWidget( layerNameLineEdit, 0, 0 );

    inputPageLayout->addWidget( layerNameButtonGroup, 1, 0 );

    themeGroupBox = new QGroupBox( inputPage, "themeGroupBox" );

    themeComboBox = new QComboBox( FALSE, themeGroupBox, "themeComboBox" );
    themeComboBox->setGeometry( QRect( 11, 21, 461, 22 ) );

    inputPageLayout->addWidget( themeGroupBox, 0, 0 );
    voronoiTabWidget->insertTab( inputPage, QString::fromLatin1("") );

    optionsPage = new QWidget( voronoiTabWidget, "optionsPage" );
    optionsPageLayout = new QGridLayout( optionsPage, 1, 1, 11, 6, "optionsPageLayout"); 

    optionsButtonGroup = new QButtonGroup( optionsPage, "optionsButtonGroup" );
    optionsButtonGroup->setColumnLayout(0, Qt::Vertical );
    optionsButtonGroup->layout()->setSpacing( 6 );
    optionsButtonGroup->layout()->setMargin( 11 );
    optionsButtonGroupLayout = new QGridLayout( optionsButtonGroup->layout() );
    optionsButtonGroupLayout->setAlignment( Qt::AlignTop );

    layout9 = new QGridLayout( 0, 1, 1, 0, 6, "layout9"); 

    boxButtonGroup = new QButtonGroup( optionsButtonGroup, "boxButtonGroup" );
    boxButtonGroup->setColumnLayout(0, Qt::Vertical );
    boxButtonGroup->layout()->setSpacing( 6 );
    boxButtonGroup->layout()->setMargin( 11 );
    boxButtonGroupLayout = new QGridLayout( boxButtonGroup->layout() );
    boxButtonGroupLayout->setAlignment( Qt::AlignTop );

    boxComboBox = new QComboBox( FALSE, boxButtonGroup, "boxComboBox" );

    boxButtonGroupLayout->addWidget( boxComboBox, 0, 0 );

    layout9->addWidget( boxButtonGroup, 1, 0 );

    layout8 = new QGridLayout( 0, 1, 1, 0, 6, "layout8"); 

    layerLinesButtonGroup = new QButtonGroup( optionsButtonGroup, "layerLinesButtonGroup" );
    layerLinesButtonGroup->setEnabled( FALSE );
    layerLinesButtonGroup->setColumnLayout(0, Qt::Vertical );
    layerLinesButtonGroup->layout()->setSpacing( 6 );
    layerLinesButtonGroup->layout()->setMargin( 11 );
    layerLinesButtonGroupLayout = new QGridLayout( layerLinesButtonGroup->layout() );
    layerLinesButtonGroupLayout->setAlignment( Qt::AlignTop );

    layerLinesLineEdit = new QLineEdit( layerLinesButtonGroup, "layerLinesLineEdit" );

    layerLinesButtonGroupLayout->addWidget( layerLinesLineEdit, 0, 0 );

    layout8->addWidget( layerLinesButtonGroup, 1, 0 );

    layout6 = new QGridLayout( 0, 1, 1, 0, 6, "layout6"); 

    generateLinesCheckBox = new QCheckBox( optionsButtonGroup, "generateLinesCheckBox" );
    generateLinesCheckBox->setChecked( FALSE );

    layout6->addWidget( generateLinesCheckBox, 0, 0 );
    spacer2 = new QSpacerItem( 161, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout6->addItem( spacer2, 0, 1 );

    layout8->addLayout( layout6, 0, 0 );

    layout9->addLayout( layout8, 0, 0 );

    optionsButtonGroupLayout->addLayout( layout9, 0, 0 );

    optionsPageLayout->addWidget( optionsButtonGroup, 0, 0 );
    voronoiTabWidget->insertTab( optionsPage, QString::fromLatin1("") );

    UIVoronoiLayout->addWidget( voronoiTabWidget, 0, 0 );
    languageChange();
    resize( QSize(537, 279).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okPushButton, SIGNAL( clicked() ), this, SLOT( okPushButton_clicked() ) );
    connect( cancelPushButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( generateLinesCheckBox, SIGNAL( clicked() ), this, SLOT( generateLinesCheckBox_clicked() ) );
    connect( helpPushButton, SIGNAL( clicked() ), this, SLOT( helpPushButton_clicked() ) );
    connect( themeComboBox, SIGNAL( activated(const QString&) ), this, SLOT( themeComboBox_activated(const QString&) ) );

    // tab order
    setTabOrder( voronoiTabWidget, themeComboBox );
    setTabOrder( themeComboBox, layerNameLineEdit );
    setTabOrder( layerNameLineEdit, okPushButton );
    setTabOrder( okPushButton, cancelPushButton );
    setTabOrder( cancelPushButton, helpPushButton );
    setTabOrder( helpPushButton, boxComboBox );
    setTabOrder( boxComboBox, layerLinesLineEdit );
    setTabOrder( layerLinesLineEdit, generateLinesCheckBox );
}

/*
 *  Destroys the object and frees any allocated resources
 */
UIVoronoi::~UIVoronoi()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void UIVoronoi::languageChange()
{
    setCaption( tr( "Voronoi" ) );
    helpPushButton->setText( tr( "Help" ) );
    okPushButton->setText( tr( "Ok" ) );
    cancelPushButton->setText( tr( "Cancel" ) );
    weightGroupBox->setTitle( tr( "Weighting attribute" ) );
    layerNameButtonGroup->setTitle( tr( "Choose a name to result Layer" ) );
    themeGroupBox->setTitle( tr( "Select a Theme" ) );
    voronoiTabWidget->changeTab( inputPage, tr( "Input Data" ) );
    optionsButtonGroup->setTitle( tr( "Result" ) );
    boxButtonGroup->setTitle( tr( "Use the box of this Layer to delimit the diagram" ) );
    layerLinesButtonGroup->setTitle( tr( "Choose a name to Layer of Lines" ) );
    generateLinesCheckBox->setText( tr( "Generate also the Layer of Lines" ) );
    voronoiTabWidget->changeTab( optionsPage, tr( "Options" ) );
}

void UIVoronoi::themeComboBox_clicked(const QString&)
{
    qWarning( "UIVoronoi::themeComboBox_clicked(const QString&): Not implemented yet" );
}

