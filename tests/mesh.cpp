#include <boost/spirit/include/qi.hpp>
#include <gtest/gtest.h>
#include <mesh/mesh.hpp>

TEST(Mesh, Grammar) {
    std::string ss =
        "$MeshFormat\n"
        "2.2 0 8\n"
        "$EndMeshFormat\n"
        "$PhysicalNames\n"
        "3\n"
        "0 1 \"First\"\n"
        "1 2 \"Second\"\n"
        "2 3 \"Third\"\n"
        "$EndPhysicalNames\n"
        "$Nodes\n"
        "6\n"
        "1 0.0 0.0 0.0\n"
        "2 1.0 0.0 0.0\n"
        "3 1.0 1.0 0.0\n"
        "4 0.0 1.0 0.0\n"
        "5 2.0 0.0 0.0\n"
        "6 2.0 1.0 0.0\n"
        "$EndNodes\n"
        "$Elements\n"
        "2\n"
        "1 3 2 99 2 1 2 3 4\n"
        "2 3 2 99 2 2 5 6 3\n"
        "$EndElements\n"
        ;
    mesh::node::Map<float> nodes = {
          {1, mesh::Node<float>(0.0f, 0.0f, 0.0f)}
        , {2, mesh::Node<float>(1.0f, 0.0f, 0.0f)}
        , {3, mesh::Node<float>(1.0f, 1.0f, 0.0f)}
        , {4, mesh::Node<float>(0.0f, 1.0f, 0.0f)}
        , {5, mesh::Node<float>(2.0f, 0.0f, 0.0f)}
        , {6, mesh::Node<float>(2.0f, 1.0f, 0.0f)}
    };
    mesh::element::Map elements = {
          {1, {mesh::element::Type::QUADRANGLE4, {99, 2}, {1, 2, 3, 4}}}
        , {2, {mesh::element::Type::QUADRANGLE4, {99, 2}, {2, 5, 6, 3}}}
    };
    mesh::physical::Entities entities = {
          {0, 1, "First"}
        , {1, 2, "Second"}
        , {2, 3, "Third"}
    };
    mesh::Mesh<float> expected = {{2.2, 0, 8}, entities, nodes, elements};
    mesh::Mesh<float> actual;

    using Iterator = std::string::iterator;

    mesh::decoder::parse<Iterator, float> grammar;
    bool result = boost::spirit::qi::parse(ss.begin(), ss.end(), grammar, actual);

    ASSERT_TRUE(result);
    EXPECT_EQ(actual.version, expected.version);

    ASSERT_EQ(actual.nodes.size(), expected.nodes.size());
    for (const auto& [k, v] : expected.nodes) {
        EXPECT_EQ(actual.nodes[k], v);
    }

    ASSERT_EQ(actual.physical, expected.physical);

    ASSERT_EQ(actual.elements.size(), expected.elements.size());
    for (const auto& [k, v] : expected.elements) {
        EXPECT_EQ(actual.elements[k], v);
    }
}

TEST(Mesh, Iterator) {
    std::string ss =
        "$MeshFormat\n"
        "2.2 0 8\n"
        "$EndMeshFormat\n"
        "$Nodes\n"
        "6\n"
        "1 0.0 0.0 0.0\n"
        "2 1.0 0.0 0.0\n"
        "3 1.0 1.0 0.0\n"
        "4 0.0 1.0 0.0\n"
        "5 2.0 0.0 0.0\n"
        "6 2.0 1.0 0.0\n"
        "$EndNodes\n"
        "$Elements\n"
        "2\n"
        "1 3 2 99 2 1 2 3 4\n"
        "2 3 2 99 2 2 5 6 3\n"
        "$EndElements\n"
        ;

    mesh::node::Map<float> nodes = {
          {1, mesh::Node<float>(0.0f, 0.0f, 0.0f)}
        , {2, mesh::Node<float>(1.0f, 0.0f, 0.0f)}
        , {3, mesh::Node<float>(1.0f, 1.0f, 0.0f)}
        , {4, mesh::Node<float>(0.0f, 1.0f, 0.0f)}
        , {5, mesh::Node<float>(2.0f, 0.0f, 0.0f)}
        , {6, mesh::Node<float>(2.0f, 1.0f, 0.0f)}
    };
    mesh::element::Map elements = {
          {1, {mesh::element::Type::QUADRANGLE4, {99, 2}, {1, 2, 3, 4}}}
        , {2, {mesh::element::Type::QUADRANGLE4, {99, 2}, {2, 5, 6, 3}}}
    };
    mesh::Mesh<float> expected  = {{2.2, 0, 8}, {}, nodes, elements};
    mesh::Mesh<float> actual    = mesh::decode<float>(ss.begin(), ss.end());
    EXPECT_EQ(actual.version, expected.version);

    ASSERT_EQ(actual.nodes.size(), expected.nodes.size());
    for (const auto& [k, v] : expected.nodes) {
        EXPECT_EQ(actual.nodes[k], v);
    }

    ASSERT_EQ(actual.physical, expected.physical);

    ASSERT_EQ(actual.elements.size(), expected.elements.size());
    for (const auto& [k, v] : expected.elements) {
        EXPECT_EQ(actual.elements[k], v);
    }
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
