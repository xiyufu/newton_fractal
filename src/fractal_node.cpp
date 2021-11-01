#include <cmath>

#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "costmap_2d/costmap_2d.h"

#include "polynomial.h"
#include "complex_point.h"


template<typename T>
size_t GetClosestRootId(const Poly<T>& p, const T& cur_point) {
  double min_dist = 1e6;
  size_t min_id = 0;
  auto roots = p.GetRoots();
  for (size_t i = 0; i < roots.size(); ++i){
    double cur_dist = Dist(roots.at(i), cur_point);
    if (cur_dist < min_dist) {
      min_dist = cur_dist;
      min_id = i;
    }
  }
  return min_id;
}

int main(int argc, char** argv) {
  int iter = 1;
  if (argc > 1) {
    iter = std::atoi(argv[1]);
  }

  ros::init(argc, argv, "fractal");

  ros::NodeHandle n;
  auto res_pub = n.advertise<nav_msgs::OccupancyGrid>("fractal_plot", 1);

  ComplexPoint a(1, 4);
  ComplexPoint b(2, 0);
  ComplexPoint c(1, -1);
  ComplexPoint d(5, 2);
  ComplexPoint e(-3, -2);

  Poly<ComplexPoint> p;
  p.AddRoot(a);
  p.AddRoot(b);
  p.AddRoot(c);
  p.AddRoot(d);
  p.AddRoot(e);

  std::vector<u_char> colors{0, 20, 40, 60, 80};

  nav_msgs::OccupancyGrid map;
  map.header.frame_id = "world";
  map.header.stamp = ros::Time::now();
  map.info.height = 1000;
  map.info.width = 1000;
  map.info.resolution = 0.01;
  map.info.origin.position.x = - static_cast<double>(map.info.height) * map.info.resolution / 2;
  map.info.origin.position.y = - static_cast<double>(map.info.width) * map.info.resolution / 2;

  costmap_2d::Costmap2D dummy_map(map.info.height, map.info.width, map.info.resolution, map.info.origin.position.x, map.info.origin.position.y);

  map.data.resize(map.info.height * map.info.width);
  for (size_t i = 0; i < map.info.height; ++i) {
    for (size_t j = 0; j < map.info.width; ++j) {
      double wx, wy;
      dummy_map.mapToWorld(i, j, wx, wy);
      ComplexPoint cur_p(wx, wy);
      for (size_t k = 0; k < iter; ++k) {
        auto p_val = p.Eval(cur_p);
        auto dp_val = p.EvalDerivate(cur_p);
        if (dp_val.abs() < 1e-6) {
          break;
        }
        cur_p = cur_p - (p_val / dp_val);
      }
      size_t min_id = GetClosestRootId(p, cur_p);
      map.data[i * map.info.width + j] = colors.at(min_id);
    }
  }

  ros::Rate loop_rate(1);
  for (size_t i = 0; i < 1; ++i) {
    res_pub.publish(map);
    loop_rate.sleep();
    ros::spinOnce();
  }
  return 0;
}