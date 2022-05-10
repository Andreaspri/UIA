#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <thread>
#include <queue_wave_front.h>
#include <Stack_returnpath.h>
#include <cmath>
#include <string>
#include <bestanavnet.h>

#define ISPART2 0 // Switch to 1 if this run will do the second part of the problem
#define OBSTACLE 3
#define NOTHING 0
#define WAY_BACK 4
#define DIRECTIONS 4
#define BORDER_THICKNESS_SQUARES 1
#define MAXMAZESIZE 10
#define WALLSPACER 2
#define FILE_PATH "..\\assets\\test.txt"
#define WIDTH 1000
#define HEIGHT 800
#define DIMENSIONS 2
#define MOUSE_POS 0
#define NUMBER_SIZE 0.8
#define NUMBER_POS 0.17
#define CHEESE_POS 1
#define VISITED_DELAY 0ms
#define MOUSE_DELAY 50ms
#define MOUSE_PATH_TO_WALLS false

// Setting up internal clock.
using std::chrono::system_clock;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

typedef int **Maze;

// GLOBALS
Maze maze;
Maze distance;
Maze visited;

int rows = 0;
int columns = 0;

void alloc_maze();

int read_maze(Super_stack);

void print_maze();

void reset_maze();

void Dijkstras(int, int, int, int, sf::RenderWindow *, float, float, const sf::Font &font, sf::Event *);

Position create_position();

void edit_grid(sf::RenderTarget *window, float, float);

int *get_position(int, int, float, float);

void set_obstacle(int x, int y);

void reset_display_with_visited(sf::RenderWindow *, float, float, Position, Position, const sf::Font &font, sf::Event*);

void display_one_point(sf::RenderWindow *, int, int, float, float, sf::Color, bool visited, const sf::Font &font, sf::Event*);

void display_without_visited(sf::RenderWindow *, float, float, Position, Position, const sf::Font &font, sf::Event*);

bool north_node(Current_queue *, Position, Position, Position);

bool south_node(Current_queue *, Position, Position, Position);

bool west_node(Current_queue *, Position, Position, Position);

bool east_node(Current_queue *, Position, Position, Position);

Position north_backtrack(sf::RenderWindow *, Current_stack *, float, float, Position, Position, Position, Position *,
                         const sf::Font &font, sf::Event*);

Position south_backtrack(sf::RenderWindow *, Current_stack *, float, float, Position, Position, Position, Position *,
                         const sf::Font &font, sf::Event*);

Position west_backtrack(sf::RenderWindow *, Current_stack *, float, float, Position, Position, Position, Position *,
                        const sf::Font &font, sf::Event*);

Position east_backtrack(sf::RenderWindow *, Current_stack *, float, float, Position, Position, Position, Position *,
                        const sf::Font &font, sf::Event*);

bool calculate_path(sf::RenderWindow *, Super_stack, float, float, const sf::Font &, sf::Event *);

int is_legal_start_end_point(Double_position_stack);

int main() {

    sf::Font font;
    font.loadFromFile("../arial.ttf");
    Super_stack maze_wire_stack;
    int isRead = read_maze(maze_wire_stack);
    if (isRead != 1) {
        printf("ERROR! Bad stuff happened while reading the file!\n");
    }
    else {
        // Display the maze in the console / terminal
        printf("Successfully read maze :)\n");
        printf("Rows: %d, Columns: %d\n", rows, columns);
        print_maze();

        sf::Event event;

        sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Maze navigation");
        window.setFramerateLimit(60);

        float entry_width = (float) WIDTH / ((float) rows + WALLSPACER);
        float entry_height = (float) HEIGHT / ((float) columns + WALLSPACER);

        window.clear(sf::Color::White);

        // Draws the starting grid.
        edit_grid(&window, entry_width, entry_height);
        window.display();

        bool mouse_placed = false;
        bool cheese_placed = false;

        bool part2isrunning = true;


        // Storing the current mouse and cheese coordinates in an array.
        Position points[2];

        while (window.isOpen()) {
            if (ISPART2) {
                // Part 2
                if (part2isrunning){
                    part2isrunning = calculate_path(&window, maze_wire_stack, entry_width, entry_height, font, &event);
                }
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed){
                        window.close();
                        goto end;
                    }
                }
            }
            else{
                // Part 1
                while (window.pollEvent(event)) {
                    // Use algorithm to find the path.
                    if (mouse_placed && cheese_placed) {
                        Dijkstras(points[0].x, points[0].y, points[1].x, points[1].y, &window, entry_width, entry_height,
                                  font, &event);
                        window.clear(sf::Color::White);
                        edit_grid(&window, entry_width, entry_height);
                        window.display();
                        memset(points, 0, 4);
                        mouse_placed = false;
                        cheese_placed = false;
                    }
                    // Switch case to handle the different events. Higher order is triggered first
                    switch (event.type) {

                        // "close requested" event: we close the window
                        case sf::Event::Closed: {
                            window.close();
                        }

                            // Mouse button released
                        case sf::Event::MouseButtonReleased: {
                            if (event.mouseButton.button == sf::Mouse::Left && !mouse_placed) {
                                sf::Vector2<int> mouse_coordinates = sf::Mouse::getPosition(window);
                                edit_grid(&window, entry_width, entry_height);
                                int *temp;
                                temp = get_position(mouse_coordinates.x, mouse_coordinates.y, entry_width, entry_height);
                                if (temp == nullptr) {
                                    printf("Failed to place mouse!\n");
                                    continue;
                                }
                                else {
                                    points[MOUSE_POS].x = temp[0];
                                    points[MOUSE_POS].y = temp[1];
                                    // Freeing the memory allocated in the get_position function.
                                    free(temp);
                                    // Mouse color is red.
                                    display_one_point(&window, points[MOUSE_POS].x, points[MOUSE_POS].y, entry_width,
                                                      entry_height, sf::Color::Red, false, font, &event);
                                    window.display();
                                    mouse_placed = true;
                                }
                            }
                                // You have to place the mouse out first, then the cheese.
                            else if (event.mouseButton.button == sf::Mouse::Right && !cheese_placed && mouse_placed) {
                                sf::Vector2<int> mouse_coordinates = sf::Mouse::getPosition(window);
                                edit_grid(&window, entry_width, entry_height);
                                int *temp;
                                temp = get_position(mouse_coordinates.x, mouse_coordinates.y, entry_width, entry_height);
                                if (temp == nullptr) {
                                    printf("Failed to place cheese!\n");
                                    continue;
                                }
                                else {
                                    points[CHEESE_POS].x = temp[0];
                                    points[CHEESE_POS].y = temp[1];
                                    // Freeing the memory allocated in the get_position function.
                                    free(temp);
                                    // Displaying the mouse and the cheese.
                                    // Mouse color is red.
                                    display_one_point(&window, points[MOUSE_POS].x, points[MOUSE_POS].y, entry_width,
                                                      entry_height, sf::Color::Red, false, font, &event);
                                    // Cheese color is yellow.
                                    display_one_point(&window, points[CHEESE_POS].x, points[CHEESE_POS].y, entry_width,
                                                      entry_height, sf::Color::Yellow, false, font, &event);

                                    window.display();

                                    cheese_placed = true;
                                }
                            }
                            else {
                                printf("Place the mouse first!\n");
                            }
                        }
                    }
                }
            }

        }
    }
    end:;
    return 0;
}

int is_legal_start_end_point(Double_position_stack points) {
    // Start or end position is NOT an obstacle
    if (maze[points.start.x][points.start.y] == OBSTACLE) {
        return 0;
    }
    else if (maze[points.end.x][points.end.y] == OBSTACLE) {
        return 0;
    }
    // Points are outside the maze
    else if (points.start.x + 1 >= rows + WALLSPACER
             || points.start.y + 1 >= columns + WALLSPACER
             || points.start.x - 1 < 0
             || points.start.y - 1 < 0) {
        return 0;
    }
    else if (points.end.x + 1 >= rows + WALLSPACER
               || points.end.y + 1 >= columns + WALLSPACER
               || points.end.x - 1 < 0
               || points.end.y - 1 < 0) {
        return 0;
    }
    else if (maze[points.start.x - 1][points.start.y] == OBSTACLE // W
               || maze[points.start.x - 1][points.start.y + 1] == OBSTACLE // SW
               || maze[points.start.x - 1][points.start.y - 1] == OBSTACLE // NW
               || maze[points.start.x][points.start.y + 1] == OBSTACLE   // S
               || maze[points.start.x][points.start.y - 1] == OBSTACLE   // N
               || maze[points.start.x + 1][points.start.y] == OBSTACLE   // E
               || maze[points.start.x + 1][points.start.y + 1] == OBSTACLE // SE
               || maze[points.start.x + 1][points.start.y - 1] == OBSTACLE) { // NE
        return 0;
    }
    else if (maze[points.end.x - 1][points.end.y] == OBSTACLE // W
               || maze[points.end.x - 1][points.end.y + 1] == OBSTACLE // SW
               || maze[points.end.x - 1][points.end.y - 1] == OBSTACLE // NW
               || maze[points.end.x][points.end.y + 1] == OBSTACLE   // S
               || maze[points.end.x][points.end.y - 1] == OBSTACLE   // N
               || maze[points.end.x + 1][points.end.y] == OBSTACLE   // E
               || maze[points.end.x + 1][points.end.y + 1] == OBSTACLE // SE
               || maze[points.end.x + 1][points.end.y - 1] == OBSTACLE) { // NE
        return 0;
    }

    return 1;
}

bool calculate_path(sf::RenderWindow *window, Super_stack points, float entry_width, float entry_height, const sf::Font &font, sf::Event* event)
{
    // No more points in the stack.
    if (points.is_empty()){
        printf("The wire input is empty, no more points in the stack\n");
        return false;
    }
    else{
        // Get the topmost point from the stack
        Double_position_stack points_ = points.pop();
        if (is_legal_start_end_point(points_)) {
            Dijkstras(points_.start.x, points_.start.y, points_.end.x, points_.end.y, window, entry_width, entry_height,
                      font, event);
            return true;
        }
        else {
            printf("Error! Unable to path to or from start nodes (%d,%d) or (%d,%d), since they are too close to another path. Skipping current path.\n",
                   points_.start.x, points_.start.y, points_.end.x, points_.end.y);
            return true;
        }
    }
}

void display_one_point(sf::RenderWindow *window, int x, int y, float entry_width, float entry_height, sf::Color color,
                       bool visit, const sf::Font &font, sf::Event* event) {
    sf::RectangleShape figure = sf::RectangleShape(sf::Vector2f((float) entry_width, (float) entry_height));
    figure.setFillColor(color);
    figure.setOutlineColor(sf::Color::Magenta);
    figure.setOutlineThickness(BORDER_THICKNESS_SQUARES);
    figure.setPosition(sf::Vector2f((float) x * entry_width, (float) y * entry_height));
    window->draw(figure);
    // Prevents hangs
    while (window->pollEvent(*event)) {
        // Should prevent hang
        if (event->type == sf::Event::Closed){
            window->close();
        }
    }
    if (visit) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(distance[x][y]));
        text.setCharacterSize((int) (std::min(entry_height, entry_width) * NUMBER_SIZE));
        text.setPosition((float) x * entry_width + NUMBER_POS * entry_width,
                         (float) y * entry_height + NUMBER_POS * entry_height);
        window->draw(text);
    }
}

// Sending in the coordinates gotten from the event, and returning the coordinates on the grid. Returns nullptr on OBSTACLE
int *get_position(int i, int j, float entry_width, float entry_height) {
    int *temp_points = (int *) malloc(DIMENSIONS * sizeof(int));

    // Good way to check the entry clicked:D
    int x = floor(i / entry_width);
    int y = floor(j / entry_height);

    // If the entry is an obstacle return nullptr.
    if (maze[x][y] == OBSTACLE) {
        printf("Mouse can not start from an obstacle!\n");
        free(temp_points);
        return nullptr;
    }
    else {
        temp_points[0] = x;
        temp_points[1] = y;
        return temp_points;
    }
}

void reset_display_with_visited(sf::RenderWindow *window, float entry_width, float entry_height, Position mouse,
                                Position cheese, const sf::Font &font, sf::Event *event) {
    for (int x = 0; x < rows + WALLSPACER; x++) {
        for (int y = 0; y < columns + WALLSPACER; y++) {
            if (maze[x][y] == WAY_BACK) {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::Green, false, font, event);
            }
            else if (x == mouse.x && y == mouse.y) {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::Red, false, font, event);
            }
            else if (x == cheese.x && y == cheese.y) {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::Yellow, false, font, event);
            }
            else if (visited[x][y] && (maze[x][y] != OBSTACLE)) {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::Blue, true, font, event);
            }
            else if (maze[x][y] == OBSTACLE) {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::Black, false, font, event);
            }
            else {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::White, false, font, event);
            }
        }
    }
}

void display_without_visited(sf::RenderWindow *window, float entry_width, float entry_height, Position mouse,
                             Position cheese, const sf::Font &font, sf::Event *event) {
    // Removing the visited mark.
    for (int x = 0; x < rows + WALLSPACER; x++) {
        for (int y = 0; y < columns + WALLSPACER; y++) {

            if (x == mouse.x && y == mouse.y) {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::Red, false, font, event);
            }
            else if (maze[x][y] == OBSTACLE) {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::Black, false, font, event);
            }
            else if (x == cheese.x && y == cheese.y) {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::Yellow, false, font, event);
            }
            else {
                display_one_point(window, x, y, entry_width, entry_height, sf::Color::White, false, font, event);
            }
        }
    }
}

// Checks if node north of current is free
bool north_node(Current_queue *queue, Position test_position, Position cheese, Position current_position) {
    if (!visited[test_position.x][test_position.y]) {
        // Set north as visited and increment distance then add to queue
        visited[test_position.x][test_position.y] = true;
        distance[test_position.x][test_position.y] = distance[current_position.x][current_position.y] + 1;
        queue->add_to_queue(test_position.x, test_position.y);
        if (test_position.x == cheese.x && test_position.y == cheese.y) {
            return false;
        }
    }
    return true;
}

bool south_node(Current_queue *queue, Position test_position, Position cheese, Position current_position) {
    if (!visited[test_position.x][test_position.y]) {
        // Set south as visited and increment distance then add to queue
        visited[test_position.x][test_position.y] = true;
        distance[test_position.x][test_position.y] = distance[current_position.x][current_position.y] + 1;
        if (test_position.x == cheese.x && test_position.y == cheese.y) {
            return false;
        }
        queue->add_to_queue(test_position.x, test_position.y);
    }
    return true;
}

bool west_node(Current_queue *queue, Position test_position, Position cheese, Position current_position) {
    if (!visited[test_position.x][test_position.y]) {
        // Set west as visited and increment distance then add to queue
        visited[test_position.x][test_position.y] = true;
        queue->add_to_queue(test_position.x, test_position.y);
        distance[test_position.x][test_position.y] = distance[current_position.x][current_position.y] + 1;
        if (test_position.x == cheese.x && test_position.y == cheese.y) {
            return false;
        }
    }
    return true;
}

bool east_node(Current_queue *queue, Position test_position, Position cheese, Position current_position) {
    if (!visited[test_position.x][test_position.y]) {
        // Set East as visited and increment distance then add to queue
        visited[test_position.x][test_position.y] = true;
        distance[test_position.x][test_position.y] = distance[current_position.x][current_position.y] + 1;
        queue->add_to_queue(test_position.x, test_position.y);
        if (test_position.x == cheese.x && test_position.y == cheese.y) {
            return false;
        }
    }
    return true;
}

Position
north_backtrack(sf::RenderWindow *window, Current_stack *stack, float entry_width, float entry_height, Position mouse,
                Position test_position, Position cheese, Position *current_position, const sf::Font &font, sf::Event* event) {
    // Check if current pos is mouse pos, then push current pos to stack.
    if ((current_position->x == mouse.x) && (current_position->y == mouse.y)) {
        stack->push_stack(current_position->x, current_position->y);
        Position stop;
        stop.x = mouse.x;
        stop.y = mouse.y;
        return stop;
    }
        // Check if new location is 1 lower than current pos, then push location to stack.
    else if (distance[test_position.x][test_position.y] == distance[current_position->x][current_position->y] - 1) {
        stack->push_stack(current_position->x, current_position->y);
        window->clear();
        maze[current_position->x][current_position->y] = WAY_BACK;
        reset_display_with_visited(window, entry_width, entry_height, mouse, cheese, font, event);
        return test_position;
    }
    Position fail;
    fail.x = INT_MIN;
    fail.y = INT_MIN;
    return fail;
}

Position
south_backtrack(sf::RenderWindow *window, Current_stack *stack, float entry_width, float entry_height, Position mouse,
                Position test_position, Position cheese, Position *current_position, const sf::Font &font, sf::Event* event) {
    if ((current_position->x == mouse.x) && (current_position->y == mouse.y)) {
        stack->push_stack(current_position->x, current_position->y);
        Position stop;
        stop.x = mouse.x;
        stop.y = mouse.y;
        return stop;
    }
    else if (distance[test_position.x][test_position.y] == distance[current_position->x][current_position->y] - 1) {
        stack->push_stack(current_position->x, current_position->y);
        window->clear();
        maze[current_position->x][current_position->y] = WAY_BACK;
        reset_display_with_visited(window, entry_width, entry_height, mouse, cheese, font, event);
        return test_position;
    }
    Position fail;
    fail.x = INT_MIN;
    fail.y = INT_MIN;
    return fail;
}

Position
west_backtrack(sf::RenderWindow *window, Current_stack *stack, float entry_width, float entry_height, Position mouse,
               Position test_position, Position cheese, Position *current_position, const sf::Font &font, sf::Event* event) {
    if ((current_position->x == mouse.x) && (current_position->y == mouse.y)) {
        stack->push_stack(current_position->x, current_position->y);
        Position stop;
        stop.x = mouse.x;
        stop.y = mouse.y;
        return stop;
    }
    else if (distance[test_position.x][test_position.y] == distance[current_position->x][current_position->y] - 1) {
        stack->push_stack(current_position->x, current_position->y);
        window->clear();
        maze[current_position->x][current_position->y] = WAY_BACK;
        reset_display_with_visited(window, entry_width, entry_height, mouse, cheese, font, event);
        return test_position;
    }
    Position fail;
    fail.x = INT_MIN;
    fail.y = INT_MIN;
    return fail;
}

Position
east_backtrack(sf::RenderWindow *window, Current_stack *stack, float entry_width, float entry_height, Position mouse,
               Position test_position, Position cheese, Position *current_position, const sf::Font &font, sf::Event * event) {
    if ((current_position->x == mouse.x) && (current_position->y == mouse.y)) {
        stack->push_stack(current_position->x, current_position->y);
        Position stop;
        stop.x = mouse.x;
        stop.y = mouse.y;
        return stop;
    }
    else if (distance[test_position.x][test_position.y] == distance[current_position->x][current_position->y] - 1) {
        stack->push_stack(current_position->x, current_position->y);
        window->clear();
        maze[current_position->x][current_position->y] = WAY_BACK;
        reset_display_with_visited(window, entry_width, entry_height, mouse, cheese, font, event);
        return test_position;
    }
    Position fail;
    fail.x = INT_MIN;
    fail.y = INT_MIN;
    return fail;
}

void Dijkstras(int start_x, int start_y, int stop_x, int stop_y, sf::RenderWindow *window, float entry_width,
               float entry_height, const sf::Font &font, sf::Event *event) {

    // Test print maze to console


    // Queue has to be malloced to circumference of a square (theoretical max queue size, by blocking the correct zones).
    // Set size to this.
    // This should be the lowest possible "max value" queue. Might need another +1 to not fill the queue
    int size = rows * 2 + columns * 2 + 1;
    printf("THE QUEUE SIZE IS %i!\n", size);
    Current_queue queue(size);

    // Initialize mouse position
    Position mouse = create_position();
    // Hardcode mouse pos
    mouse.x = start_x;
    mouse.y = start_y;

    // Initialize cheese pos
    Position cheese = create_position();
    // Hardcode cheese pos
    cheese.x = stop_x;
    cheese.y = stop_y;

    // Set mouse visited to true
    distance[mouse.x][mouse.y] = 0;
    visited[mouse.x][mouse.y] = true;

    // Announces start positions
    printf("Mouse is at (%d, %d) - Cheese is at (%d, %d) - Let the games begin!\n", mouse.x, mouse.y, cheese.x,
           cheese.y);


    // Place mouse in queue
    queue.add_to_queue(mouse.x, mouse.y);

    bool running = true;
    // DO DIJKSTRAS
    while (!queue.empty() && running) {
        while (window->pollEvent(*event)) {
            // Should prevent hang
            if (event->type == sf::Event::Closed){
                window->close();
                goto d_end;
            }
        }

        if (cheese.x == mouse.x && cheese.y == mouse.y) {
            printf("The mouse is already at the cheese!\n");
            break;
        }
        Position current_position = queue.remove_first_element_from_queue();

        Position test_position;

        std::map<int, bool> Checked;
        int randint;
        for (size_t i = 0; i < 4; ++i) {
            if (!running) {
                break;
            }
            // Pick random directions to check.
            int init_t = Checked.size();
            for (int t = init_t; t == init_t; t = Checked.size()) {
                randint = rand() % DIRECTIONS;
                if (Checked.find(randint) == Checked.end()) {
                    Checked[randint] = true;
                }
                else {
                    // pass
                }
            }
            switch (randint) {
                case 0:
                    // West
                    test_position = current_position;
                    if (ISPART2) {
                        // Checking if the entries around the child node is an obstacle.

                        // Check NW + SW diagonals (Or is it. Something messy with columns?)
                        if (maze[test_position.x - 1][test_position.y - 1] == OBSTACLE ||
                            (maze[test_position.x - 1][test_position.y + 1] == OBSTACLE)) {
                            break;
                        }
                        if (test_position.x - 2 < 0) {
                            // Outside of maze
                            //pass
                        }
                        else {
                            if ((maze[test_position.x - 2][test_position.y] == OBSTACLE)
                                || (maze[test_position.x - 2][test_position.y - 1] == OBSTACLE)
                                || (maze[test_position.x - 2][test_position.y + 1] == OBSTACLE)) {
                                // Obstacle in that direction - abort
                                break;
                            }
                        }
                    }
                    test_position.x = test_position.x - 1;
                    running = north_node(&queue, test_position, cheese, current_position);
                    break;
                case 1:
                    // East
                    test_position = current_position;
                    if (ISPART2) {
                        // Checking if the entries around the child node is an obstacle.

                        // Check ?? + ?? diagonals
                        if ((maze[test_position.x + 1][test_position.y - 1] == OBSTACLE)
                            || (maze[test_position.x + 1][test_position.y + 1] == OBSTACLE)) {
                            break;
                        }
                        // NOTE: >= due to rows not being zero indexed
                        if (test_position.x + 2 >= rows + WALLSPACER) {
                            // Outside of maze
                            // pass
                        }
                        else {
                            if ((maze[test_position.x + 2][test_position.y] == OBSTACLE)
                                || (maze[test_position.x + 2][test_position.y - 1] == OBSTACLE)
                                || (maze[test_position.x + 2][test_position.y + 1] == OBSTACLE)) {
                                // Obstacle in that direction - abort
                                break;
                            }
                        }
                    }
                    test_position.x = test_position.x + 1;
                    running = south_node(&queue, test_position, cheese, current_position);
                    break;
                case 2:
                    test_position = current_position;
                    // North
                    if (ISPART2) {
                        // Checking if the entries around the child node is an obstacle.
                        if ((maze[test_position.x - 1][test_position.y - 1] == OBSTACLE)
                            || (maze[test_position.x + 1][test_position.y - 1] == OBSTACLE)) {
                            break;
                        }
                        if (test_position.y - 2 < 0) {
                            // Outside of maze
                            //pass
                        }
                        else {
                            if ((maze[test_position.x][test_position.y - 2] == OBSTACLE)
                                || (maze[test_position.x - 1][test_position.y - 2] == OBSTACLE)
                                || (maze[test_position.x + 1][test_position.y - 2] == OBSTACLE)) {
                                break;
                            }
                        }

                    }
                    test_position.y = test_position.y - 1;
                    running = west_node(&queue, test_position, cheese, current_position);
                    break;
                case 3:
                    test_position = current_position;
                    // South
                    if (ISPART2) {
                        // Checking if the entries around the child node is an obstacle.
                        if ((maze[test_position.x + 1][test_position.y + 1] == OBSTACLE)
                            || (maze[test_position.x - 1][test_position.y + 1] == OBSTACLE)) {
                            break;
                        }
                        if (test_position.y + 2 >= columns + WALLSPACER) {
                            // Outside of maze
                            // pass
                        }
                        else {
                            if ((maze[test_position.x][test_position.y + 2] == OBSTACLE)
                                || (maze[test_position.x - 1][test_position.y + 2] == OBSTACLE)
                                || (maze[test_position.x + 1][test_position.y + 2] == OBSTACLE)) {
                                break;
                            }
                        }
                    }
                    test_position.y = test_position.y + 1;
                    running = east_node(&queue, test_position, cheese, current_position);
                    break;
            }
        }

        // Drawing visited(new generation of children from a parent).
        window->clear();
        reset_display_with_visited(window, entry_width, entry_height, mouse, cheese, font, event);
        window->display();
        sleep_until(system_clock::now() + VISITED_DELAY);
    }
    window->clear();
    reset_display_with_visited(window, entry_width, entry_height, mouse, cheese, font, event);
    display_one_point(window, cheese.x, cheese.y, entry_width, entry_height, sf::Color::Yellow, false, font, event);
    window->display();

    if (queue.empty() && !(cheese.x == mouse.x && cheese.y == mouse.y)) {
        {
            printf("no path exists from (%d, %d) to (%d, %d)\n", mouse.x, mouse.y, cheese.x, cheese.y);
            reset_maze();
        }

    }
    else {
        // Cheese has been found. Backtrack.

        // Create a new stack.
        Current_stack stack;

        Position current_position;

        current_position = cheese;

        // Used for checking valid backtrack node.
        Position temp = current_position;

        while ((current_position.x != mouse.x) || (current_position.y != mouse.y)) {
            while (window->pollEvent(*event)) {
                // Should prevent hang
                if (event->type == sf::Event::Closed){
                    window->close();
                    goto d_end;
                }
            }

            current_position = temp;
            window->display();
            sleep_until(system_clock::now() + MOUSE_DELAY);
            Position test_position;

            std::map<int, bool> Checked;
            int randint;
            // Picks random direction
            for (size_t i = 0; i < DIRECTIONS; ++i) {
                int init_t = (int) Checked.size();
                for (int t = init_t; t == init_t; t = (int) Checked.size()) {
                    randint = rand() % DIRECTIONS;
                    if (Checked.find(randint) == Checked.end()) {
                        Checked[randint] = true;
                    }
                    else {
                        // pass
                    }
                }
                switch (randint) {
                    case 0:
                        // Check North
                        test_position = current_position;
                        test_position.x = test_position.x - 1;
                        temp = north_backtrack(window, &stack, entry_width, entry_height, mouse, test_position, cheese,
                                               &current_position, font, event);
                        if (temp.y != INT_MIN && temp.x != INT_MIN) {
                            goto end;
                        }
                        break;
                    case 1:
                        // South
                        test_position = current_position;
                        test_position.x = test_position.x + 1;
                        temp = south_backtrack(window, &stack, entry_width, entry_height, mouse, test_position, cheese,
                                               &current_position, font, event);
                        if (temp.y != INT_MIN && temp.x != INT_MIN) {
                            goto end;
                        }
                        break;
                    case 2:
                        // West
                        test_position = current_position;
                        test_position.y = test_position.y - 1;
                        temp = west_backtrack(window, &stack, entry_width, entry_height, mouse, test_position, cheese,
                                              &current_position, font, event);
                        if (temp.y != INT_MIN && temp.x != INT_MIN) {
                            goto end;
                        }
                        break;
                    case 3:
                        // East
                        test_position = current_position;
                        test_position.y = test_position.y + 1;
                        temp = east_backtrack(window, &stack, entry_width, entry_height, mouse, test_position, cheese,
                                              &current_position, font, event);
                        if (temp.y != INT_MIN && temp.x != INT_MIN) {
                            goto end;
                        }
                        break;
                }
            }
            end:;
        }

        // Removing the visited and displaying the grid.
        window->clear();
        display_without_visited(window, entry_width, entry_height, mouse, cheese, font, event);
        window->display();

        // Should be back at the mouse now
        while (!stack.is_empty()) {
            current_position = stack.pop_stack();
            mouse.x = current_position.x;
            mouse.y = current_position.y;

            // Sets the mouse traveled path to a wall
            if (ISPART2){
                set_obstacle(mouse.x, mouse.y);
            }
            else {
                // Showing the mouse moving and then turing the olds position to an obstacle.
                window->clear();
                display_without_visited(window, entry_width, entry_height, mouse, cheese, font, event);
                window->display();
                sleep_until(system_clock::now() + MOUSE_DELAY);
                window->clear();
                display_without_visited(window, entry_width, entry_height, mouse, cheese, font, event);
                window->display();
            }
            visited[mouse.x][mouse.y] = true;
        }
        // NOM NOM!
        printf("Mouse is at (%d, %d) - Cheese is at (%d, %d) - NOMNOM?\n", mouse.x, mouse.y, cheese.x, cheese.y);
        // Extra credits:
        // Draw wall where mouse walked

        // Reset visited on NOTHING positions
        reset_maze();
    }
    window->clear(sf::Color::White);
    edit_grid(window, entry_width, entry_height);
    window->display();
    d_end:;
}

void reset_maze() {
    // Reset the maze after the mouse has found the cheese
    for (int x = 0; x < rows + WALLSPACER; ++x) {
        for (int y = 0; y < columns + WALLSPACER; ++y) {
            if (maze[x][y] != OBSTACLE) {
                visited[x][y] = false;
                maze[x][y] = NOTHING;
                distance[x][y] = INT_MIN;
            }
        }
    }
}


void edit_grid(sf::RenderTarget *window, float entry_width, float entry_height) {
    for (int x = 0; x < rows + WALLSPACER; x++) {
        sf::RectangleShape entry = sf::RectangleShape(sf::Vector2f((float) entry_width, (float) (entry_height)));
        for (int y = 0; y < (columns + WALLSPACER); y++) {
            if (maze[x][y] == NOTHING) {
                entry.setFillColor(sf::Color::White);
            }
            else {
                entry.setFillColor(sf::Color::Black);
            }
            entry.setOutlineColor(sf::Color::Magenta);
            entry.setOutlineThickness(BORDER_THICKNESS_SQUARES);
            entry.setPosition(sf::Vector2f((float) x * entry_width, (float) y * entry_height));

            window->draw(entry);
        }
    }
}


Position create_position() {
    auto *position = (Position *) malloc(sizeof(Position));
    return *position;
}


void alloc_maze() {
    // Wallspacer is to set the edges of the maze to walls
    maze = (int **) malloc((rows + WALLSPACER) * sizeof(int *));
    distance = (int **) malloc((rows + WALLSPACER) * sizeof(int *));
    visited = (int **) malloc((rows + WALLSPACER) * sizeof(int *));

    for (int i = 0; i < rows + WALLSPACER; ++i) {
        maze[i] = (int *) malloc((columns + WALLSPACER) * sizeof(int));
        distance[i] = (int *) malloc((columns + WALLSPACER) * sizeof(int));
        visited[i] = (int *) malloc((columns + WALLSPACER) * sizeof(int));
    }

    // Set row[0], col[0], row[END] and col[END] to obstacle, visited, and distance to INT_MAX
    for (int x = 0; x < rows + WALLSPACER; ++x) {
        for (int y = 0; y < columns + WALLSPACER; ++y) {

            if (x == 0 || x == rows + WALLSPACER - 1 || y == 0 || y == columns + WALLSPACER - 1) {
                // -1 to compensate for 0 indexing vs 1 indexing
                set_obstacle(x,y);
            }
            else {
                maze[x][y] = NOTHING;
                visited[x][y] = false;
            }

        }
    }
}


int read_maze(Super_stack stack) {
    // Input must be an int pointer pointer.
    // Reads maze from text file.
    // First row consist of two numbers, space separated
    // First number is columns
    // Second number is rows
    // Second row onward is <n , m>, and indicate x and y coordinates for obstacles
    // numbers in <> brackets, separated by " , "
    // Need to allocate space for surrounding walls (not shown in maze file)
    // MUST NOT include values outside of the maze size


    FILE *maze_file = fopen(FILE_PATH, "r");

    if (!maze_file) {
        printf("Failed to open file");
        return INT_MIN;
    }
    bool size_line = true;
    bool is_x = true;
    bool is_wall = true;
    bool waiting_for_new_start = true;
    int temporary_x = 0;    // Temporary starting point for x.
    int temporary_y = 0;    // Temporary starting point for y.
    int waiting_for_pair = 0;
    char c;
    char x_crd[MAXMAZESIZE] = {0};
    char y_crd[MAXMAZESIZE] = {0};

    // Read the file until the end.
    while (!feof(maze_file)) {
        c = getc(maze_file);

        // if sizeline
        // top line stuff
        // else if is wall
        // mid line stuff
        // else
        // point start end stuff

        if (size_line) {
            // Read Maze size logic
            // Scan for separators (flip the x to y).
            if (c == ' ') {
                is_x = false;
            }
                // Define the x and y size of the maze.
            else if (c == '\n') {
                rows = atoi(x_crd);
                columns = atoi(y_crd);

                // So that we can add stuff to the maze in the following segments.
                alloc_maze();

                // Clear cols and rows.
                memset(&x_crd[0], 0, MAXMAZESIZE);
                memset(&y_crd[0], 0, MAXMAZESIZE);
                size_line = false;
                is_x = true;
            }
        }
        else if (is_wall) {
            // Read OBSTACLE logic
            // Scan for separators (flip the x to y).
            if (c == ',' && is_x) {
                is_x = false; // Part logic for single wall points.
            }
                // First part of the set. Disable is_wall.
            else if (c == '{') {
                is_wall = false;
                is_x = true;
            }
                // Add blocking walls to the maze.
            else if (c == '\n') {
                // Checks if value is within the maze coordinates.
                if (atoi(x_crd) <= rows && atoi(x_crd) > 0 && atoi(y_crd) <= columns && atoi(y_crd) > 0) {
                    set_obstacle(atoi(x_crd),atoi(y_crd));

                    // Clear the reading input
                    memset(&x_crd[0], 0, MAXMAZESIZE);
                    memset(&y_crd[0], 0, MAXMAZESIZE);
                    is_x = true;
                }
                else {
                    printf("ERROR! Invalid obstacle data in input maze. Obstacle (%d, %d) is outside the maze (%d,%d)\n",
                           atoi(x_crd), atoi(y_crd), rows, columns);
                    fclose(maze_file);
                    return INT_MIN;
                }
            }
        }
        else {
            // Read start and end points

            // Scan for separators (flip the x to y).
            if (c == ',' && is_x) {
                is_x = false; // Part logic for single wall points.
            }
                // Start of a new point
            else if (c == '(') {
                // Workaround for starting a new pair point
                if (waiting_for_new_start) {
                    waiting_for_new_start = false;
                }
                is_x = true;
            }
                // This is the first part of the points pair, in other words the starting point.
            else if (c == ')' && !waiting_for_pair && !waiting_for_new_start) {
                // Get ready to read another part of x-y-coordinates as a point.
                if (atoi(x_crd) <= rows && atoi(x_crd) > 0 && atoi(y_crd) <= columns && atoi(y_crd) > 0) {
                    // Add start point to temp values as stack preparation.
                    temporary_x = atoi(x_crd);
                    temporary_y = atoi(y_crd);
                    waiting_for_pair = true;     // Prevents overwriting the temp values when the second point is being stored.

                    // Clear the reading input
                    memset(&x_crd[0], 0, MAXMAZESIZE);
                    memset(&y_crd[0], 0, MAXMAZESIZE);
                    is_x = true;
                }
                else {
                    printf("ERROR! Invalid starting point data in input maze. Starting point (%d, %d) is outside the maze (%d,%d)\n",
                           atoi(x_crd), atoi(y_crd), rows, columns);
                    fclose(maze_file);
                    return INT_MIN;
                }
            }
                // This is the other part of the points pair, in other words the ending point.
            else if (c == ')' && waiting_for_pair) {
                // Checks if value is within the maze coordinates.
                if (atoi(x_crd) <= rows && atoi(x_crd) > 0 && atoi(y_crd) <= columns && atoi(y_crd) > 0) {
                    // Push set of start and end points to stack.
                    stack.push(temporary_x, temporary_y, atoi(x_crd), atoi(y_crd));

                    // Clear the reading input
                    memset(&x_crd[0], 0, MAXMAZESIZE);
                    memset(&y_crd[0], 0, MAXMAZESIZE);

                    waiting_for_pair = false;
                    waiting_for_new_start = true;
                }
                else {
                    printf("ERROR! Invalid end point data in input maze. End point (%d, %d) is outside the maze (%d,%d)\n",
                           atoi(x_crd), atoi(y_crd), rows, columns);
                    fclose(maze_file);
                    return INT_MIN;
                }
            }
        }

        // If the char is a number, add to the current coordinate.
        // This applies to all 3 segments.
        if (c >= '0' && c <= '9') {
            if (is_x)
                x_crd[strlen(x_crd)] = c;
            else
                y_crd[strlen(y_crd)] = c;
        }
    }
    fclose(maze_file);
    return 1;
}

// Forces coordinate to be obstacle
void set_obstacle(int x, int y){
    maze[x][y] = OBSTACLE;
    visited[x][y] = true;
    distance[x][y] = INT_MAX;
}

void print_maze() {
    // Print the maze
    for (int x = 0; x < rows + WALLSPACER; ++x) {
        for (int y = 0; y < columns + WALLSPACER; ++y) {
            printf("%i", maze[x][y]);
        }
        printf("\n");
    }
    // Add some space
    printf("\n");
}
