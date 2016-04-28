/*******************************************************************************
* filename: snake.cc
* author: opensvn
* created on: 2016年04月27日 星期三 15时38分40秒
* license: GPLv2
* brief description: A simple implementation of the snake game
*******************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Point {
    friend bool operator==(const Point &lhs, const Point &rhs);
    friend bool operator!=(const Point &lhs, const Point &rhs);
    friend ostream &operator<<(ostream &out, const Point &p);

    Point(int x = 0, int y = 0): x(x), y(y) {}
    int x;
    int y;
};

bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point &lhs, const Point &rhs) {
    return !(lhs == rhs);
}

ostream &operator<<(ostream &out, const Point &p) {
    out << "Point: (" << p.x << ", " << p.y << ")";
    return out;
}

struct SnakeBody {
    SnakeBody(Point position): pos(position), next(NULL) {}
    Point pos;
    SnakeBody *next;
    SnakeBody *prev;
};

enum Direction {
    RIGHT = 0,
    LEFT,
    UP,
    DOWN
};

class Snake {
public:
    Snake(int row, int col): row_max(row), col_max(col), is_alive(true), d(RIGHT) {
        alloc_memory();

        Point p(row / 2, col / 2);

        head = new SnakeBody(p);
        head->next = NULL;
        head->prev = NULL;
        tail = head;

        rect[p.x][p.y] = '#'; // snake body represented by symbol '#'

        random_food();
    }

    ~Snake() {
        if (rect != NULL) {
            for (int i = 0; i < row_max; ++i)
                delete[] rect[i];
            delete[] rect;
        }

        while (head != NULL) {
            SnakeBody *body = head;
            head = head->next;
            delete body;
        }
    }

    void move() {
        print_rec();

        int direction = get_direction();

        switch (direction) {
            case RIGHT:
                move_right(); break;
            case LEFT:
                move_left(); break;
            case UP:
                move_up(); break;
            case DOWN:
                move_down(); break;
        }
    }

    bool alive() {
        return is_alive;
    }

private:
    void alloc_memory() {
        rect = new char *[row_max];
        for (int i = 0; i < row_max; ++i) {
            rect[i] = new char[col_max];
            fill(rect[i], rect[i] + col_max, ' ');
        }
    }

    void random_food() {
        srand(std::time(0));
        do {
            int x = rand() % (row_max - 2) + 1; // food's x range (0, row_max - 1)
            int y = rand() % (col_max - 2) + 1; // food's y range (0, col_max - 1)

            if (rect[x][y] != '#') {
                rect[x][y] = '@'; // food represented by '@'
                food.x = x;
                food.y = y;
                break;
            }
        } while (1);
    }

    int get_direction() {
        int direction = getchar();
        if (direction == 'a')
            return LEFT;
        if (direction == 'w')
            return UP;
        if (direction == 'd')
            return RIGHT;
        if (direction == 's')
            return DOWN;
        return -1;
    }

    void print_rec() {
        std::system("clear");
        for (int i = 0; i < col_max; ++i)
            cout << "-";
        cout << endl;
        for (int i = 1; i < row_max - 1; ++i) {
            cout << "|";
            for (int j = 1; j < col_max - 1; ++j)
                cout << rect[i][j];
            cout << "|" << endl;
        }
        for (int i = 0; i < col_max; ++i)
            cout << "-";
        cout << endl;
    }

    void add_head(const Point &p) {
        SnakeBody *body = new SnakeBody(p);
        body->prev = NULL;
        body->next = head;
        head->prev = body;
        head = body;

        rect[head->pos.x][head->pos.y] = '#';
    }

    void remove_tail() {
        SnakeBody *body = tail;
        tail->prev->next = NULL;
        tail = tail->prev;

        // clear tail
        rect[body->pos.x][body->pos.y] = ' ';

        delete body;
    }

    char get_symbol(const Point &p) {
        return rect[p.x][p.y];
    }

    void move_right() {
        Point right(head->pos.x, head->pos.y + 1);
        if (right == food)
            eat_food();
        else {
            if (right.y == col_max - 1) // run into the wall
                is_alive = false;
            else if (head->next == NULL || right != head->next->pos) {
                if (get_symbol(right) == '#') // run into the body
                    is_alive = false;
                else {
                    add_head(right);
                    remove_tail();
                }
            }
        }
    }

    void move_left() {
        Point left(head->pos.x, head->pos.y - 1);
        if (left == food)
            eat_food();
        else {
            if (left.y == 0) // run into the wall
                is_alive = false;
            else if (head->next == NULL || left != head->next->pos) {
                if (get_symbol(left) == '#') // run into the body
                    is_alive = false;
                else {
                    add_head(left);
                    remove_tail();
                }
            }
        }
    }

    void move_up() {
        Point up(head->pos.x - 1, head->pos.y);
        if (up == food)
            eat_food();
        else {
            if (up.x == 0) // run into the wall or snake body
                is_alive = false;
            else if (head->next == NULL || up != head->next->pos) {
                if (get_symbol(up) == '#') // run into the body
                    is_alive = false;
                else {
                    add_head(up);
                    remove_tail();
                }
            }
        }
    }

    void move_down() {
        Point down(head->pos.x + 1, head->pos.y);
        if (down == food)
            eat_food();
        else {
            if (down.x == row_max - 1) // run into the wall
                is_alive = false;
            else if (head->next == NULL || down != head->next->pos) {
                if (get_symbol(down) == '#') // run into the body
                    is_alive = false;
                else {
                    add_head(down);
                    remove_tail();
                }
            }
        }
    }

    void eat_food() {
        add_head(food);
        random_food();
    }

private:
    int row_max;
    int col_max;

    Point food;
    char **rect;
    Direction d;

    bool is_alive;

    SnakeBody *head;
    SnakeBody *tail;
};

int main() {
    Snake snake(10, 20);

    while (snake.alive()) {
        snake.move();
    }

    cout << "You are dead!" << endl;

    return 0;
}
