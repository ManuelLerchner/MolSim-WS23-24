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

#include <xsd/cxx/pre.hxx>

#include "checkpoint_schema.h"

// CheckPointFileType
//

const CheckPointFileType::MetaData_type& CheckPointFileType::
MetaData () const
{
  return this->MetaData_.get ();
}

CheckPointFileType::MetaData_type& CheckPointFileType::
MetaData ()
{
  return this->MetaData_.get ();
}

void CheckPointFileType::
MetaData (const MetaData_type& x)
{
  this->MetaData_.set (x);
}

void CheckPointFileType::
MetaData (::std::unique_ptr< MetaData_type > x)
{
  this->MetaData_.set (std::move (x));
}

const CheckPointFileType::ParticleData_type& CheckPointFileType::
ParticleData () const
{
  return this->ParticleData_.get ();
}

CheckPointFileType::ParticleData_type& CheckPointFileType::
ParticleData ()
{
  return this->ParticleData_.get ();
}

void CheckPointFileType::
ParticleData (const ParticleData_type& x)
{
  this->ParticleData_.set (x);
}

void CheckPointFileType::
ParticleData (::std::unique_ptr< ParticleData_type > x)
{
  this->ParticleData_.set (std::move (x));
}


// MetaDataDataType
//

const MetaDataDataType::input_file_type& MetaDataDataType::
input_file () const
{
  return this->input_file_.get ();
}

MetaDataDataType::input_file_type& MetaDataDataType::
input_file ()
{
  return this->input_file_.get ();
}

void MetaDataDataType::
input_file (const input_file_type& x)
{
  this->input_file_.set (x);
}

void MetaDataDataType::
input_file (::std::unique_ptr< input_file_type > x)
{
  this->input_file_.set (std::move (x));
}

const MetaDataDataType::input_file_hash_type& MetaDataDataType::
input_file_hash () const
{
  return this->input_file_hash_.get ();
}

MetaDataDataType::input_file_hash_type& MetaDataDataType::
input_file_hash ()
{
  return this->input_file_hash_.get ();
}

void MetaDataDataType::
input_file_hash (const input_file_hash_type& x)
{
  this->input_file_hash_.set (x);
}

const MetaDataDataType::end_time_type& MetaDataDataType::
end_time () const
{
  return this->end_time_.get ();
}

MetaDataDataType::end_time_type& MetaDataDataType::
end_time ()
{
  return this->end_time_.get ();
}

void MetaDataDataType::
end_time (const end_time_type& x)
{
  this->end_time_.set (x);
}

const MetaDataDataType::delta_t_type& MetaDataDataType::
delta_t () const
{
  return this->delta_t_.get ();
}

MetaDataDataType::delta_t_type& MetaDataDataType::
delta_t ()
{
  return this->delta_t_.get ();
}

void MetaDataDataType::
delta_t (const delta_t_type& x)
{
  this->delta_t_.set (x);
}


// ParticleDataType
//

const ParticleDataType::particle_sequence& ParticleDataType::
particle () const
{
  return this->particle_;
}

ParticleDataType::particle_sequence& ParticleDataType::
particle ()
{
  return this->particle_;
}

void ParticleDataType::
particle (const particle_sequence& s)
{
  this->particle_ = s;
}


// ParticleType
//

const ParticleType::position_type& ParticleType::
position () const
{
  return this->position_.get ();
}

ParticleType::position_type& ParticleType::
position ()
{
  return this->position_.get ();
}

void ParticleType::
position (const position_type& x)
{
  this->position_.set (x);
}

void ParticleType::
position (::std::unique_ptr< position_type > x)
{
  this->position_.set (std::move (x));
}

const ParticleType::velocity_type& ParticleType::
velocity () const
{
  return this->velocity_.get ();
}

ParticleType::velocity_type& ParticleType::
velocity ()
{
  return this->velocity_.get ();
}

void ParticleType::
velocity (const velocity_type& x)
{
  this->velocity_.set (x);
}

void ParticleType::
velocity (::std::unique_ptr< velocity_type > x)
{
  this->velocity_.set (std::move (x));
}

const ParticleType::force_type& ParticleType::
force () const
{
  return this->force_.get ();
}

ParticleType::force_type& ParticleType::
force ()
{
  return this->force_.get ();
}

void ParticleType::
force (const force_type& x)
{
  this->force_.set (x);
}

void ParticleType::
force (::std::unique_ptr< force_type > x)
{
  this->force_.set (std::move (x));
}

const ParticleType::old_force_type& ParticleType::
old_force () const
{
  return this->old_force_.get ();
}

ParticleType::old_force_type& ParticleType::
old_force ()
{
  return this->old_force_.get ();
}

void ParticleType::
old_force (const old_force_type& x)
{
  this->old_force_.set (x);
}

void ParticleType::
old_force (::std::unique_ptr< old_force_type > x)
{
  this->old_force_.set (std::move (x));
}

const ParticleType::mass_type& ParticleType::
mass () const
{
  return this->mass_.get ();
}

ParticleType::mass_type& ParticleType::
mass ()
{
  return this->mass_.get ();
}

void ParticleType::
mass (const mass_type& x)
{
  this->mass_.set (x);
}

const ParticleType::type_type& ParticleType::
type () const
{
  return this->type_.get ();
}

ParticleType::type_type& ParticleType::
type ()
{
  return this->type_.get ();
}

void ParticleType::
type (const type_type& x)
{
  this->type_.set (x);
}

const ParticleType::epsilon_type& ParticleType::
epsilon () const
{
  return this->epsilon_.get ();
}

ParticleType::epsilon_type& ParticleType::
epsilon ()
{
  return this->epsilon_.get ();
}

void ParticleType::
epsilon (const epsilon_type& x)
{
  this->epsilon_.set (x);
}

const ParticleType::sigma_type& ParticleType::
sigma () const
{
  return this->sigma_.get ();
}

ParticleType::sigma_type& ParticleType::
sigma ()
{
  return this->sigma_.get ();
}

void ParticleType::
sigma (const sigma_type& x)
{
  this->sigma_.set (x);
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// CheckPointFileType
//

CheckPointFileType::
CheckPointFileType (const MetaData_type& MetaData,
                    const ParticleData_type& ParticleData)
: ::xml_schema::type (),
  MetaData_ (MetaData, this),
  ParticleData_ (ParticleData, this)
{
}

CheckPointFileType::
CheckPointFileType (::std::unique_ptr< MetaData_type > MetaData,
                    ::std::unique_ptr< ParticleData_type > ParticleData)
: ::xml_schema::type (),
  MetaData_ (std::move (MetaData), this),
  ParticleData_ (std::move (ParticleData), this)
{
}

CheckPointFileType::
CheckPointFileType (const CheckPointFileType& x,
                    ::xml_schema::flags f,
                    ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  MetaData_ (x.MetaData_, f, this),
  ParticleData_ (x.ParticleData_, f, this)
{
}

CheckPointFileType::
CheckPointFileType (const ::xercesc::DOMElement& e,
                    ::xml_schema::flags f,
                    ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  MetaData_ (this),
  ParticleData_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void CheckPointFileType::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // MetaData
    //
    if (n.name () == "MetaData" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< MetaData_type > r (
        MetaData_traits::create (i, f, this));

      if (!MetaData_.present ())
      {
        this->MetaData_.set (::std::move (r));
        continue;
      }
    }

    // ParticleData
    //
    if (n.name () == "ParticleData" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< ParticleData_type > r (
        ParticleData_traits::create (i, f, this));

      if (!ParticleData_.present ())
      {
        this->ParticleData_.set (::std::move (r));
        continue;
      }
    }

    break;
  }

  if (!MetaData_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "MetaData",
      "");
  }

  if (!ParticleData_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "ParticleData",
      "");
  }
}

CheckPointFileType* CheckPointFileType::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class CheckPointFileType (*this, f, c);
}

CheckPointFileType& CheckPointFileType::
operator= (const CheckPointFileType& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->MetaData_ = x.MetaData_;
    this->ParticleData_ = x.ParticleData_;
  }

  return *this;
}

CheckPointFileType::
~CheckPointFileType ()
{
}

// MetaDataDataType
//

MetaDataDataType::
MetaDataDataType (const input_file_type& input_file,
                  const input_file_hash_type& input_file_hash,
                  const end_time_type& end_time,
                  const delta_t_type& delta_t)
: ::xml_schema::type (),
  input_file_ (input_file, this),
  input_file_hash_ (input_file_hash, this),
  end_time_ (end_time, this),
  delta_t_ (delta_t, this)
{
}

MetaDataDataType::
MetaDataDataType (const MetaDataDataType& x,
                  ::xml_schema::flags f,
                  ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  input_file_ (x.input_file_, f, this),
  input_file_hash_ (x.input_file_hash_, f, this),
  end_time_ (x.end_time_, f, this),
  delta_t_ (x.delta_t_, f, this)
{
}

MetaDataDataType::
MetaDataDataType (const ::xercesc::DOMElement& e,
                  ::xml_schema::flags f,
                  ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  input_file_ (this),
  input_file_hash_ (this),
  end_time_ (this),
  delta_t_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void MetaDataDataType::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // input_file
    //
    if (n.name () == "input_file" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< input_file_type > r (
        input_file_traits::create (i, f, this));

      if (!input_file_.present ())
      {
        this->input_file_.set (::std::move (r));
        continue;
      }
    }

    // input_file_hash
    //
    if (n.name () == "input_file_hash" && n.namespace_ ().empty ())
    {
      if (!input_file_hash_.present ())
      {
        this->input_file_hash_.set (input_file_hash_traits::create (i, f, this));
        continue;
      }
    }

    // end_time
    //
    if (n.name () == "end_time" && n.namespace_ ().empty ())
    {
      if (!end_time_.present ())
      {
        this->end_time_.set (end_time_traits::create (i, f, this));
        continue;
      }
    }

    // delta_t
    //
    if (n.name () == "delta_t" && n.namespace_ ().empty ())
    {
      if (!delta_t_.present ())
      {
        this->delta_t_.set (delta_t_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!input_file_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "input_file",
      "");
  }

  if (!input_file_hash_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "input_file_hash",
      "");
  }

  if (!end_time_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "end_time",
      "");
  }

  if (!delta_t_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "delta_t",
      "");
  }
}

MetaDataDataType* MetaDataDataType::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class MetaDataDataType (*this, f, c);
}

MetaDataDataType& MetaDataDataType::
operator= (const MetaDataDataType& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->input_file_ = x.input_file_;
    this->input_file_hash_ = x.input_file_hash_;
    this->end_time_ = x.end_time_;
    this->delta_t_ = x.delta_t_;
  }

  return *this;
}

MetaDataDataType::
~MetaDataDataType ()
{
}

// ParticleDataType
//

ParticleDataType::
ParticleDataType ()
: ::xml_schema::type (),
  particle_ (this)
{
}

ParticleDataType::
ParticleDataType (const ParticleDataType& x,
                  ::xml_schema::flags f,
                  ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  particle_ (x.particle_, f, this)
{
}

ParticleDataType::
ParticleDataType (const ::xercesc::DOMElement& e,
                  ::xml_schema::flags f,
                  ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  particle_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void ParticleDataType::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // particle
    //
    if (n.name () == "particle" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< particle_type > r (
        particle_traits::create (i, f, this));

      this->particle_.push_back (::std::move (r));
      continue;
    }

    break;
  }
}

ParticleDataType* ParticleDataType::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class ParticleDataType (*this, f, c);
}

ParticleDataType& ParticleDataType::
operator= (const ParticleDataType& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->particle_ = x.particle_;
  }

  return *this;
}

ParticleDataType::
~ParticleDataType ()
{
}

// ParticleType
//

ParticleType::
ParticleType (const position_type& position,
              const velocity_type& velocity,
              const force_type& force,
              const old_force_type& old_force,
              const mass_type& mass,
              const type_type& type,
              const epsilon_type& epsilon,
              const sigma_type& sigma)
: ::xml_schema::type (),
  position_ (position, this),
  velocity_ (velocity, this),
  force_ (force, this),
  old_force_ (old_force, this),
  mass_ (mass, this),
  type_ (type, this),
  epsilon_ (epsilon, this),
  sigma_ (sigma, this)
{
}

ParticleType::
ParticleType (::std::unique_ptr< position_type > position,
              ::std::unique_ptr< velocity_type > velocity,
              ::std::unique_ptr< force_type > force,
              ::std::unique_ptr< old_force_type > old_force,
              const mass_type& mass,
              const type_type& type,
              const epsilon_type& epsilon,
              const sigma_type& sigma)
: ::xml_schema::type (),
  position_ (std::move (position), this),
  velocity_ (std::move (velocity), this),
  force_ (std::move (force), this),
  old_force_ (std::move (old_force), this),
  mass_ (mass, this),
  type_ (type, this),
  epsilon_ (epsilon, this),
  sigma_ (sigma, this)
{
}

ParticleType::
ParticleType (const ParticleType& x,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  position_ (x.position_, f, this),
  velocity_ (x.velocity_, f, this),
  force_ (x.force_, f, this),
  old_force_ (x.old_force_, f, this),
  mass_ (x.mass_, f, this),
  type_ (x.type_, f, this),
  epsilon_ (x.epsilon_, f, this),
  sigma_ (x.sigma_, f, this)
{
}

ParticleType::
ParticleType (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f,
              ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  position_ (this),
  velocity_ (this),
  force_ (this),
  old_force_ (this),
  mass_ (this),
  type_ (this),
  epsilon_ (this),
  sigma_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void ParticleType::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // position
    //
    if (n.name () == "position" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< position_type > r (
        position_traits::create (i, f, this));

      if (!position_.present ())
      {
        this->position_.set (::std::move (r));
        continue;
      }
    }

    // velocity
    //
    if (n.name () == "velocity" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< velocity_type > r (
        velocity_traits::create (i, f, this));

      if (!velocity_.present ())
      {
        this->velocity_.set (::std::move (r));
        continue;
      }
    }

    // force
    //
    if (n.name () == "force" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< force_type > r (
        force_traits::create (i, f, this));

      if (!force_.present ())
      {
        this->force_.set (::std::move (r));
        continue;
      }
    }

    // old_force
    //
    if (n.name () == "old_force" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< old_force_type > r (
        old_force_traits::create (i, f, this));

      if (!old_force_.present ())
      {
        this->old_force_.set (::std::move (r));
        continue;
      }
    }

    // mass
    //
    if (n.name () == "mass" && n.namespace_ ().empty ())
    {
      if (!mass_.present ())
      {
        this->mass_.set (mass_traits::create (i, f, this));
        continue;
      }
    }

    // type
    //
    if (n.name () == "type" && n.namespace_ ().empty ())
    {
      if (!type_.present ())
      {
        this->type_.set (type_traits::create (i, f, this));
        continue;
      }
    }

    // epsilon
    //
    if (n.name () == "epsilon" && n.namespace_ ().empty ())
    {
      if (!epsilon_.present ())
      {
        this->epsilon_.set (epsilon_traits::create (i, f, this));
        continue;
      }
    }

    // sigma
    //
    if (n.name () == "sigma" && n.namespace_ ().empty ())
    {
      if (!sigma_.present ())
      {
        this->sigma_.set (sigma_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!position_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "position",
      "");
  }

  if (!velocity_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "velocity",
      "");
  }

  if (!force_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "force",
      "");
  }

  if (!old_force_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "old_force",
      "");
  }

  if (!mass_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "mass",
      "");
  }

  if (!type_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "type",
      "");
  }

  if (!epsilon_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "epsilon",
      "");
  }

  if (!sigma_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "sigma",
      "");
  }
}

ParticleType* ParticleType::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class ParticleType (*this, f, c);
}

ParticleType& ParticleType::
operator= (const ParticleType& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->position_ = x.position_;
    this->velocity_ = x.velocity_;
    this->force_ = x.force_;
    this->old_force_ = x.old_force_;
    this->mass_ = x.mass_;
    this->type_ = x.type_;
    this->epsilon_ = x.epsilon_;
    this->sigma_ = x.sigma_;
  }

  return *this;
}

ParticleType::
~ParticleType ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (const ::std::string& u,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::unique_ptr< ::CheckPointFileType > (
    ::CheckPoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (const ::std::string& u,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::CheckPointFileType > (
    ::CheckPoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (const ::std::string& u,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::CheckPointFileType > (
    ::CheckPoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::std::istream& is,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::CheckPoint (isrc, f, p);
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::std::istream& is,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::CheckPoint (isrc, h, f, p);
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::std::istream& is,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::CheckPoint (isrc, h, f, p);
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::CheckPoint (isrc, f, p);
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::CheckPoint (isrc, h, f, p);
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::std::istream& is,
            const ::std::string& sid,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::CheckPoint (isrc, h, f, p);
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::xercesc::InputSource& i,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::unique_ptr< ::CheckPointFileType > (
    ::CheckPoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::xercesc::InputSource& i,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::CheckPointFileType > (
    ::CheckPoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::xercesc::InputSource& i,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::CheckPointFileType > (
    ::CheckPoint (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (const ::xercesc::DOMDocument& doc,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

    return ::std::unique_ptr< ::CheckPointFileType > (
      ::CheckPoint (
        std::move (d), f | ::xml_schema::flags::own_dom, p));
  }

  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "CheckPoint" &&
      n.namespace_ () == "")
  {
    ::std::unique_ptr< ::CheckPointFileType > r (
      ::xsd::cxx::tree::traits< ::CheckPointFileType, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "CheckPoint",
    "");
}

::std::unique_ptr< ::CheckPointFileType >
CheckPoint (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
            ::xml_schema::flags f,
            const ::xml_schema::properties&)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "CheckPoint" &&
      n.namespace_ () == "")
  {
    ::std::unique_ptr< ::CheckPointFileType > r (
      ::xsd::cxx::tree::traits< ::CheckPointFileType, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "CheckPoint",
    "");
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

void
CheckPoint (::std::ostream& o,
            const ::CheckPointFileType& s,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::CheckPoint (s, m, f));

  ::xsd::cxx::tree::error_handler< char > h;

  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
  }
}

void
CheckPoint (::std::ostream& o,
            const ::CheckPointFileType& s,
            ::xml_schema::error_handler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0);

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::CheckPoint (s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
CheckPoint (::std::ostream& o,
            const ::CheckPointFileType& s,
            ::xercesc::DOMErrorHandler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::CheckPoint (s, m, f));
  ::xsd::cxx::xml::dom::ostream_format_target t (o);
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
CheckPoint (::xercesc::XMLFormatTarget& t,
            const ::CheckPointFileType& s,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::CheckPoint (s, m, f));

  ::xsd::cxx::tree::error_handler< char > h;

  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
  }
}

void
CheckPoint (::xercesc::XMLFormatTarget& t,
            const ::CheckPointFileType& s,
            ::xml_schema::error_handler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::CheckPoint (s, m, f));
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
CheckPoint (::xercesc::XMLFormatTarget& t,
            const ::CheckPointFileType& s,
            ::xercesc::DOMErrorHandler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::CheckPoint (s, m, f));
  if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
  {
    throw ::xsd::cxx::tree::serialization< char > ();
  }
}

void
CheckPoint (::xercesc::DOMDocument& d,
            const ::CheckPointFileType& s,
            ::xml_schema::flags)
{
  ::xercesc::DOMElement& e (*d.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "CheckPoint" &&
      n.namespace_ () == "")
  {
    e << s;
  }
  else
  {
    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "CheckPoint",
      "");
  }
}

::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument >
CheckPoint (const ::CheckPointFileType& s,
            const ::xml_schema::namespace_infomap& m,
            ::xml_schema::flags f)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::serialize< char > (
      "CheckPoint",
      "",
      m, f));

  ::CheckPoint (*d, s, f);
  return d;
}

void
operator<< (::xercesc::DOMElement& e, const CheckPointFileType& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // MetaData
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "MetaData",
        e));

    s << i.MetaData ();
  }

  // ParticleData
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "ParticleData",
        e));

    s << i.ParticleData ();
  }
}

void
operator<< (::xercesc::DOMElement& e, const MetaDataDataType& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // input_file
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "input_file",
        e));

    s << i.input_file ();
  }

  // input_file_hash
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "input_file_hash",
        e));

    s << i.input_file_hash ();
  }

  // end_time
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "end_time",
        e));

    s << ::xml_schema::as_double(i.end_time ());
  }

  // delta_t
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "delta_t",
        e));

    s << ::xml_schema::as_double(i.delta_t ());
  }
}

void
operator<< (::xercesc::DOMElement& e, const ParticleDataType& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // particle
  //
  for (ParticleDataType::particle_const_iterator
       b (i.particle ().begin ()), n (i.particle ().end ());
       b != n; ++b)
  {
    const ParticleDataType::particle_type& x (*b);

    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "particle",
        e));

    s << x;
  }
}

void
operator<< (::xercesc::DOMElement& e, const ParticleType& i)
{
  e << static_cast< const ::xml_schema::type& > (i);

  // position
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "position",
        e));

    s << i.position ();
  }

  // velocity
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "velocity",
        e));

    s << i.velocity ();
  }

  // force
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "force",
        e));

    s << i.force ();
  }

  // old_force
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "old_force",
        e));

    s << i.old_force ();
  }

  // mass
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "mass",
        e));

    s << ::xml_schema::as_double(i.mass ());
  }

  // type
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "type",
        e));

    s << i.type ();
  }

  // epsilon
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "epsilon",
        e));

    s << ::xml_schema::as_double(i.epsilon ());
  }

  // sigma
  //
  {
    ::xercesc::DOMElement& s (
      ::xsd::cxx::xml::dom::create_element (
        "sigma",
        e));

    s << ::xml_schema::as_double(i.sigma ());
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

