/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 **/

#ifndef MODULES_PLANNING_TASKS_DP_ST_SPEED_DP_ST_COST_H_
#define MODULES_PLANNING_TASKS_DP_ST_SPEED_DP_ST_COST_H_

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "modules/common/proto/pnc_point.pb.h"
#include "modules/planning/proto/dp_st_speed_config.pb.h"

#include "modules/planning/common/path_obstacle.h"
#include "modules/planning/common/speed/st_boundary.h"
#include "modules/planning/common/speed/st_point.h"
#include "modules/planning/tasks/dp_st_speed/st_graph_point.h"

namespace apollo {
namespace planning {

class DpStCost {
 public:
  explicit DpStCost(const DpStSpeedConfig& dp_st_speed_config,
                    const std::vector<const PathObstacle*>& obstacles,
                    const common::TrajectoryPoint& init_point);

  double GetObstacleCost(const StGraphPoint& point);

  double GetReferenceCost(const STPoint& point,
                          const STPoint& reference_point) const;

  double GetSpeedCost(const STPoint& first, const STPoint& second,
                      const double speed_limit) const;

  double GetAccelCostByTwoPoints(const double pre_speed, const STPoint& first,
                                 const STPoint& second);
  double GetAccelCostByThreePoints(const STPoint& first, const STPoint& second,
                                   const STPoint& third);

  double GetJerkCostByTwoPoints(const double pre_speed, const double pre_acc,
                                const STPoint& pre_point,
                                const STPoint& curr_point);
  double GetJerkCostByThreePoints(const double first_speed,
                                  const STPoint& first_point,
                                  const STPoint& second_point,
                                  const STPoint& third_point);

  double GetJerkCostByFourPoints(const STPoint& first, const STPoint& second,
                                 const STPoint& third, const STPoint& fourth);

 private:
  double GetAccelCost(const double accel);
  double JerkCost(const double jerk);

  const DpStSpeedConfig& config_;
  const std::vector<const PathObstacle*>& obstacles_;
  const common::TrajectoryPoint& init_point_;
  double unit_s_ = 0.0;
  double unit_t_ = 0.0;
  double unit_v_ = 0.0;

  std::unordered_map<std::string, std::pair<double, double>>
      boundary_range_map_;
  std::unordered_map<int, double> accel_cost_map_;
  std::unordered_map<int, double> jerk_cost_map_;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_TASKS_DP_ST_SPEED_DP_ST_COST_H_
