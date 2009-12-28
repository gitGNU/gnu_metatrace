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
// raytrace
//=======================================================================================
namespace raytrace {
        
        template <typename far_plane> struct simple_camera {
                template <typename u, typename v> struct generate {
                private:
                        typedef vector::normalize<
                                vector::vector<u,v,far_plane>
                        > direction;
                
                        typedef vector::vector<
                                frac0<0,1>, frac0<0,1>, frac0<0,1>
                        > position;
                public:
                        typedef ray::ray<
                                position,
                                direction
                        > type;
                };
        };
        
        
        template <
                typename CameraT, 
                typename ObjectsT, 
                typename LightsT
        > struct whitted_style {
                
                typedef CameraT camera;
                typedef ObjectsT objects;
                typedef LightsT lights;
                
                template <typename ray> struct raytrace {
                        typedef vector::normal_to_rgb<typename ray::direction> background_color;
                
                        typedef typename ObjectsT::template intersect<ray> intersection;
                        enum {
                                does_intersect = intersection::does_intersect
                        };
                        
                        /*
                        typedef typename intersection::distance distance;
                        
                        enum {
                                c = to_int<
                                        tinplate::mul<
                                                frac0<255,1>,
                                                tinplate::max<
                                                        frac0<0,1>,
                                                        tinplate::min<
                                                                frac0<1,1>,
                                                                mul<
                                                                        frac0<1,4>,
                                                                        distance
                                                                >
                                                        >
                                                >
                                        >
                                >::value
                        };                        
                        typedef rgb<c,c,c> distance_color;
                        typedef vector::normal_to_rgb<typename intersection::normal> normal_color;
                        */
                        
                        typedef typename lights::template shade<intersection> lit_result;

                public:
                        typedef typename ift<
                                intersection::does_intersect,
                                rgbf_to_rgb<typename lit_result::lit_color>,
                                //rgbf_to_rgb<typename intersection::color>,
                                background_color
                        >::type color;
                };
        };
        
        template <
                template<typename,typename,typename> class RendererT,                
                typename CameraT, 
                typename ObjectsT, 
                typename LightsT                
        > struct scene {
                
                template <size_t x, size_t width, size_t y, size_t height> struct kernel {
                public:                                                
                        // Map 0..width to -0.5..+0.5.
                        typedef tinplate::sub< 
                                frac0<x+config::virtual_x, config::virtual_width>, 
                                frac0<1,2>
                        > u;
                        typedef tinplate::neg<tinplate::sub<
                                frac0<y+config::virtual_y, config::virtual_height>,
                                frac0<1,2>
                        >> v;
                
                        // Generate primary ray.
                        typedef typename CameraT::template generate<u,v>::type ray;
                
                        typedef typename RendererT<
                                CameraT, ObjectsT, LightsT
                        >::template raytrace<ray> raytrace;
                public:                        
                        typedef typename raytrace::color color;
                        
                        // only for debugging
                        /*
                        typedef typename raytrace::distance distance;
                        typedef typename raytrace::normal_color normal_color;
                        typedef typename raytrace::direction_color direction_color;
                        typedef typename raytrace::intersection::normal normal;
                        typedef typename raytrace::intersection::point_of_intersection point_of_intersection;                        
                        enum { does_intersect = raytrace::does_intersect };
                        */
                };
        };
}