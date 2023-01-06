#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <mesh/mesh.hpp>

TEST(Elements, Line) {
    std::string ss = "3 2 99 2 1 2 3 4";
    using Iterator = std::string::iterator;

    mesh::Element expected  = {mesh::element::Type::QUADRANGLE4, {99, 2}, {1, 2, 3, 4}};
    mesh::Element actual    = {};

    mesh::element::decoder::element<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}


int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
