#ifndef MESH_VERSION_HPP__
#define MESH_VERSION_HPP__

#include <boost/spirit/include/qi.hpp>
#include <cstdint>

namespace mesh {
    template <typename Precision>
    struct Version {
        Precision   version;
        int32_t     format;
        int32_t     size;

        friend bool
        operator==(const Version<Precision>& lhs, const Version<Precision>& rhs) {
            return lhs.version  == rhs.version
                && lhs.format   == rhs.format
                && lhs.size     == rhs.size
                ;
        }

        friend bool
        operator!=(const Version<Precision>& lhs, const Version<Precision>& rhs) {
            return lhs.version  != rhs.version
                || lhs.format   != rhs.format
                || lhs.size     != rhs.size
                ;
        }

        friend std::ostream&
        operator<<(std::ostream& os, const Version<Precision>& v) {
            os  << v.version
                << " "
                << v.format
                << " "
                << v.size
                ;
            return os;
        }
    };
} // namespace mesh

BOOST_FUSION_ADAPT_TPL_STRUCT(
        (Precision),
        (mesh::Version) (Precision),
        (Precision, version)
        (int32_t,   format)
        (int32_t,   size)
        );

namespace mesh {
namespace version {
namespace decoder {
    namespace qi = boost::spirit::qi;

    template <typename Iterator, typename Precision>
    struct version_number : qi::grammar<Iterator, Precision> {
        version_number() : version_number::base_type(rule) {
            rule %= qi::float_;
        }

        qi::rule<Iterator, Precision> rule;
    };

    template <typename Iterator>
    struct file_type : qi::grammar<Iterator, int32_t> {
        file_type() : file_type::base_type(rule) {
            rule %= qi::int_(0);
        }

        qi::rule<Iterator, int32_t> rule;
    };

    template <typename Iterator>
    struct data_size : qi::grammar<Iterator, int32_t> {
        data_size() : data_size::base_type(rule) {
            rule %= qi::int_(8);
        }

        qi::rule<Iterator, int32_t> rule;
    };

    template <typename Iterator, typename Precision>
    struct format : qi::grammar<Iterator, Version<Precision>> {
        format() : format::base_type(rule) {
            rule %= qi::skip(qi::eol)
                [  qi::lit("$MeshFormat")
                >> qi::skip(qi::space)[version >> ftype >> dsize]
                >> qi::lit("$EndMeshFormat")
                ]
                ;
        }

        version_number<Iterator, Precision>     version;
        file_type<Iterator>                     ftype;
        data_size<Iterator>                     dsize;
        qi::rule<Iterator, Version<Precision>>  rule;
    };
} // namespace decoder
} // namespace version
} // namespace mesh

#endif // MESH_VERSION_HPP__
