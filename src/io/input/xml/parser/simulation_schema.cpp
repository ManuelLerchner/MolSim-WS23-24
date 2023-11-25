// Copyright (c) 2005-2023 Code Synthesis.
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis gives permission
// to link this program with the Xerces-C++ library (or with modified
// versions of Xerces-C++ that use the same license as Xerces-C++), and
// distribute linked combinations including the two. You must obey the GNU
// General Public License version 2 in all respects for all of the code
// used other than Xerces-C++. If you modify this copy of the program, you
// may extend this exception to your version of the program, but you are
// not obligated to do so. If you do not wish to do so, delete this
// exception statement from your version.
//
// Furthermore, Code Synthesis makes a special exception for the Free/Libre
// and Open Source Software (FLOSS) which is described in the accompanying
// FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include "simulation_schema.h"

#include <xsd/cxx/pre.hxx>

// DoubleVec3
//

const DoubleVec3::x_type& DoubleVec3::x() const { return this->x_.get(); }

DoubleVec3::x_type& DoubleVec3::x() { return this->x_.get(); }

void DoubleVec3::x(const x_type& x) { this->x_.set(x); }

const DoubleVec3::y_type& DoubleVec3::y() const { return this->y_.get(); }

DoubleVec3::y_type& DoubleVec3::y() { return this->y_.get(); }

void DoubleVec3::y(const y_type& x) { this->y_.set(x); }

const DoubleVec3::z_type& DoubleVec3::z() const { return this->z_.get(); }

DoubleVec3::z_type& DoubleVec3::z() { return this->z_.get(); }

void DoubleVec3::z(const z_type& x) { this->z_.set(x); }

// IntVec3
//

const IntVec3::dimx_type& IntVec3::dimx() const { return this->dimx_.get(); }

IntVec3::dimx_type& IntVec3::dimx() { return this->dimx_.get(); }

void IntVec3::dimx(const dimx_type& x) { this->dimx_.set(x); }

const IntVec3::dimy_type& IntVec3::dimy() const { return this->dimy_.get(); }

IntVec3::dimy_type& IntVec3::dimy() { return this->dimy_.get(); }

void IntVec3::dimy(const dimy_type& x) { this->dimy_.set(x); }

const IntVec3::dimz_type& IntVec3::dimz() const { return this->dimz_.get(); }

IntVec3::dimz_type& IntVec3::dimz() { return this->dimz_.get(); }

void IntVec3::dimz(const dimz_type& x) { this->dimz_.set(x); }

// configuration
//

const configuration::fps_optional& configuration::fps() const { return this->fps_; }

configuration::fps_optional& configuration::fps() { return this->fps_; }

void configuration::fps(const fps_type& x) { this->fps_.set(x); }

void configuration::fps(const fps_optional& x) { this->fps_ = x; }

const configuration::video_length_optional& configuration::video_length() const { return this->video_length_; }

configuration::video_length_optional& configuration::video_length() { return this->video_length_; }

void configuration::video_length(const video_length_type& x) { this->video_length_.set(x); }

void configuration::video_length(const video_length_optional& x) { this->video_length_ = x; }

const configuration::delta_t_optional& configuration::delta_t() const { return this->delta_t_; }

configuration::delta_t_optional& configuration::delta_t() { return this->delta_t_; }

void configuration::delta_t(const delta_t_type& x) { this->delta_t_.set(x); }

void configuration::delta_t(const delta_t_optional& x) { this->delta_t_ = x; }

const configuration::end_time_optional& configuration::end_time() const { return this->end_time_; }

configuration::end_time_optional& configuration::end_time() { return this->end_time_; }

void configuration::end_time(const end_time_type& x) { this->end_time_.set(x); }

void configuration::end_time(const end_time_optional& x) { this->end_time_ = x; }

const configuration::cuboid_sequence& configuration::cuboid() const { return this->cuboid_; }

configuration::cuboid_sequence& configuration::cuboid() { return this->cuboid_; }

void configuration::cuboid(const cuboid_sequence& s) { this->cuboid_ = s; }

// cuboid
//

const cuboid::position_type& cuboid::position() const { return this->position_.get(); }

cuboid::position_type& cuboid::position() { return this->position_.get(); }

void cuboid::position(const position_type& x) { this->position_.set(x); }

void cuboid::position(::std::unique_ptr<position_type> x) { this->position_.set(std::move(x)); }

const cuboid::grid_dim_type& cuboid::grid_dim() const { return this->grid_dim_.get(); }

cuboid::grid_dim_type& cuboid::grid_dim() { return this->grid_dim_.get(); }

void cuboid::grid_dim(const grid_dim_type& x) { this->grid_dim_.set(x); }

void cuboid::grid_dim(::std::unique_ptr<grid_dim_type> x) { this->grid_dim_.set(std::move(x)); }

const cuboid::grid_spacing_type& cuboid::grid_spacing() const { return this->grid_spacing_.get(); }

cuboid::grid_spacing_type& cuboid::grid_spacing() { return this->grid_spacing_.get(); }

void cuboid::grid_spacing(const grid_spacing_type& x) { this->grid_spacing_.set(x); }

const cuboid::temperature_type& cuboid::temperature() const { return this->temperature_.get(); }

cuboid::temperature_type& cuboid::temperature() { return this->temperature_.get(); }

void cuboid::temperature(const temperature_type& x) { this->temperature_.set(x); }

const cuboid::mass_type& cuboid::mass() const { return this->mass_.get(); }

cuboid::mass_type& cuboid::mass() { return this->mass_.get(); }

void cuboid::mass(const mass_type& x) { this->mass_.set(x); }

const cuboid::velocity_type& cuboid::velocity() const { return this->velocity_.get(); }

cuboid::velocity_type& cuboid::velocity() { return this->velocity_.get(); }

void cuboid::velocity(const velocity_type& x) { this->velocity_.set(x); }

void cuboid::velocity(::std::unique_ptr<velocity_type> x) { this->velocity_.set(std::move(x)); }

const cuboid::type_type& cuboid::type() const { return this->type_.get(); }

cuboid::type_type& cuboid::type() { return this->type_.get(); }

void cuboid::type(const type_type& x) { this->type_.set(x); }

#include <xsd/cxx/xml/dom/parsing-source.hxx>

// DoubleVec3
//

DoubleVec3::DoubleVec3(const x_type& x, const y_type& y, const z_type& z) : ::xml_schema::type(), x_(x, this), y_(y, this), z_(z, this) {}

DoubleVec3::DoubleVec3(const DoubleVec3& x, ::xml_schema::flags f, ::xml_schema::container* c)
    : ::xml_schema::type(x, f, c), x_(x.x_, f, this), y_(x.y_, f, this), z_(x.z_, f, this) {}

DoubleVec3::DoubleVec3(const ::xercesc::DOMElement& e, ::xml_schema::flags f, ::xml_schema::container* c)
    : ::xml_schema::type(e, f | ::xml_schema::flags::base, c), x_(this), y_(this), z_(this) {
    if ((f & ::xml_schema::flags::base) == 0) {
        ::xsd::cxx::xml::dom::parser<char> p(e, true, false, false);
        this->parse(p, f);
    }
}

void DoubleVec3::parse(::xsd::cxx::xml::dom::parser<char>& p, ::xml_schema::flags f) {
    for (; p.more_content(); p.next_content(false)) {
        const ::xercesc::DOMElement& i(p.cur_element());
        const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

        // x
        //
        if (n.name() == "x" && n.namespace_().empty()) {
            if (!x_.present()) {
                this->x_.set(x_traits::create(i, f, this));
                continue;
            }
        }

        // y
        //
        if (n.name() == "y" && n.namespace_().empty()) {
            if (!y_.present()) {
                this->y_.set(y_traits::create(i, f, this));
                continue;
            }
        }

        // z
        //
        if (n.name() == "z" && n.namespace_().empty()) {
            if (!z_.present()) {
                this->z_.set(z_traits::create(i, f, this));
                continue;
            }
        }

        break;
    }

    if (!x_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("x", "");
    }

    if (!y_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("y", "");
    }

    if (!z_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("z", "");
    }
}

DoubleVec3* DoubleVec3::_clone(::xml_schema::flags f, ::xml_schema::container* c) const { return new class DoubleVec3(*this, f, c); }

DoubleVec3& DoubleVec3::operator=(const DoubleVec3& x) {
    if (this != &x) {
        static_cast< ::xml_schema::type&>(*this) = x;
        this->x_ = x.x_;
        this->y_ = x.y_;
        this->z_ = x.z_;
    }

    return *this;
}

DoubleVec3::~DoubleVec3() {}

// IntVec3
//

IntVec3::IntVec3(const dimx_type& dimx, const dimy_type& dimy, const dimz_type& dimz)
    : ::xml_schema::type(), dimx_(dimx, this), dimy_(dimy, this), dimz_(dimz, this) {}

IntVec3::IntVec3(const IntVec3& x, ::xml_schema::flags f, ::xml_schema::container* c)
    : ::xml_schema::type(x, f, c), dimx_(x.dimx_, f, this), dimy_(x.dimy_, f, this), dimz_(x.dimz_, f, this) {}

IntVec3::IntVec3(const ::xercesc::DOMElement& e, ::xml_schema::flags f, ::xml_schema::container* c)
    : ::xml_schema::type(e, f | ::xml_schema::flags::base, c), dimx_(this), dimy_(this), dimz_(this) {
    if ((f & ::xml_schema::flags::base) == 0) {
        ::xsd::cxx::xml::dom::parser<char> p(e, true, false, false);
        this->parse(p, f);
    }
}

void IntVec3::parse(::xsd::cxx::xml::dom::parser<char>& p, ::xml_schema::flags f) {
    for (; p.more_content(); p.next_content(false)) {
        const ::xercesc::DOMElement& i(p.cur_element());
        const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

        // dimx
        //
        if (n.name() == "dimx" && n.namespace_().empty()) {
            if (!dimx_.present()) {
                this->dimx_.set(dimx_traits::create(i, f, this));
                continue;
            }
        }

        // dimy
        //
        if (n.name() == "dimy" && n.namespace_().empty()) {
            if (!dimy_.present()) {
                this->dimy_.set(dimy_traits::create(i, f, this));
                continue;
            }
        }

        // dimz
        //
        if (n.name() == "dimz" && n.namespace_().empty()) {
            if (!dimz_.present()) {
                this->dimz_.set(dimz_traits::create(i, f, this));
                continue;
            }
        }

        break;
    }

    if (!dimx_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("dimx", "");
    }

    if (!dimy_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("dimy", "");
    }

    if (!dimz_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("dimz", "");
    }
}

IntVec3* IntVec3::_clone(::xml_schema::flags f, ::xml_schema::container* c) const { return new class IntVec3(*this, f, c); }

IntVec3& IntVec3::operator=(const IntVec3& x) {
    if (this != &x) {
        static_cast< ::xml_schema::type&>(*this) = x;
        this->dimx_ = x.dimx_;
        this->dimy_ = x.dimy_;
        this->dimz_ = x.dimz_;
    }

    return *this;
}

IntVec3::~IntVec3() {}

// configuration
//

configuration::configuration() : ::xml_schema::type(), fps_(this), video_length_(this), delta_t_(this), end_time_(this), cuboid_(this) {}

configuration::configuration(const configuration& x, ::xml_schema::flags f, ::xml_schema::container* c)
    : ::xml_schema::type(x, f, c),
      fps_(x.fps_, f, this),
      video_length_(x.video_length_, f, this),
      delta_t_(x.delta_t_, f, this),
      end_time_(x.end_time_, f, this),
      cuboid_(x.cuboid_, f, this) {}

configuration::configuration(const ::xercesc::DOMElement& e, ::xml_schema::flags f, ::xml_schema::container* c)
    : ::xml_schema::type(e, f | ::xml_schema::flags::base, c),
      fps_(this),
      video_length_(this),
      delta_t_(this),
      end_time_(this),
      cuboid_(this) {
    if ((f & ::xml_schema::flags::base) == 0) {
        ::xsd::cxx::xml::dom::parser<char> p(e, true, false, false);
        this->parse(p, f);
    }
}

void configuration::parse(::xsd::cxx::xml::dom::parser<char>& p, ::xml_schema::flags f) {
    for (; p.more_content(); p.next_content(false)) {
        const ::xercesc::DOMElement& i(p.cur_element());
        const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

        // fps
        //
        if (n.name() == "fps" && n.namespace_().empty()) {
            if (!this->fps_) {
                this->fps_.set(fps_traits::create(i, f, this));
                continue;
            }
        }

        // video_length
        //
        if (n.name() == "video_length" && n.namespace_().empty()) {
            if (!this->video_length_) {
                this->video_length_.set(video_length_traits::create(i, f, this));
                continue;
            }
        }

        // delta_t
        //
        if (n.name() == "delta_t" && n.namespace_().empty()) {
            if (!this->delta_t_) {
                this->delta_t_.set(delta_t_traits::create(i, f, this));
                continue;
            }
        }

        // end_time
        //
        if (n.name() == "end_time" && n.namespace_().empty()) {
            if (!this->end_time_) {
                this->end_time_.set(end_time_traits::create(i, f, this));
                continue;
            }
        }

        // cuboid
        //
        if (n.name() == "cuboid" && n.namespace_().empty()) {
            ::std::unique_ptr<cuboid_type> r(cuboid_traits::create(i, f, this));

            this->cuboid_.push_back(::std::move(r));
            continue;
        }

        break;
    }
}

configuration* configuration::_clone(::xml_schema::flags f, ::xml_schema::container* c) const {
    return new class configuration(*this, f, c);
}

configuration& configuration::operator=(const configuration& x) {
    if (this != &x) {
        static_cast< ::xml_schema::type&>(*this) = x;
        this->fps_ = x.fps_;
        this->video_length_ = x.video_length_;
        this->delta_t_ = x.delta_t_;
        this->end_time_ = x.end_time_;
        this->cuboid_ = x.cuboid_;
    }

    return *this;
}

configuration::~configuration() {}

// cuboid
//

cuboid::cuboid(const position_type& position, const grid_dim_type& grid_dim, const grid_spacing_type& grid_spacing,
               const temperature_type& temperature, const mass_type& mass, const velocity_type& velocity, const type_type& type)
    : ::xml_schema::type(),
      position_(position, this),
      grid_dim_(grid_dim, this),
      grid_spacing_(grid_spacing, this),
      temperature_(temperature, this),
      mass_(mass, this),
      velocity_(velocity, this),
      type_(type, this) {}

cuboid::cuboid(::std::unique_ptr<position_type> position, ::std::unique_ptr<grid_dim_type> grid_dim, const grid_spacing_type& grid_spacing,
               const temperature_type& temperature, const mass_type& mass, ::std::unique_ptr<velocity_type> velocity, const type_type& type)
    : ::xml_schema::type(),
      position_(std::move(position), this),
      grid_dim_(std::move(grid_dim), this),
      grid_spacing_(grid_spacing, this),
      temperature_(temperature, this),
      mass_(mass, this),
      velocity_(std::move(velocity), this),
      type_(type, this) {}

cuboid::cuboid(const cuboid& x, ::xml_schema::flags f, ::xml_schema::container* c)
    : ::xml_schema::type(x, f, c),
      position_(x.position_, f, this),
      grid_dim_(x.grid_dim_, f, this),
      grid_spacing_(x.grid_spacing_, f, this),
      temperature_(x.temperature_, f, this),
      mass_(x.mass_, f, this),
      velocity_(x.velocity_, f, this),
      type_(x.type_, f, this) {}

cuboid::cuboid(const ::xercesc::DOMElement& e, ::xml_schema::flags f, ::xml_schema::container* c)
    : ::xml_schema::type(e, f | ::xml_schema::flags::base, c),
      position_(this),
      grid_dim_(this),
      grid_spacing_(this),
      temperature_(this),
      mass_(this),
      velocity_(this),
      type_(this) {
    if ((f & ::xml_schema::flags::base) == 0) {
        ::xsd::cxx::xml::dom::parser<char> p(e, true, false, false);
        this->parse(p, f);
    }
}

void cuboid::parse(::xsd::cxx::xml::dom::parser<char>& p, ::xml_schema::flags f) {
    for (; p.more_content(); p.next_content(false)) {
        const ::xercesc::DOMElement& i(p.cur_element());
        const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(i));

        // position
        //
        if (n.name() == "position" && n.namespace_().empty()) {
            ::std::unique_ptr<position_type> r(position_traits::create(i, f, this));

            if (!position_.present()) {
                this->position_.set(::std::move(r));
                continue;
            }
        }

        // grid_dim
        //
        if (n.name() == "grid_dim" && n.namespace_().empty()) {
            ::std::unique_ptr<grid_dim_type> r(grid_dim_traits::create(i, f, this));

            if (!grid_dim_.present()) {
                this->grid_dim_.set(::std::move(r));
                continue;
            }
        }

        // grid_spacing
        //
        if (n.name() == "grid_spacing" && n.namespace_().empty()) {
            if (!grid_spacing_.present()) {
                this->grid_spacing_.set(grid_spacing_traits::create(i, f, this));
                continue;
            }
        }

        // temperature
        //
        if (n.name() == "temperature" && n.namespace_().empty()) {
            if (!temperature_.present()) {
                this->temperature_.set(temperature_traits::create(i, f, this));
                continue;
            }
        }

        // mass
        //
        if (n.name() == "mass" && n.namespace_().empty()) {
            if (!mass_.present()) {
                this->mass_.set(mass_traits::create(i, f, this));
                continue;
            }
        }

        // velocity
        //
        if (n.name() == "velocity" && n.namespace_().empty()) {
            ::std::unique_ptr<velocity_type> r(velocity_traits::create(i, f, this));

            if (!velocity_.present()) {
                this->velocity_.set(::std::move(r));
                continue;
            }
        }

        // type
        //
        if (n.name() == "type" && n.namespace_().empty()) {
            if (!type_.present()) {
                this->type_.set(type_traits::create(i, f, this));
                continue;
            }
        }

        break;
    }

    if (!position_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("position", "");
    }

    if (!grid_dim_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("grid_dim", "");
    }

    if (!grid_spacing_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("grid_spacing", "");
    }

    if (!temperature_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("temperature", "");
    }

    if (!mass_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("mass", "");
    }

    if (!velocity_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("velocity", "");
    }

    if (!type_.present()) {
        throw ::xsd::cxx::tree::expected_element<char>("type", "");
    }
}

cuboid* cuboid::_clone(::xml_schema::flags f, ::xml_schema::container* c) const { return new class cuboid(*this, f, c); }

cuboid& cuboid::operator=(const cuboid& x) {
    if (this != &x) {
        static_cast< ::xml_schema::type&>(*this) = x;
        this->position_ = x.position_;
        this->grid_dim_ = x.grid_dim_;
        this->grid_spacing_ = x.grid_spacing_;
        this->temperature_ = x.temperature_;
        this->mass_ = x.mass_;
        this->velocity_ = x.velocity_;
        this->type_ = x.type_;
    }

    return *this;
}

cuboid::~cuboid() {}

#include <istream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/sax/std-input-source.hxx>

::std::unique_ptr< ::configuration> configuration_(const ::std::string& u, ::xml_schema::flags f, const ::xml_schema::properties& p) {
    ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::tree::error_handler<char> h;

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(u, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing<char> >();

    return ::std::unique_ptr< ::configuration>(::configuration_(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::configuration> configuration_(const ::std::string& u, ::xml_schema::error_handler& h, ::xml_schema::flags f,
                                                   const ::xml_schema::properties& p) {
    ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(u, h, p, f));

    if (!d.get()) throw ::xsd::cxx::tree::parsing<char>();

    return ::std::unique_ptr< ::configuration>(::configuration_(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::configuration> configuration_(const ::std::string& u, ::xercesc::DOMErrorHandler& h, ::xml_schema::flags f,
                                                   const ::xml_schema::properties& p) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(u, h, p, f));

    if (!d.get()) throw ::xsd::cxx::tree::parsing<char>();

    return ::std::unique_ptr< ::configuration>(::configuration_(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::configuration> configuration_(::std::istream& is, ::xml_schema::flags f, const ::xml_schema::properties& p) {
    ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc(is);
    return ::configuration_(isrc, f, p);
}

::std::unique_ptr< ::configuration> configuration_(::std::istream& is, ::xml_schema::error_handler& h, ::xml_schema::flags f,
                                                   const ::xml_schema::properties& p) {
    ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc(is);
    return ::configuration_(isrc, h, f, p);
}

::std::unique_ptr< ::configuration> configuration_(::std::istream& is, ::xercesc::DOMErrorHandler& h, ::xml_schema::flags f,
                                                   const ::xml_schema::properties& p) {
    ::xsd::cxx::xml::sax::std_input_source isrc(is);
    return ::configuration_(isrc, h, f, p);
}

::std::unique_ptr< ::configuration> configuration_(::std::istream& is, const ::std::string& sid, ::xml_schema::flags f,
                                                   const ::xml_schema::properties& p) {
    ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc(is, sid);
    return ::configuration_(isrc, f, p);
}

::std::unique_ptr< ::configuration> configuration_(::std::istream& is, const ::std::string& sid, ::xml_schema::error_handler& h,
                                                   ::xml_schema::flags f, const ::xml_schema::properties& p) {
    ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0, (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc(is, sid);
    return ::configuration_(isrc, h, f, p);
}

::std::unique_ptr< ::configuration> configuration_(::std::istream& is, const ::std::string& sid, ::xercesc::DOMErrorHandler& h,
                                                   ::xml_schema::flags f, const ::xml_schema::properties& p) {
    ::xsd::cxx::xml::sax::std_input_source isrc(is, sid);
    return ::configuration_(isrc, h, f, p);
}

::std::unique_ptr< ::configuration> configuration_(::xercesc::InputSource& i, ::xml_schema::flags f, const ::xml_schema::properties& p) {
    ::xsd::cxx::tree::error_handler<char> h;

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(i, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing<char> >();

    return ::std::unique_ptr< ::configuration>(::configuration_(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::configuration> configuration_(::xercesc::InputSource& i, ::xml_schema::error_handler& h, ::xml_schema::flags f,
                                                   const ::xml_schema::properties& p) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(i, h, p, f));

    if (!d.get()) throw ::xsd::cxx::tree::parsing<char>();

    return ::std::unique_ptr< ::configuration>(::configuration_(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::configuration> configuration_(::xercesc::InputSource& i, ::xercesc::DOMErrorHandler& h, ::xml_schema::flags f,
                                                   const ::xml_schema::properties& p) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::parse<char>(i, h, p, f));

    if (!d.get()) throw ::xsd::cxx::tree::parsing<char>();

    return ::std::unique_ptr< ::configuration>(::configuration_(std::move(d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::configuration> configuration_(const ::xercesc::DOMDocument& doc, ::xml_schema::flags f,
                                                   const ::xml_schema::properties& p) {
    if (f & ::xml_schema::flags::keep_dom) {
        ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(static_cast< ::xercesc::DOMDocument*>(doc.cloneNode(true)));

        return ::std::unique_ptr< ::configuration>(::configuration_(std::move(d), f | ::xml_schema::flags::own_dom, p));
    }

    const ::xercesc::DOMElement& e(*doc.getDocumentElement());
    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(e));

    if (n.name() == "configuration" && n.namespace_() == "") {
        ::std::unique_ptr< ::configuration> r(::xsd::cxx::tree::traits< ::configuration, char>::create(e, f, 0));
        return r;
    }

    throw ::xsd::cxx::tree::unexpected_element<char>(n.name(), n.namespace_(), "configuration", "");
}

::std::unique_ptr< ::configuration> configuration_(::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d, ::xml_schema::flags f,
                                                   const ::xml_schema::properties&) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> c(((f & ::xml_schema::flags::keep_dom) && !(f & ::xml_schema::flags::own_dom))
                                                                 ? static_cast< ::xercesc::DOMDocument*>(d->cloneNode(true))
                                                                 : 0);

    ::xercesc::DOMDocument& doc(c.get() ? *c : *d);
    const ::xercesc::DOMElement& e(*doc.getDocumentElement());

    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(e));

    if (f & ::xml_schema::flags::keep_dom) doc.setUserData(::xml_schema::dom::tree_node_key, (c.get() ? &c : &d), 0);

    if (n.name() == "configuration" && n.namespace_() == "") {
        ::std::unique_ptr< ::configuration> r(::xsd::cxx::tree::traits< ::configuration, char>::create(e, f, 0));
        return r;
    }

    throw ::xsd::cxx::tree::unexpected_element<char>(n.name(), n.namespace_(), "configuration", "");
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

void configuration_(::std::ostream& o, const ::configuration& s, const ::xml_schema::namespace_infomap& m, const ::std::string& e,
                    ::xml_schema::flags f) {
    ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::configuration_(s, m, f));

    ::xsd::cxx::tree::error_handler<char> h;

    ::xsd::cxx::xml::dom::ostream_format_target t(o);
    if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
        h.throw_if_failed< ::xsd::cxx::tree::serialization<char> >();
    }
}

void configuration_(::std::ostream& o, const ::configuration& s, ::xml_schema::error_handler& h, const ::xml_schema::namespace_infomap& m,
                    const ::std::string& e, ::xml_schema::flags f) {
    ::xsd::cxx::xml::auto_initializer i((f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::configuration_(s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t(o);
    if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
        throw ::xsd::cxx::tree::serialization<char>();
    }
}

void configuration_(::std::ostream& o, const ::configuration& s, ::xercesc::DOMErrorHandler& h, const ::xml_schema::namespace_infomap& m,
                    const ::std::string& e, ::xml_schema::flags f) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::configuration_(s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t(o);
    if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
        throw ::xsd::cxx::tree::serialization<char>();
    }
}

void configuration_(::xercesc::XMLFormatTarget& t, const ::configuration& s, const ::xml_schema::namespace_infomap& m,
                    const ::std::string& e, ::xml_schema::flags f) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::configuration_(s, m, f));

    ::xsd::cxx::tree::error_handler<char> h;

    if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
        h.throw_if_failed< ::xsd::cxx::tree::serialization<char> >();
    }
}

void configuration_(::xercesc::XMLFormatTarget& t, const ::configuration& s, ::xml_schema::error_handler& h,
                    const ::xml_schema::namespace_infomap& m, const ::std::string& e, ::xml_schema::flags f) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::configuration_(s, m, f));
    if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
        throw ::xsd::cxx::tree::serialization<char>();
    }
}

void configuration_(::xercesc::XMLFormatTarget& t, const ::configuration& s, ::xercesc::DOMErrorHandler& h,
                    const ::xml_schema::namespace_infomap& m, const ::std::string& e, ::xml_schema::flags f) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::configuration_(s, m, f));
    if (!::xsd::cxx::xml::dom::serialize(t, *d, e, h, f)) {
        throw ::xsd::cxx::tree::serialization<char>();
    }
}

void configuration_(::xercesc::DOMDocument& d, const ::configuration& s, ::xml_schema::flags) {
    ::xercesc::DOMElement& e(*d.getDocumentElement());
    const ::xsd::cxx::xml::qualified_name<char> n(::xsd::cxx::xml::dom::name<char>(e));

    if (n.name() == "configuration" && n.namespace_() == "") {
        e << s;
    } else {
        throw ::xsd::cxx::tree::unexpected_element<char>(n.name(), n.namespace_(), "configuration", "");
    }
}

::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> configuration_(const ::configuration& s, const ::xml_schema::namespace_infomap& m,
                                                                      ::xml_schema::flags f) {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument> d(::xsd::cxx::xml::dom::serialize<char>("configuration", "", m, f));

    ::configuration_(*d, s, f);
    return d;
}

void operator<<(::xercesc::DOMElement& e, const DoubleVec3& i) {
    e << static_cast<const ::xml_schema::type&>(i);

    // x
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("x", e));

        s << ::xml_schema::as_double(i.x());
    }

    // y
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("y", e));

        s << ::xml_schema::as_double(i.y());
    }

    // z
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("z", e));

        s << ::xml_schema::as_double(i.z());
    }
}

void operator<<(::xercesc::DOMElement& e, const IntVec3& i) {
    e << static_cast<const ::xml_schema::type&>(i);

    // dimx
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("dimx", e));

        s << i.dimx();
    }

    // dimy
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("dimy", e));

        s << i.dimy();
    }

    // dimz
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("dimz", e));

        s << i.dimz();
    }
}

void operator<<(::xercesc::DOMElement& e, const configuration& i) {
    e << static_cast<const ::xml_schema::type&>(i);

    // fps
    //
    if (i.fps()) {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("fps", e));

        s << *i.fps();
    }

    // video_length
    //
    if (i.video_length()) {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("video_length", e));

        s << *i.video_length();
    }

    // delta_t
    //
    if (i.delta_t()) {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("delta_t", e));

        s << ::xml_schema::as_decimal(*i.delta_t());
    }

    // end_time
    //
    if (i.end_time()) {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("end_time", e));

        s << ::xml_schema::as_decimal(*i.end_time());
    }

    // cuboid
    //
    for (configuration::cuboid_const_iterator b(i.cuboid().begin()), n(i.cuboid().end()); b != n; ++b) {
        const configuration::cuboid_type& x(*b);

        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("cuboid", e));

        s << x;
    }
}

void operator<<(::xercesc::DOMElement& e, const cuboid& i) {
    e << static_cast<const ::xml_schema::type&>(i);

    // position
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("position", e));

        s << i.position();
    }

    // grid_dim
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("grid_dim", e));

        s << i.grid_dim();
    }

    // grid_spacing
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("grid_spacing", e));

        s << ::xml_schema::as_decimal(i.grid_spacing());
    }

    // temperature
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("temperature", e));

        s << ::xml_schema::as_decimal(i.temperature());
    }

    // mass
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("mass", e));

        s << ::xml_schema::as_decimal(i.mass());
    }

    // velocity
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("velocity", e));

        s << i.velocity();
    }

    // type
    //
    {
        ::xercesc::DOMElement& s(::xsd::cxx::xml::dom::create_element("type", e));

        s << i.type();
    }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.