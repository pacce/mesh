#ifndef MESH_ELEMENTS_HPP__
#define MESH_ELEMENTS_HPP__

#include <boost/phoenix/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <fstream>

#include "mesh-nodes.hpp"

namespace mesh {
namespace element {
    enum class Type {
          LINE2
        , TRIANGLE3
        , QUADRANGLE4
        , TETRATHEDRON4
        , HEXAHEDRON8
        , PRISM6
        , PYRAMID5
        , LINE3
        , TRIANGLE6
        , QUADRANGLE9
        , TETRAHEDRON10
        , HEXAHEDRON27
        , PRISM18
        , PYRAMID14
        , POINT1
        , QUADRANGLE8
        , HEXAHEDRON20
        , PRISM15
        , PYRAMID13
    };

    using Tag = std::size_t;
} // namespace element

    struct Element {
        element::Type               type;
        std::vector<element::Tag>   tags;
        std::vector<node::Number>   nodes;

        friend std::ostream&
        operator<<(std::ostream& os, const Element& e) {
            switch(e.type) {
                case element::Type::LINE2:
                { os << "2-node line"; break; }
                case element::Type::TRIANGLE3:
                { os << "3-node triangle"; break; }
                case element::Type::QUADRANGLE4:
                { os << "4-node quadrangle"; break; }
                case element::Type::TETRATHEDRON4:
                { os << "4-node tetrahedron"; break; }
                case element::Type::HEXAHEDRON8:
                { os << "8-node hexahedron"; break; }
                case element::Type::PRISM6:
                { os << "6-node prism"; break; }
                case element::Type::PYRAMID5:
                { os << "5-node pyramid"; break; }
                case element::Type::LINE3:
                { os << "3-node line"; break; }
                case element::Type::TRIANGLE6:
                { os << "6-node triangle"; break; }
                case element::Type::QUADRANGLE9:
                { os << "9-node quadrangle"; break; }
                case element::Type::TETRAHEDRON10:
                { os << "10-node tetrahedron"; break; }
                case element::Type::HEXAHEDRON27:
                { os << "27-node hexahedron"; break; }
                case element::Type::PRISM18:
                { os << "18-node prism"; break; }
                case element::Type::PYRAMID14:
                { os << "14-node pyramid"; break; }
                case element::Type::POINT1:
                { os << "1-node point"; break; }
                case element::Type::QUADRANGLE8:
                { os << "8-node quadrangle"; break; }
                case element::Type::HEXAHEDRON20:
                { os << "20-node hexahedron"; break; }
                case element::Type::PRISM15:
                { os << "15-node prism"; break; }
                case element::Type::PYRAMID13:
                { os << "13-node pyramid"; break; }
            }
            os << ", ";
            for (const element::Tag& tag : e.tags) { os << tag << " "; }
            os << ", ";
            for (const node::Number& node : e.nodes) { os << node << " "; }
            return os;
        }
    };
} // namespace mesh

BOOST_FUSION_ADAPT_STRUCT(
        mesh::Element,
        (mesh::element::Type,               type)
        (std::vector<mesh::element::Tag>,   tags)
        (std::vector<mesh::node::Number>,   nodes)
        );

namespace mesh {
namespace element {
namespace decoder {
    namespace qi = boost::spirit::qi;

    template <typename Iterator>
    struct tags : qi::grammar<Iterator, std::vector<Tag>> {
        tags() : tags::base_type(rule) {
            using boost::phoenix::ref;

            std::size_t tags = 0;
            rule    %= qi::skip(qi::space)
                    [  qi::omit[qi::int_[ref(tags) = qi::_1]]
                    >> qi::repeat(ref(tags))[qi::int_]
                    ]
                    ;
        }
        qi::rule<Iterator, std::vector<Tag>> rule;
    };

    template <typename Iterator>
    struct element : qi::grammar<Iterator, Element> {
        element() : element::base_type(rule) {
            rule    %= qi::skip(qi::space)
                    [  qi::int_
                    >> ts
                    >> qi::repeat[qi::int_]
                    ]
                    ;
            BOOST_SPIRIT_DEBUG_NODE(rule);
        }
        tags<Iterator>              ts;
        qi::rule<Iterator, Element> rule;
    };
} // namespace decoder
} // namespace element
} // namespace mesh

namespace boost {
namespace spirit {
namespace traits {
    template <>
    struct transform_attribute<mesh::element::Type, std::size_t, boost::spirit::qi::domain> {
        typedef std::size_t type;

        static type
        pre(mesh::element::Type&) { return {}; }

        static void
        post(mesh::element::Type& t, type const& size) {
            switch(size) {
                case  1: { t = mesh::element::Type::LINE2;          break; }
                case  2: { t = mesh::element::Type::TRIANGLE3;      break; }
                case  3: { t = mesh::element::Type::QUADRANGLE4;    break; }
                case  4: { t = mesh::element::Type::TETRATHEDRON4;  break; }
                case  5: { t = mesh::element::Type::HEXAHEDRON8;    break; }
                case  6: { t = mesh::element::Type::PRISM6;         break; }
                case  7: { t = mesh::element::Type::PYRAMID5;       break; }
                case  8: { t = mesh::element::Type::LINE3;          break; }
                case  9: { t = mesh::element::Type::TRIANGLE6;      break; }
                case 10: { t = mesh::element::Type::QUADRANGLE9;    break; }
                case 11: { t = mesh::element::Type::TETRAHEDRON10;  break; }
                case 12: { t = mesh::element::Type::HEXAHEDRON27;   break; }
                case 13: { t = mesh::element::Type::PRISM18;        break; }
                case 14: { t = mesh::element::Type::PYRAMID14;      break; }
                case 15: { t = mesh::element::Type::POINT1;         break; }
                case 16: { t = mesh::element::Type::QUADRANGLE8;    break; }
                case 17: { t = mesh::element::Type::HEXAHEDRON20;   break; }
                case 18: { t = mesh::element::Type::PRISM15;        break; }
                case 19: { t = mesh::element::Type::PYRAMID13;      break; }
            }
        }

        static void
        fail(mesh::element::Type&) {}
    };
} // namespace traits
} // namespace spirit
} // namespace boost
#endif // MESH_ELEMENTS_HPP__
