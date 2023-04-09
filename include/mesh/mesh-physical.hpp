#ifndef MESH_PHYSICAL_HPP__
#define MESH_PHYSICAL_HPP__

#include <boost/phoenix/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdint>
#include <ostream>
#include <string>

namespace mesh {
namespace physical {
    using Dimension = std::size_t;
    using Tag       = std::size_t;
    using Name      = std::string;

    struct Entity {
        Dimension   dimension;
        Tag         tag;
        Name        name;

        friend std::ostream&
        operator<<(std::ostream& os, const Entity& e) {
            os  << e.dimension
                << " "
                << e.tag
                << " "
                << e.name
                ;
            return os;
        }

        auto operator<=>(const Entity&) const = default;
    };

    using Entities = std::vector<Entity>;
} // namespace physical
} // namespace mesh

BOOST_FUSION_ADAPT_STRUCT(
        mesh::physical::Entity,
        (mesh::physical::Dimension, dimension)
        (mesh::physical::Tag,       tag)
        (mesh::physical::Name,      name)
        );

namespace mesh {
namespace physical {
namespace decoder {
    namespace qi = boost::spirit::qi;

    template <typename Iterator>
    struct entity : qi::grammar<Iterator, Entity> {
        entity() : entity::base_type(rule) {
            rule = qi::skip(qi::space)[
                qi::int_ >> qi::int_ >> '"' >> *~qi::char_('"') >> '"'
            ];
        }
        qi::rule<Iterator, Entity> rule;
    };

    template <typename Iterator>
    struct entities : qi::grammar<Iterator, std::vector<Entity>> {
        entities() : entities::base_type(rule) {
            using boost::phoenix::ref;

            std::size_t count = 0;
            rule %= qi::skip(qi::eol)
                [   qi::lit("$PhysicalNames")
                >>  qi::omit[qi::int_[ref(count) = qi::_1]]
                >>  qi::repeat(ref(count))[entry]
                >>  qi::lit("$EndPhysicalNames")
                ]
                ;
        }
        entity<Iterator>                        entry;
        qi::rule<Iterator, std::vector<Entity>> rule;
    };
} // namespace decoder
} // namespace physical
} // namespace mesh

#endif //  MESH_PHYSICAL_HPP__
