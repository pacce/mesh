#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <mesh/mesh.hpp>

TEST(Physical, Entity) {
    std::string ss = "0 1 \"Entity\"";
    using Iterator = std::string::iterator;

    mesh::physical::Entity expected = {0, 1, "Entity"};
    mesh::physical::Entity actual   = {};

    mesh::physical::decoder::entity<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual, expected);
}

TEST(Physical, Entities) {
    std::string ss =
        "$PhysicalNames\n"
        "3\n"
        "0 1 \"First\"\n"
        "1 2 \"Second\"\n"
        "2 3 \"Third\"\n"
        "$EndPhysicalNames\n"
        ;
    using Iterator = std::string::iterator;

    mesh::physical::Entities expected = {
          {0, 1, "First"}
        , {1, 2, "Second"}
        , {2, 3, "Third"}
    };
    mesh::physical::Entities actual   = {};

    mesh::physical::decoder::entities<Iterator> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    ASSERT_EQ(actual.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
