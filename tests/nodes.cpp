#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <mesh/mesh.hpp>

TEST(Nodes, Node) {
    std::string ss = "1.0 0.0 0.0";
    mesh::Node<float> expected  = mesh::Node<float>::xaxis();
    mesh::Node<float> actual    = {};

    using Iterator = std::string::iterator;

    mesh::node::decoder::node<Iterator, float> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Nodes, Line) {
    std::string ss = "1 1.0 0.0 0.0";
    mesh::node::Pair<float> expected    = {1, mesh::Node<float>::xaxis()};
    mesh::node::Pair<float> actual;

    using Iterator = std::string::iterator;

    mesh::node::decoder::line<Iterator, float> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual.first, expected.first);
    EXPECT_EQ(actual.second, expected.second);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
