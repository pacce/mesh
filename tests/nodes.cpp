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

TEST(Nodes, Lines) {
    std::string ss = 
        "$Nodes\n"
        "1 0.0 0.0 0.0\n"
        "2 1.0 0.0 0.0\n"
        "3 1.0 1.0 0.0\n"
        "4 0.0 1.0 0.0\n"
        "5 2.0 0.0 0.0\n"
        "6 2.0 1.0 0.0\n"
        "$EndNodes"
        ;
    mesh::node::Map<float> expected = {
          {1, mesh::Node<float>(0.0f, 0.0f, 0.0f)}
        , {2, mesh::Node<float>(1.0f, 0.0f, 0.0f)}
        , {3, mesh::Node<float>(1.0f, 1.0f, 0.0f)}
        , {4, mesh::Node<float>(0.0f, 1.0f, 0.0f)}
        , {5, mesh::Node<float>(2.0f, 0.0f, 0.0f)}
        , {6, mesh::Node<float>(2.0f, 1.0f, 0.0f)}
    };
    mesh::node::Map<float> actual;

    using Iterator = std::string::iterator;

    mesh::node::decoder::nodes<Iterator, float> grammar;
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
