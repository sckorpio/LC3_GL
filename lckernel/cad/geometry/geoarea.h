#pragma once

#include "cad/const.h"

#include "geocoordinate.h"
#include "geovector.h"
#include "geobase.h"
#include "cad/base/visitor.h"

namespace lc {
    namespace geo {
        /**
          * Class that describes an area or window.
          */
        class Area : public Base, virtual public Visitable {
            public:
                /**
                  * Create a new Area. The coordinates coordA and coordB will be ordered so that minP will always be < maxP
                  * The coordinates are not allowed to describe a volume
                  *
                  * @param CoordA First coordinate of a area
                  * @param CoordB Second coordinate of a area
                  */
                explicit Area(const Coordinate& coordA, const Coordinate& coordB) :
                    _minP(Coordinate(std::min(coordA.x(), coordB.x()), std::min(coordA.y(), coordB.y()), std::min(coordA.z(), coordB.z()))),
                    _maxP(Coordinate(std::max(coordA.x(), coordB.x()), std::max(coordA.y(), coordB.y()), std::max(coordA.z(), coordB.z()))) {
                    if (coordA.x() != coordB.x() && coordA.y() != coordB.y() && coordA.z() != coordB.z()) {
                        throw "Points describe a volume, not a area.";
                    }

                }

                explicit Area() : _minP(0., 0.), _maxP(0., 0.) {
                }

                /**
                 * @brief Area
                 * given at a coordinate with a given width and height
                 * @param coordA
                 * @param width
                 * @param height
                 */
                explicit Area(const Coordinate& coord, double width, double height) : Area(coord, Coordinate(coord.x() + width, coord.y() + height)) {
                }

                //explicit Area(const Area &a) : _minP(a._minP), _maxP(a._maxP) {}

                inline Area& operator = (const Area& other) {
                    if (this != &other) {
                        _minP = other._minP;
                        _maxP = other._maxP;
                    }

                    return *this;
                }

                /**
                  * Return the smallest corner (closest to (0,0,0) )
                  */
                inline const Coordinate minP() const {
                    return _minP;
                }

                /**
                  * Return the highest corner
                  */
                inline const Coordinate maxP() const {
                    return _maxP;
                }

                /**
                 * @brief width
                 * Returns the width of this area
                 * @return
                 */
                inline double width() const {
                    return _maxP.x() - _minP.x();
                }

                /**
                 * @brief height
                 * Returns the height of this area
                 * @return
                 */
                inline double height() const {
                    return _maxP.y() - _minP.y();
                }

                /**
                  * @brief Test of a specific point lies within area
                  * @param point Point to test against
                  * @return boolean true of the point is within the area
                  */
                inline bool inArea(const Coordinate& point, double tolerance = 0.) const {
                    return (point.x() >= _minP.x() - tolerance && point.x() <= _maxP.x() + tolerance && point.y() >= _minP.y() - tolerance && point.y() <= _maxP.y() + tolerance);
                }

                /**
                 * @brief inArea
                 * test if this object's fits fully in area
                 * @param area
                 * @return
                 */
                inline bool inArea(const Area& area) const {
                    return _minP.x() >= area._minP.x() && _minP.y() >= area._minP.y() && _maxP.x() <= area._maxP.x() && _maxP.y() <= area._maxP.y();
                }

                /**
                 * @brief overlaps
                 * returns true if any overlap is happening between the two area's, even if otherArea fits within this area
                 * @param other
                 * @return
                 */
                inline bool overlaps(const Area& otherArea) const {
                    if (otherArea._maxP.x() < _minP.x() || otherArea._minP.x() > _maxP.x() || otherArea._maxP.y() < _minP.y() || otherArea._minP.y() > _maxP.y()) {
                        return false;
                    } else {
                        return true;
                    }
                }

                /**
                 * @brief numCornersInside
                 * count the number of corners this object has in otherArea
                 * @param other
                 * @return
                 */
                inline short numCornersInside(const Area& otherArea) const  {
                    short pointsInside = 0;

                    if (otherArea.inArea(_minP)) {
                        pointsInside++;
                    }

                    if (otherArea.inArea(_maxP)) {
                        pointsInside++;
                    }

                    if (otherArea.inArea(Coordinate(_minP.x(), _maxP.y()))) {
                        pointsInside++;
                    }

                    if (otherArea.inArea(Coordinate(_maxP.x(), _minP.y()))) {
                        pointsInside++;
                    }

                    return pointsInside;
                }

                /**
                 * @brief merge
                 * two area's and expand if required to largest containing area
                 * @param other
                 * @return
                 */
                inline Area merge(const Area& other) const {
                    return Area(
                               Coordinate(std::min(other.minP().x(), this->minP().x()), std::min(other.minP().y(), this->minP().y())),
                               Coordinate(std::max(other.maxP().x(), this->maxP().x()), std::max(other.maxP().y(), this->maxP().y())));
                }

                 /**
                  * @brief merge
                  * two area's and expand if required to largest containing area
                  * @param other
                  * @return
                  */
                inline Area merge(const Coordinate& other) const {
                    return Area(
                            Coordinate(std::min(other.x(), this->minP().x()), std::min(other.y(), this->minP().y())),
                            Coordinate(std::max(other.x(), this->maxP().x()), std::max(other.y(), this->maxP().y())));
                }

                /**
                 * @brief merge
                 * two area's and expand if required to largest containing area
                 * @param other
                 * @param tolerance, tolerance to detect zero size intersection
                 * @return
                 */
                inline Area intersection(const Area& other, double tolerance = 0.) const {
                    Area ret(
                        Coordinate(std::max(other.minP().x(), this->minP().x()), std::max(other.minP().y(), this->minP().y())),
                        Coordinate(std::min(other.maxP().x(), this->maxP().x()), std::min(other.maxP().y(), this->maxP().y())));

                    if (ret.width() < tolerance || ret.height() < tolerance) {
                        return Area();
                    }

                    return ret;
                }

                /**
                 * @brief top
                 * vector of this area
                 * @return
                 */
                inline Vector top() const {
                    return Vector(Coordinate(_minP.x(), _maxP.y()), Coordinate(_maxP.x(), _maxP.y()));
                }

                /**
                 * @brief left
                 * vector for this area
                 * @return
                 */
                inline Vector left() const {
                    return Vector(Coordinate(_minP.x(), _minP.y()), Coordinate(_minP.x(), _maxP.y()));
                }

                /**
                 * @brief bottom
                 * vector of this area
                 * @return
                 */
                inline Vector bottom() const {
                    return Vector(Coordinate(_minP.x(), _minP.y()), Coordinate(_maxP.x(), _minP.y()));
                }

                /**
                 * Increase the area on each side by increaseBy
                 */
                inline Area increaseBy (double increaseBy) const {
                    return Area(geo::Coordinate(_minP.x() - increaseBy, _minP.y() - increaseBy, _minP.z()),
                                geo::Coordinate(_maxP.x() + increaseBy, _maxP.y() + increaseBy, _maxP.z()));
                }
                /**
                 * @brief checks for the equality of Area
                 * @param Area
                 * @return bool equality
                 */
                inline bool operator==(const Area& ar) const {
                    return this->minP() == ar.minP() && this->maxP() == ar.maxP();
                }


            /**
                 * @brief right
                 * vector of this area
                 * @return
                 */
                inline Vector right() const {
                    return Vector(Coordinate(_maxP.x(), _minP.y()), Coordinate(_maxP.x(), _maxP.y()));
                }

                virtual void accept(GeoEntityVisitor &v) const override { v.visit(*this); }

            private:
                friend std::ostream& operator<<(std::ostream& os, const Area& area) {
                    os << "Area(" << area.minP() << " " << area.maxP() << ")";
                    return os;
                }

            private:
                Coordinate _minP;
                Coordinate _maxP;
        };
    }
}
