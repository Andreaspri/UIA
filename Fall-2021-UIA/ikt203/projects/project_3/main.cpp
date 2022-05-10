#include <iostream>
#include <library.h>
#include <Polygon.h>
#include <linked_list.h>
#include <graphics_handling.h>



// Declarations




int main()
{
    // Color definitions
    sf::Color line_color = sf::Color::Black;

    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Interactive Polygon Editor");


    // Create the image background
    sf::Image image;
    if (!(image.loadFromFile("../get.jpg")))
        std::cout << "Cannot load image";   //Load Image
    sf::Texture texture;
    texture.loadFromImage(image);  //Load Texture from image
    sf::Sprite sprite(texture);

    polygon_list stack_list = create_list();
    polygon_list selected_polygons = create_list();

    push_stack_to_list_element(&stack_list);


    window.setKeyRepeatEnabled(false);




    // Sound shenanigans
    sf::SoundBuffer buffer;
    buffer.loadFromFile("assets/heman.ogg");
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(5);
    sound.play();


    sf::VertexArray line(sf::LineStrip, 2);
    int last_point[2] = {0, 0};

    bool editing_state = false;
    Polygon edit_stack;
    int old_point[2];

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // Switch case to handle the different events. Higher order is triggered first
            switch (event.type)
            {

                // "close requested" event: we close the window
                case sf::Event::Closed:
                {
                    sound.stop();
                    window.close();
                }

                    // Mouse button released
                case sf::Event::MouseButtonReleased:
                {

                    // Left mouse released
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {



                        if (!editing_state){

                            //add_mouse_coordinates_to_stack(&stack_list, &window);

                            sf::Vector2<int>* coordinates = get_mouse_position(&window);


                            current_polygon(end_of_list(&stack_list))->add_coordinate(&coordinates->x, &coordinates->y);


                            //current_polygon(end_of_list(&stack_list))->last_point();

                            // Click logic:
                            // if size of vertex stack = 0
                            //  LMB: Push vertex point 0
                            // else
                            //  Next line (follow mouse)
                            //  LMB, push vertex point x to stack
                            //  RMB: pop last vertex point from stack and discard it
                            //  MMB: Pop all from vertex stack, push to "finished vertexes" linked list of structs.
                            // on every update, draw everything from finished vertexes + current vertex stack

                            // Rubber-banding start point helper-variables
                            last_point[0] = coordinates->x;
                            last_point[1] = coordinates->y;
                        }
                    }
                        // Right mouse released
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (!current_polygon(end_of_list(&stack_list))->is_empty()){
                            editing_state = false;
                            // These temp values is needed to store the return value.
                            int temp_coordinate[2] = {0};
                            int* temp_coordinate_;

                            // Deleting last point in the stack.

                            temp_coordinate_ = current_polygon(end_of_list(&stack_list))->delete_last_point(temp_coordinate);
                            if (temp_coordinate_ != nullptr){
                                // Storing the new last point in the stack.
                                last_point[0] = temp_coordinate_[0];
                                last_point[1] = temp_coordinate_[1];
                            }
                        }

                        else if (editing_state){
                            editing_state = false;
                        }
                        else {
                            sf::Vector2<int> coordinates = sf::Mouse::getPosition(window);
                            if(point_clicked(&stack_list, coordinates.x, coordinates.y, old_point))
                            {
                                edit_stack = point_clicked_helper(&stack_list, coordinates.x, coordinates.y, old_point);
                                editing_state = true;
                            }

                        }

                    }
                        // Middle mouse released
                    else if (event.mouseButton.button == sf::Mouse::Middle)
                    {
                        editing_state = false;

                        sf::Vector2<int> mouse_coordinates = sf::Mouse::getPosition(window);
                        if(current_polygon(end_of_list(&stack_list))->is_empty())
                            check_if_inside(&stack_list, &selected_polygons, mouse_coordinates);
                        else
                        {
                            int temp_coordinates[2];
                            int* temp = current_polygon(end_of_list(&stack_list))->first_point(temp_coordinates);
                            current_polygon(end_of_list(&stack_list))->add_coordinate(&temp[0], &temp[1]);
                            add_empty_list_node(&stack_list);
                        }

                    }
                }

                // Default event - Any other event - Don't care - Break out of the switch
                default:
                    break;

            }
        }
        window.clear();
        window.draw(sprite);
        if (!current_polygon(end_of_list(&stack_list))->is_empty() && !editing_state){
            // Updating the last line when we move the mouse.
            sf::Vector2<int> mouse_coordinates = sf::Mouse::getPosition(window);
            line[0].position = sf::Vector2f((float)last_point[0], (float)last_point[1]);
            line[0].color = line_color;
            line[1].position = sf::Vector2f((float)mouse_coordinates.x, (float)mouse_coordinates.y);
            line[1].color = line_color;
            window.draw(line);
        }
        else if (editing_state){
            sf::Vector2<int> mouse_coordinates = sf::Mouse::getPosition(window);
            edit_point(edit_stack.get_polygon(), old_point[0], old_point[1], mouse_coordinates.x, mouse_coordinates.y);
            old_point[0] = mouse_coordinates.x;
            old_point[1] = mouse_coordinates.y;
        }
        if (!list_is_empty(&selected_polygons))
            draw_all_selected_polygons(&selected_polygons, &window);
        draw_all_polygons(&stack_list, &window);



        window.display();
    }

    return 0;
}
