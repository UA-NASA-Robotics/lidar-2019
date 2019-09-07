#include "LidarSession.h"

///=============================================================================
/// Configuration
///=============================================================================

/*--------------------------- Idling State -----------------------------------*/

    // spin rate
    // sample rate

/*--------------------------- Ready State ------------------------------------*/

    // spin rate
    // sample rate

/*--------------------------- Connection Parameters --------------------------*/

char const * LIDAR_IP_ADDRESS = "192.168.1.3";

/*--------------------------- Slicing Parameters -----------------------------*/

double const MIN_SCAN_ANGLE = -180.0;
double const MAX_SCAN_ANGLE = 180.0;
int const NUM_SCANS_PER_SLICE = 2;

///=============================================================================
/// LidarSessoin Implementation
///=============================================================================

LidarSession &
LidarSession :: start_session ()
{
    static LidarSession lidar_session;
    lidar_session.active = true;
    lidar_session.wakeup();
    return lidar_session;
}

void
LidarSession :: stop_session ()
{
    sleep();
    active = false;
}

int
LidarSession :: get_distance (double angle)
{
    // ensure that angle is in coorect range
    while (angle > 180) angle -= 360;
    while (angle < -180) angle += 360;

    // get a full scan and then extract:
    //  - start angle
    //  - angle increment
    //  - distance values

    // get index
    int index = (angle - start_angle) / angle_increment;

    return distance_values.at(index);
}

std::vector<std::pair<double, int>> LidarSession::
LidarSession :: get_slice ()
{
    std::vector<std::pair<double, int>> points;
    for (int i = 0; i < NUM_SCANS_PER_SLICE; ++i)
        get_scan(points);
    return points;
}

LidarSession :: LidarSession ()
  : active(false)
{}

bool
LidarSession :: connect ()
{
    // TODO: This may be a good place to spin up a second thread
    //       in order to implement a timeout feature.  (I don't want
    //       to wait more than N seconds for a connection.)
    bool connected = r2000_driver.connect(LIDAR_IP_ADDRESS);
    return connected;
}

void
LidarSession :: get_scan (std::vector<std::pair<double, int>> & points)
{
    // 1) start capturing data
    // 2) conduct a full scan, adding the points to the given vector
}

bool
LidarSession :: wakeup ()
{
    connect();
    // TODO: set the parameters
}

bool
LidarSession :: sleep ()
{
    connect();
    // TODO: set the parameters (for lower power consumption)
}
