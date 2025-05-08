#include <gtest/gtest.h>
#include <sstream>
#include <string>

extern void encode_buffered(std::istream&, std::ostream&);
extern bool decode_buffered(std::istream&, std::ostream&);
extern void encode_streaming(std::istream&, std::ostream&);
extern bool decode_streaming(std::istream&, std::ostream&);

TEST(Ascii85Test, EncodeBufferedBasic) {
    std::istringstream in("Hello");
    std::ostringstream out;
    encode_buffered(in, out);
    EXPECT_EQ(out.str(), "87cUR");
}

TEST(Ascii85Test, DecodeBufferedBasic) {
    std::istringstream in("87cUR");
    std::ostringstream out;
    bool success = decode_buffered(in, out);
    EXPECT_TRUE(success);
    EXPECT_EQ(out.str(), "Hello");
}

TEST(Ascii85Test, EncodeStreamingBasic) {
    std::istringstream in("Hello");
    std::ostringstream out;
    encode_streaming(in, out);
    EXPECT_EQ(out.str(), "87cUR");
}

TEST(Ascii85Test, DecodeStreamingBasic) {
    std::istringstream in("87cUR");
    std::ostringstream out;
    bool success = decode_streaming(in, out);
    EXPECT_TRUE(success);
    EXPECT_EQ(out.str(), "Hello");
}

TEST(Ascii85Test, DecodeInvalidChar) {
    std::istringstream in("87cU#");
    std::ostringstream out;
    bool success = decode_buffered(in, out);
    EXPECT_FALSE(success);
}

TEST(Ascii85Test, DecodeInvalidLength) {
    std::istringstream in("87c");
    std::ostringstream out;
    bool success = decode_buffered(in, out);
    EXPECT_FALSE(success);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}