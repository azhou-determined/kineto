/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "ActivityProfilerInterface.h"

#include <memory>
#include <set>
#include <vector>

#include "ActivityType.h"
#include "TraceActivity.h"

namespace libkineto {
  class CpuTraceBuffer;
}

namespace KINETO_NAMESPACE {

using namespace libkineto;

class ActivityProfilerController;
class Config;
class ConfigLoader;

class ActivityProfilerProxy : public ActivityProfilerInterface {

 public:
  ActivityProfilerProxy(bool cpuOnly, ConfigLoader& configLoader);
  ~ActivityProfilerProxy() override;

  void init() override;
  bool isInitialized() override {
    return controller_ != nullptr;
  }

  bool isActive() override;

  void recordThreadInfo() override;

  void scheduleTrace(const std::string& configStr) override;
  void scheduleTrace(const Config& config);

  void prepareTrace(const std::set<ActivityType>& activityTypes) override;
  void startTrace() override;
  std::unique_ptr<ActivityTraceInterface> stopTrace() override;

  void pushCorrelationId(uint64_t id) override;
  void popCorrelationId() override;

  void pushUserCorrelationId(uint64_t id) override;
  void popUserCorrelationId() override;

  void transferCpuTrace(
     std::unique_ptr<CpuTraceBuffer> traceBuffer) override;

  bool enableForRegion(const std::string& match) override;

  void addMetadata(const std::string& key, const std::string& value) override;

 private:
  bool cpuOnly_{true};
  ConfigLoader& configLoader_;
  ActivityProfilerController* controller_{nullptr};
};

} // namespace libkineto
