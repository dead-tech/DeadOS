#include "Screen/Framebuffer.hpp"

int main()
{
    Screen::Framebuffer framebuffer;
    framebuffer.clear();
    char buffer[] = "Welcome to DeadOS";
    framebuffer.write_cstr(buffer);
    return 0;
}
