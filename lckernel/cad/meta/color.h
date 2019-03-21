#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

namespace lc {

    /**
    * Represents a Color
    *
    */
    class Color {
        public:
            Color() : _r(0.), _g(0.), _b(0.), _a(1.) {}
            Color(int r, int g, int b, int a = 0xff) : _r(std::min(std::max(0, r), 0xff) / 255.) , _g(std::min(std::max(0, g), 0xff) / 255.), _b(std::min(std::max(0, b), 0xff) / 255.), _a(std::min(std::max(0, a), 0xff) / 255.) {
            }
            Color(double r, double g, double b, double a = 1.) : _r(std::min(std::max(0., r), 1.)), _g(std::min(std::max(0., g), 1.)), _b(std::min(std::max(0., b), 1.)), _a(std::min(std::max(0., a), 1.)) {
            }
            Color(const Color& other) : _r(other._r), _g(other._g), _b(other._b), _a(other._a) {}

            Color& operator = (const Color& other) {
                if (this != &other) {
                    _r = other._r;
                    _g = other._g;
                    _b = other._b;
                    _a = other._a;
                }

                return *this;
            }

            double absDiff2(const Color& other){
                return ((_r-other._r)*(_r-other._r)+(_g-other._g)*(_g-other._g)+(_b-other._b)*(_b-other._b)+(_a-other._a)*(_a-other._a));
            }

            bool operator==(lc::Color b) {
                return _r == b._r && _b == b._b && _g == b._g && _a == b._a;
            }


            virtual ~Color() {}

            inline double red() const {
                return _r;
            }
            inline double green() const {
                return _g;
            }
            inline double blue() const {
                return _b;
            }
            inline double alpha() const {
                return _a;
            }

            inline unsigned char redI() const {
                return (unsigned char) std::round(_r * 255);
            }
            inline unsigned char greenI() const {
                return (unsigned char) std::round(_g * 255);
            }
            inline unsigned char blueI() const {
                return (unsigned char) std::round(_b * 255);
            }
            inline unsigned char alphaI() const {
                return (unsigned char) std::round(_a * 255);
            }

            friend std::ostream& operator<<(std::ostream& os, const Color& color) {
                os << "Color(red=" << color._r << " green=" << color._g << " blue=" << color._b << " ahlpa=" << color._a << ")";
                return os;
            }

        private:
            double _r;
            double _g;
            double _b;
            double _a;
    };


}
