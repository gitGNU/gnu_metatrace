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
// objects
//=======================================================================================
namespace objects {
        
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // plane
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        enum aa_plane_direction {
                x, y, z
        };
        template <typename distance_, aa_plane_direction direction, typename color> struct aa_plane;
        
        
        
        template <typename ray_, typename plane_, bool does_intersect> struct aa_plane_eins {
        private:
                typedef ray_ ray;
                typedef plane_ plane;
                typedef typename plane::value plane_value;
                typedef typename ray::position::y rayp_y;
                typedef typename ray::direction::y rayd_y;
        
                typedef scalar::sub<rayp_y, plane_value> height;
        public:
                typedef scalar::div<height, scalar::neg<rayd_y>> distance;
                typedef ::ray::madd<ray, distance> point_of_intersection;                
        };
        
        template <typename ray_, typename plane_> struct aa_plane_eins<ray_, plane_, false> {
                typedef scalar::neg<scalar::c1> distance;                
                typedef vector::vector<scalar::c0,scalar::c0,scalar::c0> point_of_intersection;                
        };

        template <typename value_, typename color_> struct aa_plane<value_, aa_plane_direction::y, color_> {
                typedef value_ value;
                
                template <typename ray_> struct intersect {
                        typedef ray_ ray;
                        typedef typename ray::position::y rayp_y;
                        typedef typename ray::direction::y rayd_y;
                        typedef typename scalar::c0 c0;

                        enum {
                                hit_side = scalar::greater<rayp_y, value>::value ? 1 : -1,
                                does_intersect = (hit_side>0 && scalar::less<rayd_y,c0>::value)
                                              || (hit_side<0 && scalar::greater<rayd_y,c0>::value)
                        };
                private:
                        typedef aa_plane_eins<ray, aa_plane, does_intersect> eins;
                public:                        
                        typedef typename eins::distance distance;
                        typedef typename eins::point_of_intersection point_of_intersection;
                        typedef vector::vector<
                                scalar::c0,
                                ift<(hit_side>0), scalar::c1, scalar::cn1>,
                                scalar::c0
                        > normal;
                        typedef color_ color;
                };
                
        };
        /*private:
                typedef distance_ distance;                

        public:
                
                template <typename ray_> struct intersect {
                private:
                        typedef ray_ ray;
                        typedef typename ray::position ray_pos;
                        typedef typename ray::direction ray_dir;                        
                        
                public:
                        enum {
                                hit_side = ,
                                does_intersect = zwo::does_intersect
                        };
                        
                        typedef typename zwo::distance distance;
                        typedef typename drei::point_of_intersection point_of_intersection;
                        typedef typename drei::normal normal;
                        typedef vector::normal_to_rgbf<normal> color;
                };
        };*/
}
