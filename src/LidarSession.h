#ifndef LIDAR_SESSION_H
#define LIDAR_SESSION_H

#include <vector>
#include "pepperl_fuchs_r2000/r2000_driver.h"

/**
 * LidarSession is a singleton object serving as an interface to the
 * Pepperl+Fuchs lidar sensor.  It manages a TCP-based connection with the
 * sensor behind the scenes.
 */
class LidarSession
{
public:

	/**
	 * A type to represent a sampling of points in current plane.
	 */
	using lidar_slice = std::vector<std::pair<double, int>>;

	/**
	 * Spins up the Lidar session, so that it is operating according to its
	 * configured parameters.
	 */
	static LidarSession & start_session ();

	/**
	 * Spins down the Lidar system, so that it enters an idling state.
	 */
	void stop_session ();

	/**
	 * Returns true if and only if the LidarSession has entered an
	 * error state.
	 */
	bool error () const;

	/**
	 * Returns the distance (in millimeters) that the lidar currently
	 * measures at the given angle (in degrees).
	 */
	int get_distance (double angle);

	/**
	 * Returns a 2D slice of the Lidar's environment, in the form of a
	 * vector of angle-distance pairs.
	 */
	std::vector<std::pair<double, int>> get_slice ();

private:
	/// Driver for the Lidar
	pepperl_fuchs::R2000Driver r2000_driver;

	/// Flag to indicate that the session has been started but not yet ended.
	bool active;

	/**
	 * Constructs an instance of a Lidar session in its idle state.
	 */
	LidarSession ();

	/**
	 * Helper method to manage the process of connecting to the Lidar.
	 */
	bool connect ();

	/**
	 * Helper method to retrieve a full scan of measurements from the Lidar.
	 */
	void get_scan (std::vector<std::pair<double, int>> & points);

	/**
	 * Helper method to spin the Lidar up into its Ready configuration.
	 */
	bool wakeup ();

	/**
	 * Helper method to spin the Lidar down to its idling configuration.
	 */
	bool sleep ();

};

#endif // LIDAR_SESSION_H