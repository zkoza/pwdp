#include <print>

int main(int argc, const char* argv[])
{
    std::println("argc = {}", argc);
    for (int i = 0; i < argc; i++)
    {
        std::println("argv[{}] = {}", i, argv[i]);
    }
}
