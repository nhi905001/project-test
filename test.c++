#include <iostream>
#include <cstring>

void copyData(const char* input) {
    char buffer[8];

    strcpy(buffer, input);

    std::cout << "Data: " << buffer << std::endl;
}

int main() {
    const char* data = "This string is much longer than 8 bytes";

    copyData(data);

    return 0;
}