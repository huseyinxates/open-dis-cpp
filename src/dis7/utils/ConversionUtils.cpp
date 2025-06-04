#include "ConversionUtils.h"
#include <cmath>

namespace DIS {

double ConversionUtils::getOrientationFromEuler(double lat, double lon, double psi, double theta)
{
    double sinlat = sin(lat);
    double sinlon = sin(lon);
    double coslon = cos(lon);
    double coslat = cos(lat);
    double sinsin = sinlat * sinlon;

    double cosTheta = cos(theta);
    double cosPsi = cos(psi);
    double sinPsi = sin(psi);
    double sinTheta = sin(theta);

    double cosThetaCosPsi = cosTheta * cosPsi;
    double cosThetaSinPsi = cosTheta * sinPsi;
    double sincos = sinlat * coslon;

    double b11 = -sinlon * cosThetaCosPsi + coslon * cosThetaSinPsi;
    double b12 = -sincos * cosThetaCosPsi - sinsin * cosThetaSinPsi - coslat * sinTheta;

    return radToDeg(atan2(b11, b12)); //range is -pi to pi
}

double ConversionUtils::getPitchFromEuler(double lat, double lon, double psi, double theta)
{
    double sinlat = sin(lat);
    double sinlon = sin(lon);
    double coslon = cos(lon);
    double coslat = cos(lat);
    double cosLatCosLon = coslat * coslon;
    double cosLatSinLon = coslat * sinlon;

    double cosTheta = cos(theta);
    double cosPsi = cos(psi);
    double sinPsi = sin(psi);
    double sinTheta = sin(theta);

    return radToDeg(asin(cosLatCosLon * cosTheta * cosPsi + cosLatSinLon * cosTheta * sinPsi
                         - sinlat * sinTheta));
}

double ConversionUtils::getRollFromEuler(double lat, double lon, double psi, double theta, double phi)
{
    double sinlat = sin(lat);
    double sinlon = sin(lon);
    double coslon = cos(lon);
    double coslat = cos(lat);
    double cosLatCosLon = coslat * coslon;
    double cosLatSinLon = coslat * sinlon;

    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    double cosPsi = cos(psi);
    double sinPsi = sin(psi);
    double sinPhi = sin(phi);
    double cosPhi = cos(phi);

    double sinPhiSinTheta = sinPhi * sinTheta;
    double cosPhiSinTheta = cosPhi * sinTheta;

    double b23 = cosLatCosLon * (-cosPhi * sinPsi + sinPhiSinTheta * cosPsi)
                 + cosLatSinLon * (cosPhi * cosPsi + sinPhiSinTheta * sinPsi)
                 + sinlat * (sinPhi * cosTheta);

    double b33 = cosLatCosLon * (sinPhi * sinPsi + cosPhiSinTheta * cosPsi)
                 + cosLatSinLon * (-sinPhi * cosPsi + cosPhiSinTheta * sinPsi)
                 + sinlat * (cosPhi * cosTheta);

    return radToDeg(atan2(-b23, -b33));
}

bool ConversionUtils::ecefToLla(double x, double y, double z,
                                double &lat, double &lon, double &alt)
{
    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
    {
        lat = lon = alt = 0.0;
        return false;
    }

    const double a = 6378137.0;             // WGS-84 semi-major axis
    const double e2 = 6.69437999014e-3;     // first eccentricity squared

    const double b = a * sqrt(1.0 - e2);
    const double ep = sqrt((a * a - b * b) / (b * b));

    const double p = sqrt(x * x + y * y);
    if (p < 1e-9)
    {
        lon = 0.0;
        lat = (z >= 0.0 ? PI / 2.0 : -PI / 2.0);
        alt = fabs(z) - b;
        return true;
    }

    lon = atan2(y, x);
    const double th = atan2(a * z, b * p);
    const double sin_th = sin(th);
    const double cos_th = cos(th);
    lat = atan2(z + ep * ep * b * sin_th * sin_th * sin_th,
                p - e2 * a * cos_th * cos_th * cos_th);

    const double sin_lat = sin(lat);
    const double N = a / sqrt(1.0 - e2 * sin_lat * sin_lat);
    alt = p / cos(lat) - N;

    return std::isfinite(lat) && std::isfinite(lon) && std::isfinite(alt);
}
} // namespace DIS
