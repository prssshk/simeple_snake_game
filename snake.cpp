#include "snake.h"
#include <QPainter>
#include <QTimer>
#include <QColor>
#include <QPushButton>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGridLayout>
#include <QDir>


Snake::Snake(QWidget *parent)
    : QMainWindow(parent)
{
            //WINDOW_SETTINGS
    resize(Width, Height);
    setStyleSheet("background-color:black;");
            //KEY_SETTINGS
    up = false;
    down = false;
    left = false;
    right = true;

    ingame = true;
    start_game();

    QPushButton *retry_but = new QPushButton;
    retry_but->setGeometry(155,210,40,20);
    retry_but->setVisible(false);


}

void Snake::start_game()
{
   int x_pos = qrand()%300;
   int y_pos = qrand()%390;
   for (int i = 0;i<3;i ++)
       pos.append(QPoint((x_pos - x_pos % 10)+40-i*10,y_pos - y_pos % 10));

   create_goal();
   timer = startTimer(100);
   repaint();

}

void Snake::create_goal()
{
    int x_pos = qrand()%390;
    int y_pos = qrand()%390;
    goal_pos.setX(x_pos-x_pos % 10);goal_pos.setY(y_pos - y_pos % 10);

    for(int i = 0;i<pos.size()-1;i ++)
    {
        if (goal_pos ==  pos[i])
        {
             x_pos = qrand()%390;
             y_pos = qrand()%390;
            goal_pos.setX(x_pos);goal_pos.setY(y_pos);
             i = -1;
        }
    }





}

void Snake::check_goal()
{
    if (pos[0] == goal_pos)
    {
        score ++;
        pos.append(QPoint(pos[pos.size()-1].rx()-10,pos[pos.size()-1].ry()));
        create_goal();

        QMediaPlayer * m_player = new QMediaPlayer(this);
        m_player->setMedia(QUrl("smb_1-up.wav"));
        m_player->setVolume(50);
        m_player->play();
    }
}

void Snake::move_snake()
{
            //BODY_CHANGE_POSITION
    for (int i = pos.size();i>0;i--)
       {
            pos[i].rx() = pos[i-1].rx();
            pos[i].ry() = pos[i-1].ry();
       }
            //HEAD_CHANGE_POSITION
    if (up)
        pos[0].ry() -= 10;
    if (down)
        pos[0].ry() += 10;
    if (right)
        pos[0].rx() += 10;
    if (left)
        pos[0].rx() -= 10;
}

void Snake::collision()
{
                //WALLS
    if (pos[0].rx()>= Width || pos[0].rx()<0)
        ingame = false;
    if (pos[0].ry()>= Height || pos[0].ry()<0)
        ingame = false;

                //BODY
    for (int i = pos.size(); i > 0; i--)
        {
            if ((i > 4) && (pos[0].rx() == pos[i].rx()) && (pos[0].ry() == pos[i].ry())) {
                ingame = false;
            }
        }
    if (!ingame)
        killTimer(timer);
}

void Snake::game_over()
{
    QMediaPlayer * m_player = new QMediaPlayer(this);
    m_player->setMedia(QUrl("smb_gameover.wav"));
    m_player->setVolume(50);
    m_player->play();
  // retry_but.setVisible(true);

}


void Snake::keyPressEvent(QKeyEvent *event) {

    int key = event->key();

    if ((key == Qt::Key_Left) && (!right)) {
        left = true;
        up = false;
        down = false;
    }

    if ((key == Qt::Key_Right) && (!left)) {
        right = true;
        up = false;
        down = false;
    }

    if ((key == Qt::Key_Up) && (!down)) {
        up = true;
        right = false;
        left = false;
    }

    if ((key == Qt::Key_Down) && (!up)) {
        down = true;
        right = false;
        left = false;
    }

    QWidget::keyPressEvent(event);
}
void Snake::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (ingame)
   {
                //HEAD
    painter.setPen(QColor(0,255,0));
    painter.drawRect(pos[0].rx(),pos[0].ry(),10,10);
                //BODY
    painter.setPen(QColor(0,128,0));
    for(int i = 1;i<pos.size();i ++)
    {
        painter.drawRect(pos[i].rx(),pos[i].ry(),10,10);
    }
                //GOAL
    painter.setPen(QColor(255,0,0));
    painter.drawRect(goal_pos.rx(),goal_pos.ry(),10,10);
    }
    else
    {
    QString mes = "GAME OVER";
    painter.setPen(QColor(Qt::white));
    painter.drawText(QPoint(155,190),mes);
    game_over();
    }
}

void Snake::timerEvent(QTimerEvent *) {

    if (ingame) {

        check_goal();
        collision();
        move_snake();
    }

    repaint();
}


Snake::~Snake()
{
}

