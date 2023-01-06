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
          LINE2         =  1
        , TRIANGLE3     =  2
        , QUADRANGLE4   =  3
        , TETRATHEDRON4 =  4
        , HEXAHEDRON8   =  5
        , PRISM6        =  6
        , PYRAMID5      =  7
        , LINE3         =  8
        , TRIANGLE6     =  9
        , QUADRANGLE9   = 10
        , TETRAHEDRON10 = 11
        , HEXAHEDRON27  = 12
        , PRISM18       = 13
        , PYRAMID14     = 14
        , POINT1        = 15
        , QUADRANGLE8   = 16
        , HEXAHEDRON20  = 17
        , PRISM15       = 18
        , PYRAMID13     = 91
    };

    using Tag   = std::size_t;
    using Tags  = std::vector<Tag>;
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

        friend bool
        operator==(const Element& lhs, const Element& rhs) {
            auto tags = [](const element::Tags& lh, const element::Tags& rh) {
                if (lh.size() == rh.size()) {
                    for (std::size_t i = 0; i < lh.size(); i++) {
                        if (lh[i] != rh[i]) { return false; }
                    }
                } else {
                    return false;
                }
                return true;
            };

            auto nodes = [](const std::vector<node::Number>& lh, const std::vector<node::Number>& rh) {
                if (lh.size() == rh.size()) {
                    for (std::size_t i = 0; i < lh.size(); i++) {
                        if (lh[i] != rh[i]) { return false; }
                    }
                } else {
                    return false;
                }
                return true;
            };
            return lhs.type == rhs.type
                && tags(lhs.tags, rhs.tags)
                && nodes(lhs.nodes, rhs.nodes)
                ;
        }

        friend bool
        operator!=(const Element& lhs, const Element& rhs) {
            return !(lhs == rhs);
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
        }
        tags<Iterator>              ts;
        qi::rule<Iterator, Element> rule;
    };
} // namespace decoder
} // namespace element
} // namespace mesh

#endif // MESH_ELEMENTS_HPP__
