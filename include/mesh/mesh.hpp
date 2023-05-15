#ifndef MESH_HPP__
#define MESH_HPP__

#include <boost/spirit/include/qi.hpp>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>

#include "mesh-elements.hpp"
#include "mesh-nodes.hpp"
#include "mesh-physical.hpp"
#include "mesh-version.hpp"

namespace mesh {
    template <typename Precision>
    struct Mesh {
        mesh::Version<Precision>            version;
        std::optional<physical::Entities>   physical;
        mesh::node::Map<Precision>          nodes;
        mesh::element::Map                  elements;
    };
} // namespace mesh

BOOST_FUSION_ADAPT_TPL_STRUCT(
        (Precision),
        (mesh::Mesh) (Precision),
        (mesh::Version<Precision>,                  version)
        (std::optional<mesh::physical::Entities>,   physical)
        (mesh::node::Map<Precision>,                nodes)
        (mesh::element::Map,                        elements)
        );

namespace mesh {
namespace decoder {
    namespace qi = boost::spirit::qi;

    template <typename Iterator, typename Precision>
    struct parse : qi::grammar<Iterator, Mesh<Precision>> {
        parse() : parse::base_type(rule) {
            rule    %= version
                    >> -physical
                    >> node
                    >> elements
                    ;
        }

        mesh::version::decoder::format<Iterator, Precision> version;
        mesh::physical::decoder::entities<Iterator>         physical;
        mesh::node::decoder::nodes<Iterator, Precision>     node;
        mesh::element::decoder::elements<Iterator>          elements;

        qi::rule<Iterator, Mesh<Precision>>                 rule;
    };
}

    template <typename Precision, typename Iterator>
    Mesh<Precision>
    decode(const Iterator begin, const Iterator end) {
        mesh::Mesh<Precision> msh;

        mesh::decoder::parse<Iterator, Precision> grammar;
        if (!boost::spirit::qi::parse(begin, end, grammar, msh)) {
            throw std::runtime_error("failed to decode mesh file");
        }
        return msh;
    }

    template <typename Precision>
    Mesh<Precision>
    decode(const std::filesystem::path& path) {
        std::ifstream handle(path);
        if (!handle.is_open()) { throw std::runtime_error("could not open mesh file"); }
        handle.unsetf(std::ios::skipws);

        return mesh::decode<Precision>(boost::spirit::istream_iterator(handle), {});
    }
} // namespace mesh

#endif // MESH_HPP__
