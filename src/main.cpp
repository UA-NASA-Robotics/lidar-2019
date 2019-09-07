#include <iostream>
#include "pepperl_fuchs_r2000/r2000_driver.h"

const char * LIDAR_IP_ADDRESS = "192.168.1.3";

int main ()
{
	pepperl_fuchs::R2000Driver lidar;

	// attempt to connect to lidar
	if (!lidar.connect(LIDAR_IP_ADDRESS, 80))
	{
		std::cout << "Failed to connect to lidar (" << LIDAR_IP_ADDRESS << ")\n";
		return 1;
	}

	// configure the lidar
	lidar.setScanFrequency(35);
	lidar.setSamplesPerScan(360);

	// display current settings
	std::cout << "Current Settings:\n";
	for (const auto & param : lidar.getParameters())
		std::cout << param.first << " : " << param.second << '\n';

	// attempt to start capturing
	if (!lidar.startCapturingTCP())
	{
		std::cout << "Failed to start capturing from lidar.\n";
		return 1;
	}

	// display the raw data
	while(true)
	{
		auto scan = lidar.getFullScan();
		std::cout << '\n';
		std::cout << "Size of \"distance_data\": " << scan.distance_data.size() << '\n';
		std::cout << "Size of \"amplitude_data\": " << scan.amplitude_data.size() << '\n';
		std::cout << "Size of \"headers\": " << scan.headers.size() << '\n';

		std::cout << scan.headers.at(0).first_angle / 10000.0 << '\n';

		std::int32_t first_angle = scan.headers.at(0).first_angle / 10000.0;
		std::int32_t angular_increment = scan.headers.at(0).angular_increment / 10000.0;
		for (int i = 0; i < scan.distance_data.size(); ++i)
		{
			double angle = first_angle + i * angular_increment;
			double distance = scan.distance_data.at(i);
			std::cout << angle << ' ' << distance << '\n';
		}
	}

	// stop capturing data
	lidar.stopCapturing();

	return 0;
}