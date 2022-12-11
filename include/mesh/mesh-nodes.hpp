#ifndef MESH_NODES_HPP__
#define MESH_NODES_HPP__

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <geometry/geometry.hpp>
#include <map>
#include <vector>

namespace mesh {
    template <typename Precision> using Node = geometry::d3::Point<Precision>;
namespace node {
    template <typename Precision> using Pair    = std::pair<std::size_t, Node<Precision>>;
    template <typename Precision> using Map     = std::map<std::size_t, Node<Precision>>;
namespace decoder {
    namespace qi = boost::spirit::qi;
    template <typename Iterator, typename Precision>
    struct node : qi::grammar<Iterator, std::vector<Precision>> {
        node() : node::base_type(rule) {
            rule %= qi::skip(qi::space)[
                qi::repeat(3)[qi::float_]
            ];
        }

        qi::rule<Iterator, std::vector<Precision>> rule;
    };

    template <typename Iterator, typename Precision>
    struct line : qi::grammar<Iterator, Pair<Precision>> {
        line() : line::base_type(rule) {
            rule %= qi::skip(qi::space)[qi::int_ >> coordinates];
        }
        node<Iterator, Precision>           coordinates;
        qi::rule<Iterator, Pair<Precision>> rule;
    };

    template <typename Iterator, typename Precision>
    struct nodes : qi::grammar<Iterator, Map<Precision>()> {
        nodes() : nodes::base_type(rule) {
            rule %= qi::skip(qi::eol)
                [  qi::lit("$Nodes")
                >> qi::omit[qi::int_]
                >> *entries
                >> qi::lit("$EndNodes")
                ]
                ;
        }

        line<Iterator, Precision>               entries;
        qi::rule<Iterator, Map<Precision>()>    rule;
    };
} // namespace decoder
} // namespace node
} // namespace mesh

namespace boost {
namespace spirit {
namespace traits {
    template <typename Precision>
    struct transform_attribute<mesh::Node<Precision>, std::vector<Precision>, boost::spirit::qi::domain> {
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
