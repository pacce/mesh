#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <mesh/mesh.hpp>

TEST(Element, Line2) {
    std::string ss = "1 2 99 2 1 2";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::LINE2, {99, 2}, {1, 2}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Triangle3) {
    std::string ss = "2 2 99 2 1 2 3";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::TRIANGLE3, {99, 2}, {1, 2, 3}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Quadrangle4) {
    std::string ss = "3 2 99 2 1 2 3 4";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::QUADRANGLE4, {99, 2}, {1, 2, 3, 4}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Tetrahedron4) {
    std::string ss = "4 2 99 2 1 2 3 4";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::TETRATHEDRON4, {99, 2}, {1, 2, 3, 4}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Hexahedron8) {
    std::string ss = "5 2 99 2 1 2 3 4 5 6 7 8";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::HEXAHEDRON8, {99, 2}, {1, 2, 3, 4, 5, 6, 7, 8}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Prism6) {
    std::string ss = "6 2 99 2 1 2 3 4 5 6";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::PRISM6, {99, 2}, {1, 2, 3, 4, 5, 6}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Pyramid5) {
    std::string ss = "7 2 99 2 1 2 3 4 5";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::PYRAMID5, {99, 2}, {1, 2, 3, 4, 5}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Line3) {
    std::string ss = "8 2 99 2 1 2 3";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::LINE3, {99, 2}, {1, 2, 3}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Triangle6) {
    std::string ss = "9 2 99 2 1 2 3 4 5 6";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::TRIANGLE6, {99, 2}, {1, 2, 3, 4, 5, 6}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Quadrangle9) {
    std::string ss = "10 2 99 2 1 2 3 4 5 6 7 8 9";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::QUADRANGLE9, {99, 2}, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Element, Tetrahedron10) {
    std::string ss = "11 2 99 2 1 2 3 4 5 6 7 8 9 10";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::TETRAHEDRON10, {99, 2}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Elements, Parse) {
    std::string ss = 
        "$Elements\n"
        "2\n"
        "1 3 2 99 2 1 2 3 4\n"
        "2 3 2 99 2 2 5 6 3\n"
        "$EndElements\n"
        ;
    mesh::element::Map expected = {
          {1, {mesh::element::Type::QUADRANGLE4, {99, 2}, {1, 2, 3, 4}}}
        , {2, {mesh::element::Type::QUADRANGLE4, {99, 2}, {2, 5, 6, 3}}}
    };
    mesh::element::Map actual;

    using Iterator = std::string::iterator;

    mesh::element::decoder::elements<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    ASSERT_EQ(actual.size(), expected.size());
    for (const auto& [k, v] : expected) {
        EXPECT_EQ(actual[k], v);
    }
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
