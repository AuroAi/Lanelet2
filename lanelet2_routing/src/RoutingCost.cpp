#include "RoutingCost.h"
#include <lanelet2_core/geometry/Lanelet.h>
#include <lanelet2_core/primitives/LaneletOrArea.h>
#include <lanelet2_core/utility/Units.h>
#include <boost/geometry/algorithms/perimeter.hpp>

namespace lanelet {
namespace routing {
namespace {
Velocity speedLimit(const TrafficRules& trafficRules, const ConstLaneletOrArea& la) {
  auto limit = la.applyVisitor([&](auto& la) { return trafficRules.speedLimit(la); });
  if (std::isinf(limit.speedLimit.value())) {
    throw lanelet::InvalidInputError("Infinite speed limit returned by trafficRules object");
  }
  return limit.speedLimit;
}
}  // namespace

double RoutingCostTravelTime::travelTime(const TrafficRules& trafficRules, const ConstLanelet& ll) const {
  auto limit = speedLimit(trafficRules, ll);
  return units::SecondQuantity(geometry::approximatedLength2d(ll) * units::Meter() / limit).value();
}

double RoutingCostTravelTime::travelTime(const TrafficRules& trafficRules, const ConstArea& ar) const {
  auto limit = speedLimit(trafficRules, ar);
  auto diameter = boost::geometry::perimeter(utils::to2D(ar.outerBoundPolygon()));
  return units::SecondQuantity(diameter * units::Meter() / limit).value();
}

double RoutingCostDistance::length(const ConstLanelet& ll) const { return geometry::approximatedLength2d(ll); }

double RoutingCostDistance::length(const ConstArea& ar) const {
  return boost::geometry::perimeter(utils::to2D(ar.outerBoundPolygon()));
}
}  // namespace routing
}  // namespace lanelet
