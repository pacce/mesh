#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <mesh/mesh.hpp>

TEST(Version, Format) {
    std::string ss =
        "$MeshFormat\n"
        "2.2 0 8\n"
        "$EndMeshFormat\n"
        ;
    mesh::Version<float> expected  = {2.2, 0, 8};
    mesh::Version<float> actual    = {};

    using Iterator = std::string::iterator;

    mesh::version::decoder::format<Iterator, float> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
