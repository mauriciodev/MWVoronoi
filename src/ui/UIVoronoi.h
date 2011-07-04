/****************************************************************************
** Form interface generated from reading ui file 'ui/UIVoronoi.ui'
**
** Created: Qui Mai 26 18:09:37 2011
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef UIVORONOI_H
#define UIVORONOI_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTabWidget;
class QWidget;
class QGroupBox;
class QComboBox;
class QButtonGroup;
class QLineEdit;
class QCheckBox;

class UIVoronoi : public QDialog
{
    Q_OBJECT

public:
    UIVoronoi( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~UIVoronoi();

    QPushButton* helpPushButton;
    QPushButton* okPushButton;
    QPushButton* cancelPushButton;
    QTabWidget* voronoiTabWidget;
    QWidget* inputPage;
    QGroupBox* weightGroupBox;
    QComboBox* weightComboBox;
    QButtonGroup* layerNameButtonGroup;
    QLineEdit* layerNameLineEdit;
    QGroupBox* themeGroupBox;
    QComboBox* themeComboBox;
    QWidget* optionsPage;
    QButtonGroup* optionsButtonGroup;
    QButtonGroup* boxButtonGroup;
    QComboBox* boxComboBox;
    QButtonGroup* layerLinesButtonGroup;
    QLineEdit* layerLinesLineEdit;
    QCheckBox* generateLinesCheckBox;

public slots:
    virtual void okPushButton_clicked() = 0;
    virtual void generateLinesCheckBox_clicked() = 0;
    virtual void themeComboBox_activated(const QString&) = 0;
    virtual void helpPushButton_clicked() = 0;
    virtual void themeComboBox_clicked(const QString&);

protected:
    QGridLayout* UIVoronoiLayout;
    QGridLayout* layout5;
    QSpacerItem* spacer1;
    QGridLayout* inputPageLayout;
    QGridLayout* layerNameButtonGroupLayout;
    QGridLayout* optionsPageLayout;
    QGridLayout* optionsButtonGroupLayout;
    QGridLayout* layout9;
    QGridLayout* boxButtonGroupLayout;
    QGridLayout* layout8;
    QGridLayout* layerLinesButtonGroupLayout;
    QGridLayout* layout6;
    QSpacerItem* spacer2;

protected slots:
    virtual void languageChange();

};

#endif // UIVORONOI_H
