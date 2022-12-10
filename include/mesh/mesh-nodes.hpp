#ifndef MESH_NODES_HPP__
#define MESH_NODES_HPP__

#include <boost/spirit/include/qi.hpp>
#include <geometry/geometry.hpp>
#include <vector>

namespace qi = boost::spirit::qi;
namespace mesh {
    template <typename Precision> using Node = geometry::d3::Point<Precision>;
namespace node {
namespace decoder {
    template <typename Iterator, typename Precision>
    struct node : qi::grammar<Iterator, std::vector<Precision>()> {
        node() : node::base_type(rule) {
            rule %= qi::skip(qi::space)[
                qi::repeat(3)[qi::float_]
            ];
        }

        qi::rule<Iterator, std::vector<Precision>()> rule;
    };
} // namespace decoder
} // namespace node
} // namespace mesh

namespace boost {
namespace spirit {
namespace traits {
    template <typename Precision>
    struct transform_attribute<mesh::Node<Precision>, std::vector<Precision>, qi::domain> {
        typedef std::vector<Precision> type;

        static type
        pre(mesh::Node<Precision>&) { return {}; }

        static void
        post(mesh::Node<Precision>& n, type const& xs) {
            n = mesh::Node<Precision>(xs.at(0), xs.at(1), xs.at(2));
        }

        static void
        fail(mesh::Node<Precision>&) {}
    };
} // namespace traits
} // namespace spirit
} // namespace boost

#endif //  MESH_NODES_HPP__
