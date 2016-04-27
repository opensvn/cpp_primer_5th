/*******************************************************************************
* filename: snake.cc
* author: opensvn
* created on: 2016年04月27日 星期三 15时38分40秒
* license: GPLv2
* brief description: A simple implementation of the snake game
*******************************************************************************/

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

struct Point {
    friend bool operator==(const Point& lhs, const Point& rhs);
    friend ostream& operator<<(ostream& out, const Point& p);

    Point(int x = 0, int y = 0): x(x), y(y) {}
    int x;
    int y;
};

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << "Point: (" << p.x << ", " << p.y << ")";
    return out;
}

struct SnakeBody {
    SnakeBody(Point position): pos(position), next(NULL) {}
    Point pos;
    SnakeBody* next;
    SnakeBody* prev;
};

struct Snake {
    Snake(): head(NULL), tail(NULL) {}
    ~Snake() {
        SnakeBody* body;
        while (head != NULL) {
            body = head;
            head = head->next;
            delete body;
        }
    }

    Point move_right() {
        Point p(head->pos.x, head->pos.y + 1);
        add_head(p);
        return remove_tail();
    }

    Point move_left() {
        Point p(head->pos.x, head->pos.y - 1);
        add_head(p);
        return remove_tail();
    }

    Point move_up() {
        Point p(head->pos.x - 1, head->pos.y);
        add_head(p);
        return remove_tail();
    }

    Point move_down() {
        Point p(head->pos.x + 1, head->pos.y);
        add_head(p);
        return remove_tail();
    }

    void add_head(Point pos) {
        SnakeBody* body = new SnakeBody(pos);
        body->prev = NULL;
        body->next = head;
        head->prev = body;
        head = body;
    }

    Point remove_tail() {
        Point p = tail->pos;
        SnakeBody* body = tail;
        tail->prev->next = NULL;
        tail = tail->prev;
        delete body;
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

        snake.head = new SnakeBody(p);
        snake.head->next = NULL;
        snake.head->prev = NULL;
        snake.tail = snake.head;

        rect[p.x][p.y] = '#'; // snake body represented by symbol '#'

        random_food();

        d = RIGHT;
    }

    ~SnakeGame() {
        if (rect != NULL) {
            for (int i = 0; i < row_max; ++i)
                delete[] rect[i];
            delete[] rect;
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
        if (snake.head->pos.x == 0 || snake.head->pos.x == row_max - 1
                || snake.head->pos.y == 0 || snake.head->pos.y == col_max - 1)
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
            int x = rand() % (row_max - 2) + 1; // food's x range (0, row_max - 1)
            int y = rand() % (col_max - 2) + 1; // food's y range (0, col_max - 1)

            if (rect[x][y] != '#') {
                rect[x][y] = '@'; // food represented by '@'
                food_point.x = x;
                food_point.y = y;
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
            for (int j = 1; j < col_max - 1; ++j) {
                cout << rect[i][j];
            }
            cout << "|" << endl;
        }
        for (int i = 0; i < col_max; ++i)
            cout << "-";
        cout << endl;
    }

    void clear(Point p) {
        rect[p.x][p.y] = ' ';
    }

    void set_head() {
        rect[snake.head->pos.x][snake.head->pos.y] = '#';
    }

    void move_right() {
        if (snake.head->next == NULL || snake.head->next->pos.y != snake.head->pos.y + 1) {
            if (can_eat(RIGHT))
                eat_food();
            else
                clear(snake.move_right());
            set_head();
        }
    }

    void move_left() {
        if (snake.head->next == NULL || snake.head->next->pos.y != snake.head->pos.y - 1) {
            if (can_eat(LEFT))
                eat_food();
            else
                clear(snake.move_left());
            set_head();
        }
    }

    void move_up() {
        if (snake.head->next == NULL || snake.head->next->pos.x != snake.head->pos.x - 1) {
            if (can_eat(UP))
                eat_food();
            else
                clear(snake.move_up());
            set_head();
        }
    }

    void move_down() {
        if (snake.head->next == NULL || snake.head->next->pos.x != snake.head->pos.x + 1) {
            if (can_eat(DOWN))
                eat_food();
            else
                clear(snake.move_down());
            set_head();
        }
    }

    bool can_eat(int direction) {
        Point head = snake.head->pos;
        switch (direction) {
            case RIGHT:
                head.y += 1; break;
            case LEFT:
                head.y -= 1; break;
            case UP:
                head.x -= 1; break;
            case DOWN:
                head.x += 1; break;
        }
        return head == food_point;
    }

    void eat_food() {
        snake.add_head(food_point);
        random_food();
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
    SnakeGame game(20, 40);

    while (game.alive()) {
        game.move();
    }

    cout << "You are dead!" << endl;

    return 0;
}
