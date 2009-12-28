//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copyright (C) 2009  Sebastian Mach (*1983)
// * mail: phresnel/at/gmail/dot/com
// * http://phresnel.org
// * http://picogen.org
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//=======================================================================================
// vector math
//=======================================================================================
namespace vector {
        template <typename x_, typename y_, typename z_> struct vector {
                typedef x_ x;
                typedef y_ y;
                typedef z_ z;
        };

        template <typename vec> struct length_sq_impl {
                typedef
                scalar::add<
                        scalar::mul<typename vec::x, typename vec::x>,
                        scalar::mul<typename vec::y, typename vec::y>,
                        scalar::mul<typename vec::z, typename vec::z>
                > type;
        };
        template <typename vec> struct length_sq 
        : length_sq_impl<vec>::type {};


        template <typename vec> struct length_impl {
                typedef scalar::sqrt<
                        length_sq<vec>
                > type;
        };
        template <typename vec> struct length 
        : length_impl<vec>::type {};
                
        
        template <typename lhs, typename rhs> struct add_impl {
                typedef vector<
                        scalar::add<typename lhs::x, typename rhs::x>,
                        scalar::add<typename lhs::y, typename rhs::y>,
                        scalar::add<typename lhs::z, typename rhs::z>
                > type;
        };
        template <typename lhs, typename rhs> struct add
        : add_impl<lhs,rhs>::type {};
        
        
        template <typename lhs, typename rhs> struct sub_impl {
                typedef vector<
                        scalar::sub<typename lhs::x, typename rhs::x>,
                        scalar::sub<typename lhs::y, typename rhs::y>,
                        scalar::sub<typename lhs::z, typename rhs::z>
                > type;
        };
        template <typename lhs, typename rhs> struct sub
        : sub_impl<lhs,rhs>::type {};
        
        
        template <typename lhs, typename rhs> struct scale_impl {
                typedef vector<
                        scalar::mul<typename lhs::x, rhs>,
                        scalar::mul<typename lhs::y, rhs>,
                        scalar::mul<typename lhs::z, rhs>
                > type;
        };
        template <typename lhs, typename rhs> struct scale
        : scale_impl<lhs,rhs>::type {};

        
        template <typename lhs, typename rhs> struct dot_impl {
                typedef scalar::add<
                        scalar::mul<typename lhs::x, typename rhs::x>,
                        scalar::mul<typename lhs::y, typename rhs::y>,
                        scalar::mul<typename lhs::z, typename rhs::z>
                > type;
        };
        template <typename lhs, typename rhs> struct dot
        : dot_impl<lhs,rhs>::type {};

        
        template <typename vec> struct normalize_impl {
        private:
                typedef length<vec> len;
                typedef scalar::reciprocal<len> rlen;
        public:
                typedef scale<vec, rlen> type;
        };
        template <typename vec> struct normalize
        : normalize_impl<vec>::type{};


        /*template <typename vec> struct normal_to_rgb
        : rgb<
                to_int<scalar::mul<frac0<255,1>,scalar::add<scalar::mul<typename vec::x,frac0<1,2>>, frac0<1,2>>>>::value,
                to_int<scalar::mul<frac0<255,1>,scalar::add<scalar::mul<typename vec::y,frac0<1,2>>, frac0<1,2>>>>::value,
                to_int<scalar::mul<frac0<255,1>,scalar::add<scalar::mul<typename vec::z,frac0<1,2>>, frac0<1,2>>>>::value
        > {};
                
        template <typename vec> struct normal_to_rgbf
        : rgbf<
                scalar::add<scalar::mul<typename vec::x,frac0<1,2>>, frac0<1,2>>,
                scalar::add<scalar::mul<typename vec::y,frac0<1,2>>, frac0<1,2>>,
                scalar::add<scalar::mul<typename vec::z,frac0<1,2>>, frac0<1,2>>
        > {};*/
}