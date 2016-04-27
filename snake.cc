/*******************************************************************************
* filename: snake.cc
* author: opensvn
* created on: 2016年04月27日 星期三 15时38分40秒
* license: GPLv2
* brief description: A simple implementation of the snake game
*******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

//bool operator==(const Point& lhs, const Point& rhs);
struct Point {
    friend bool operator==(const Point& lhs, const Point& rhs);
    Point(int x = 0, int y = 0): x(x), y(y) {}
    int x;
    int y;
};

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

struct SnakeBody {
    SnakeBody(Point position): pos(position), next(NULL) {}
    Point pos;
    SnakeBody* next;
    SnakeBody* prev;
};

struct Snake {
    Snake(): head(NULL), tail(NULL) {}

    Point move_right() {
        Point p(head->pos.y, head->pos.x + 1);
        add_head(p);
        return remove_tail();
    }

    Point move_left() {
        Point p(head->pos.y, head->pos.x - 1);
        add_head(p);
        return remove_tail();
    }

    Point move_up() {
        Point p(head->pos.y - 1, head->pos.x);
        add_head(p);
        return remove_tail();
    }

    Point move_down() {
        Point p(head->pos.y + 1, head->pos.x);
        add_head(p);
        return remove_tail();
    }

    void add_head(Point pos) {
        SnakeBody* body = new SnakeBody(pos);
        body->prev = NULL;
        body->next = head;
        head = body;
    }

    Point remove_tail() {
        Point p;
        p.x = tail->pos.x;
        p.y = tail->pos.y;
        tail->prev->next = NULL;
        tail = tail->prev;
        return p;
    }

    SnakeBody* head;
    SnakeBody* tail;
};

class SnakeGame {
public:    
    SnakeGame(int row, int col): row_max(row), col_max(col) {
        alloc_memory();

        Point p(row / 2, col / 2);

        snake.head = new SnakeBody(Point(col/2, row/2));
        snake.head->next = tail;
        snake.head->prev = NULL;
        snake.tail = head;


        rect[head->pos.y][head->pos.x] = '#'; // snake body represented by symbol #

        random_food();

        d = RIGHT;
    }

    ~SnakeGame() {
        if (rect != NULL) {
            for (int i = 0; i < row_max; ++i)
                delete[] rect[i];
            delete[] rect;
        }
        if (head != NULL) {
            while (head != NULL) {
                SnakeBody* p = head;
                head = head->next;
                delete p;
            }
        }
    }

    void move() {
        std::system("clear");

        int d = get_direction();
        
        switch (d) {
            case RIGHT:
                move_right(); break;
            case LEFT:
                move_left(); break;
            case UP:
                move_up(); break;
            case DOWN:
                move_down(); break;
            default:
                throw "invalid direction";
        }
    }

    bool alive() {
        if (head->pos.x == 0 || head->pos.x == col_max - 1
                || head->pos.y == 0 || head->pos.y == row_max - 1)
            return false;
        else
            return true;
    }

private:
    void alloc_memory() {
        rect = new char*[row_max];
        for (int i = 0; i < row_max; ++i) {
            rect[i] = new char[col_max];
            memset(rect[i], ' ', col_max);
        }
    }

    void random_food() {
        srand(std::time(0));
        do {
            int x = rand() % (col_max - 2) + 1; // food's x range (0, col_max - 1)
            int y = rand() % (row_max - 2) + 1; // food's y range (0, row_max - 1)

            if (rect[x][y] != '#') {
                rect[x][y] = '@';
                food_point.x = x;
                food_point.y = y;
                break;
            }
        } while (1);
    }

    int get_direction() {
        int direction = getchar();
        if (direction == 37)
            return LEFT;
        if (direction == 38)
            return UP;
        if (direction == 39)
            return RIGHT;
        if (direction == 40)
            return DOWN;
    }

    void clear(Point p) {
        rect[p.y][p.x] = ' ';
    }

    void move_right() {
        if (can_eat(RIGHT))
            eat_food();
        else
            clear(snake.move_right());
    }

    void move_left() {
        if (can_eat(LEFT))
            eat_food();
        else
            clear(snake.move_left());
    }

    void move_up() {
        if (can_eat(UP))
            eat_food();
        else
            clear(snake.move_up());
    }

    void move_down() {
        if (can_eat(DOWN))
            eat_food();
        else
            clear(snake.move_down());
    }

    bool can_eat(int direction) {
        Point head = snake->head;
        switch (direction) {
            case RIGHT:
                head.x += 1; break;
            case LEFT:
                head.x -= 1; break;
            case UP:
                head.y -= 1; break;
            case DOWN:
                head.y += 1; break;
        }
        return head == food_point;
    }

    void eat_food() {
        snake.add_head(food_point);
    }

private:
    int row_max;
    int col_max;
    //Point head;
    Point food_point;
    char **rect;
    enum Direction {
        RIGHT = 0,
        LEFT,
        UP,
        DOWN
    };
    Direction d;
    //SnakeBody* head;
    Snake snake;
};

int main() {
    SnakeGame game(60, 80);

    while (game.alive()) {
        game.move();
    }

    return 0;
}
