#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <mesh/mesh.hpp>

TEST(Node, Line) {
    std::string ss = "1.0 0.0 0.0";
    mesh::Node<float> expected  = mesh::Node<float>::xaxis();
    mesh::Node<float> actual    = {};

    using Iterator = std::string::iterator;

    mesh::node::decoder::node<Iterator, float> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
