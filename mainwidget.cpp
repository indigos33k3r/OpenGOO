#include "mainwidget.h"
#include <QDebug>


#include "svglevelloader.h"

MainWidget::MainWidget(QRect geometry,bool debug,bool multiwindow,QWidget *parent)
    : QGLWidget(QGLFormat(QGL::HasOverlay),parent)
{
    if (!multiwindow) this->showFullScreen();//To have the game full screen
    this->setGeometry(geometry);
    this->geometry=geometry;
    this->debug=debug;
    this->multiwindow=multiwindow;
    if (debug&&multiwindow) qWarning()<<"Multi Window mode ON";
    levelS=new LevelSelector(geometry,this);//Create the level selector
    levelS->show();//Show the level selector
    level=NULL;
    connect(levelS,SIGNAL(closing()),this,SLOT(close())); //Connect the closing of the levelSelector with the closing of the game
    connect(levelS,SIGNAL(eventLevelSelected()),this,SLOT(levelSelected()));//Connect the choose of the the level to the creation of the level

}

MainWidget::~MainWidget()
{
    if (levelS!=NULL){
        delete levelS;
    }
    if (level!=NULL){
        delete level;
    }
}

void MainWidget::closeEvent(QCloseEvent *e){
    if (level!=NULL){
        level->close();
    }

    e->accept();
}


void MainWidget::levelSelected()//Create the level selected
{

    if(debug)qWarning()<<"Level Selected "<<levelS->getLevelSelected().toAscii();
    if(!levelS->getLevelSelected().compare("Exit")){
        this->close();
        return;
    }
    else
    {

        if (multiwindow) this->hide();

        if (multiwindow){
            if (!debug)
                level=new Level(geometry,levelS->getLevelSelected(),STANDARD,true); //Create the level
            else{
                level=new Level(geometry,levelS->getLevelSelected(),DEBUG,true); //Create the level
                qWarning()<<"Level object created";
            }
        }
        else {
            if (!debug)
                level=new Level(geometry,levelS->getLevelSelected(),STANDARD,false,this); //Create the level
            else{
                level=new Level(geometry,levelS->getLevelSelected(),DEBUG,false,this); //Create the level
                qWarning()<<"Level object created";
            }
        }

        delete levelS;
        levelS=NULL;

        this->repaint();

        connect(level,SIGNAL(closing()),this,SLOT(close()));//Connect the closing of the level with the closing of the game
        connect(level,SIGNAL(eventBackToMainMenu()),this,SLOT(backToMainMenu()));
        if (level->startLevel()){
            level->show();//Show the Level

            if (debug) qWarning()<<"level showed an signal connected.";
        }

    }
}

void MainWidget::backToMainMenu()
{
    this->show();
    qWarning()<<"BackToMainMenu!";
    delete level;
    levelS=new LevelSelector(geometry,this);//Create the level selector
    levelS->show();//Show the level selector
    level=NULL;
    connect(levelS,SIGNAL(closing()),this,SLOT(close())); //Connect the closing of the levelSelector with the closing of the game
    connect(levelS,SIGNAL(eventLevelSelected()),this,SLOT(levelSelected()));//Connect the choose of the the level to the creation of the level delete level;
    qWarning()<<"HERE LEVEL SELECTOR!!";
}