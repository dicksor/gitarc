#include "gaviewgame.h"
#include "gaverticalnotes.h"
#include "gahorizontalnotesbar.h"
#include "ganotes.h"
#include "ganotereader.h"
#include "constants.h"
#include <QGraphicsWidget>
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>

GAViewGame::GAViewGame(QSize layoutSize, QGraphicsView *parent) : QGraphicsView(parent)
{

    this->scene = new QGraphicsScene(this);
    this->setScene(this->scene);
    this->setSceneRect(0, 0, layoutSize.width(), layoutSize.height());

    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    verticalNotes = new GAVerticalNotes(this->sceneRect());
    this->scene->addItem(verticalNotes);

    horizontalNotes = new GAHorizontalNotesBar(this->sceneRect());
    this->scene->addItem(horizontalNotes);

    GANoteReader *noteReader = new GANoteReader(":res/partitions/notes.csv");
    this->connect(noteReader, &GANoteReader::nextNotesLine, this, &GAViewGame::drawNoteLine);
    noteReader->readPartition();

    //show boundingRect of all items on the scene
    /*QList<QGraphicsItem*> list = scene->items();

    for(int i = 0; i < list.size(); i++)
    {
        QGraphicsRectItem *rect = new QGraphicsRectItem(list[i]->boundingRect());
        rect->setBrush(Qt::red);
        scene->addItem(rect);
    }*/
    this->show();
}

void GAViewGame::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        horizontalNotes->isPressed(0);
    }

    if(event->key() == Qt::Key_S)
    {
        horizontalNotes->isPressed(1);
    }

    if(event->key() == Qt::Key_D)
    {
        horizontalNotes->isPressed(2);
    }

    if(event->key() == Qt::Key_F)
    {
        horizontalNotes->isPressed(3);
    }
}

void GAViewGame::drawNoteLine(QByteArray notesLine)
{
    float stripWidth = this->sceneRect().width() / NUM_NOTES;
    float leftStripMargin = LEFTMARGIN_PERCENTAGE * stripWidth;
    for(int i = 0; i <= NUM_NOTES; i++)
    {
        if(notesLine[i] == '1'){
            float xPos = leftStripMargin + i * stripWidth / 2;
            GANotes *notes = new GANotes(QPointF(xPos - NOTE_RADIUS / 4, 0), this->sceneRect().height());
            this->scene->addItem(notes);
        }
    }
}

