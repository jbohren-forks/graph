//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// This file is part of the Generic Graph Component Library
//
// You should have received a copy of the License Agreement for the
// Generic Graph Component Library along with the software;  see the
// file LICENSE.  If not, contact Office of Research, University of Notre
// Dame, Notre Dame, IN  46556.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================
//

#ifndef BOOST_INDIRECT_CMP_HPP
#define BOOST_INDIRECT_CMP_HPP

#include <functional>
#include <boost/config.hpp>
#include <boost/property_map.hpp>

namespace boost {

  //: indirect_cmp
  //
  // could also do this with compose_f_gx_hx, and the member binder...
  //
  //!category: functors
  //!component: type
  //!tparam: Decorator - a model of Decorator
  //!definition: functor.h
  template <class Decorator, class Compare>
  class indirect_cmp {
  public:
    typedef typename boost::property_traits<Decorator>::value_type T;
    typedef typename boost::property_traits<Decorator>::key_type K;
    typedef K first_argument_type;
    typedef K second_argument_type;
    typedef T result_type;
    inline indirect_cmp(const Decorator& df, const Compare& c = Compare())
      : d(df), cmp(c) { }

    template <class A, class B>
    inline bool 
    operator()(const A& u, const B& v) const {
      T du = get(d, u), dv = get(d, v);
      return cmp(du, dv);
    }
  protected:
    Decorator d;
    Compare cmp;
  };

} // namespace boost


#endif // GGCL_INDIRECT_CMP_HPP
