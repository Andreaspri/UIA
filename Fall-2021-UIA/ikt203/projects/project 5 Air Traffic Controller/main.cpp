#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "chrono"
#include "thread"
#include <gift_wrap_algorithm.h>
#include "queue.h"



#define DELTA_TIME 0
#define PLANE_RADIUS_1 1
#define FRAMERATE 60
#define ARRIVAL_RATE 10 // Timedelta for aircraft arrival

typedef struct showcase{
    sf::RenderWindow *window;
    game::Game_background *game_background;
    Queue *queue;
}Showcase;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

void GameThread(Showcase *);



int main(){


    Queue queue;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Air Traffic Controller - Aircraft radar");
    window.setKeyRepeatEnabled(false);
    window.setActive(false);
    window.setFramerateLimit(FRAMERATE);
    sf::Image icon;
    if (!icon.loadFromFile("assets/Aircraft.png")){
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Initializing the background class
    game::Game_background game_background(GREEN, &queue);

    // Setting up thread to render graphics
    auto *my_showcase = (Showcase *)malloc(sizeof(Showcase));
    my_showcase->game_background = &game_background;
    my_showcase->window = &window;
    my_showcase->queue = &queue;

    sf::Thread myThread(&GameThread, my_showcase);
    sf::Event event;

    myThread.launch();

    while (window.isOpen()){

        while (window.waitEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        //game_background.update_aircrafts(my_showcase->queue->get_all_positions());
        myThread.wait();
    }



    return 0;
}

// Drawing the background and changing the angle of the red searcher in a thread.
void GameThread(Showcase *my_showcase) {
    auto time = std::chrono::system_clock::now();
    auto start_time = time.time_since_epoch().count();
    long long time_step=0;
    while (my_showcase->window->isOpen()) {
        my_showcase->window->clear();
        my_showcase->window->draw(*my_showcase->game_background);
        my_showcase->window->display();
        auto time_passed = (time.time_since_epoch().count()-start_time)/10000000;
        time = std::chrono::system_clock::now();
        if (time_passed >= time_step)
        {
            my_showcase->queue->enQueue(newAircraft());
            time_step+=ARRIVAL_RATE;
        }
        Data convex = convex_hull(my_showcase->queue->get_all_positions(), my_showcase->queue->size(), my_showcase->queue->head(), my_showcase->queue->tail());
        if (convex.positions != nullptr){
            my_showcase->game_background->update_convex_hull(convex);
        }
        my_showcase->game_background->update_radar();
        my_showcase->queue->apply_changes_to_aircrafts();
        my_showcase->game_background->update_aircrafts(my_showcase->queue->get_all_positions(),my_showcase->queue->size(),my_showcase->queue->head());

        // TODO: Only do this sort if any plane has changed priority
        my_showcase->queue->sort();
        while (true)
        {
            if (!my_showcase->queue->is_empty())
            {
                if (my_showcase->queue->check_if_node_is_outside())
                    my_showcase->queue->deQueue();
                else
                    break;
            }
            else
                break;
        }



    }
}
