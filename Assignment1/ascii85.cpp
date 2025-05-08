#include <iostream>
#include <vector>
#include <string>
#include <cstring>

void encode_buffered(std::istream& in, std::ostream& out) {
    std::vector<char> buffer((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    size_t len = buffer.size();
    for (size_t i = 0; i < len; i += 4) {
        uint32_t value = 0;
        for (size_t j = 0; j < 4; ++j) {
            value <<= 8;
            if (i + j < len) value |= (unsigned char)buffer[i + j];
        }
        char output[5];
        for (int j = 4; j >= 0; --j) {
            output[j] = (value % 85) + 33;
            value /= 85;
        }
        out.write(output, 5);
    }
}

void encode_streaming(std::istream& in, std::ostream& out) {
    char block[4];
    while (in) {
        in.read(block, 4);
        size_t read = in.gcount();
        if (read == 0) break;
        uint32_t value = 0;
        for (size_t j = 0; j < 4; ++j) {
            value <<= 8;
            if (j < read) value |= (unsigned char)block[j];
        }
        char output[5];
        for (int j = 4; j >= 0; --j) {
            output[j] = (value % 85) + 33;
            value /= 85;
        }
        out.write(output, 5);
    }
}

bool decode_buffered(std::istream& in, std::ostream& out) {
    std::vector<char> buffer((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    size_t len = buffer.size();
    if (len % 5 != 0) return false;
    for (size_t i = 0; i < len; i += 5) {
        uint32_t value = 0;
        for (size_t j = 0; j < 5; ++j) {
            char c = buffer[i + j];
            if (c < 33 || c > 117) return false;
            value = value * 85 + (c - 33);
        }
        char output[4];
        for (int j = 3; j >= 0; --j) {
            output[j] = value & 0xFF;
            value >>= 8;
        }
        out.write(output, 4);
    }
    return true;
}

bool decode_streaming(std::istream& in, std::ostream& out) {
    char block[5];
    while (in) {
        in.read(block, 5);
        size_t read = in.gcount();
        if (read == 0) break;
        if (read != 5) return false;
        uint32_t value = 0;
        for (size_t j = 0; j < 5; ++j) {
            char c = block[j];
            if (c < 33 || c > 117) return false;
            value = value * 85 + (c - 33);
        }
        char output[4];
        for (int j = 3; j >= 0; --j) {
            output[j] = value & 0xFF;
            value >>= 8;
        }
        out.write(output, 4);
    }
    return true;
}

int main(int argc, char* argv[]) {
    bool decode = false;
    bool stream = false;

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-d") == 0) decode = true;
        else if (std::strcmp(argv[i], "-e") == 0) decode = false;
        else if (std::strcmp(argv[i], "--stream") == 0) stream = true;
        else {
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            return 1;
        }
    }

    if (decode) {
        bool success = stream ? decode_streaming(std::cin, std::cout) : decode_buffered(std::cin, std::cout);
        if (!success) {
            std::cerr << "Decoding error" << std::endl;
            return 1;
        }
    } else {
        if (stream) encode_streaming(std::cin, std::cout);
        else encode_buffered(std::cin, std::cout);
    }

    return 0;
}