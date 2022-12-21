#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include <QVector>
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
class Snake : public QMainWindow
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();
protected:
      void paintEvent(QPaintEvent *event);
      void timerEvent(QTimerEvent *event);
      void keyPressEvent(QKeyEvent *event);
private:
      int Height = 400;
      int Width = 400;
      int dot_size = 10;
      int timer;
      int score = 0;

      bool right,up,down,left,ingame;
      QVector <QPoint> pos;
      QPoint goal_pos;
      QPushButton retry_but;

      void start_game();
      void create_goal();
      void check_goal();
      void move_snake();
      void collision();
      void records();
      void game_over();

};
#endif // SNAKE_H
