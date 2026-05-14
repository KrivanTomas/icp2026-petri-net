/**
 * @file main_window.h
 *
 * @brief Header file for the main gui window
 *
  * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_graphics_scene.h"

#include <QMainWindow>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
};
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onEditorModeChanged(EditorGraphicsScene::Mode mode);
    void onEditorSelectionChanged();
    void onEditorDeleteSelection();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    EditorGraphicsScene *scene;
};
