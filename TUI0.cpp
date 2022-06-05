#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <chrono>
#include <thread>
#include <typeinfo>

struct Screen {
    int width;
    int height;
    
    Screen(int width, int height) { 
        this->width = width; 
        this->height = height; 
    }
};

template<typename T>
concept Printable_Object = 
    requires(T a) {
        { a } -> std::convertible_to<int>;
        { a } -> std::convertible_to<char>;
    };

template<Printable_Object T>
void render_screen(std::vector<std::vector<T>> frame_buffer) {
    
    for (size_t i = 0; i < frame_buffer.size(); i++) {
        for (size_t j = 0; j < frame_buffer[i].size(); j++) {
            std::cout << frame_buffer[i][j]; 
        }
        std::cout << std::endl; 
    }
}

template<Printable_Object T>
void double_buffer_TUI(Screen screen, T print_object) {

    static_assert(Printable_Object<T>);

    T default_print_object;
    if (typeid(print_object) == typeid(char)) 
        default_print_object = ' ';
    else if (typeid(print_object) == typeid(int))
        default_print_object = 0;


    std::vector<std::vector<T>> frame_buffer(screen.height);

    for (int i = 0; i < screen.height; i++) {
        for (int j = 0; j < screen.width; j++) {

            if (i == 0 || i == screen.height-1)
                frame_buffer[i].push_back(print_object);
            else if (j == 0 || j == screen.width-1)
                frame_buffer[i].push_back(print_object);
            else
                frame_buffer[i].push_back(default_print_object);

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            std::system("clear");
            render_screen(frame_buffer);
        }
    }
}

// Don't actually let someone pass in length to a function. You're asking for a 
// buffer overflow attack...
void print_buffer(char buffer[], int length)
{
    std::string out_str;

    for (int i = 0; i < length; i++) {
        out_str.push_back(buffer[i]);
    }
    
    std::cout << out_str << std::endl;
}

void lame_buffer_TUI() {
    char buffer[25];
    memset(buffer, ' ', 24);
    buffer[25] = '\0';

    buffer[0] = '@';
    int buffer_position = 0;

    while (buffer_position <= 20) {
        std::system("clear");
        print_buffer(buffer, 25);

        for (int i = 0; i < 300000000; i++)
            continue;

        buffer[buffer_position] = ' ';
        buffer_position += 5;
        buffer[buffer_position] = '@';
    }
}

int main() {
    lame_buffer_TUI();
    Screen screen(8, 10);
    double_buffer_TUI(screen, 8);
}
