#include "catch.hpp"
#include <limits>
#include <dis7/utils/ConversionUtils.h>

TEST_CASE("ECEF to LLA conversion", "[ConversionUtils]") {
  double lat = 0.0;
  double lon = 0.0;
  double alt = 0.0;
  bool ok = DIS::ConversionUtils::ecefToLla(6378137.0, 0.0, 0.0, lat, lon, alt);
  REQUIRE(ok);
  REQUIRE(lat == Approx(0.0).margin(1e-6));
  REQUIRE(lon == Approx(0.0).margin(1e-6));
  REQUIRE(alt == Approx(0.0).margin(1e-3));
}

TEST_CASE("ECEF to LLA invalid input", "[ConversionUtils]") {
  double lat = 1.0;
  double lon = 1.0;
  double alt = 1.0;
  bool ok = DIS::ConversionUtils::ecefToLla(std::numeric_limits<double>::quiet_NaN(), 0.0, 0.0, lat, lon, alt);
  REQUIRE_FALSE(ok);
  REQUIRE(lat == 0.0);
  REQUIRE(lon == 0.0);
  REQUIRE(alt == 0.0);
}
