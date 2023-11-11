// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/fuchsia/startup_context.h"

#include <tuple>
#include <utility>

#include <fuchsia/io/cpp/fidl.h>
#include <lib/sys/cpp/outgoing_directory.h>
#include <lib/sys/cpp/service_directory.h>

#include "base/check.h"
#include "base/check_op.h"
#include "base/fuchsia/file_utils.h"
#include "base/fuchsia/fuchsia_logging.h"
#include "base/logging.h"

namespace base {

StartupContext::StartupContext(
    fuchsia::component::runner::ComponentStartInfo start_info) {
  std::unique_ptr<sys::ServiceDirectory> incoming_services;

  // Component manager generates |flat_namespace|, so things are horribly broken
  // if |flat_namespace| is malformed.
  CHECK(start_info.has_ns());

  // Find the /svc directory and wrap it into a sys::ServiceDirectory.
  auto& namespace_entries = *start_info.mutable_ns();
  for (auto& entry : namespace_entries) {
    CHECK(entry.has_path() && entry.has_directory());
    if (entry.path() == kServiceDirectoryPath) {
      incoming_services = std::make_unique<sys::ServiceDirectory>(
          std::move(*entry.mutable_directory()));
      break;
    }
  }

  // If there is no service-directory in the namespace then `incoming_services`
  // may be null, in which case `svc()` will be null.
  component_context_ =
      std::make_unique<sys::ComponentContext>(std::move(incoming_services));
  if (start_info.has_outgoing_dir()) {
    outgoing_directory_request_ = std::move(*start_info.mutable_outgoing_dir());
  }
}

StartupContext::~StartupContext() = default;

StartupContext::StartupContext(fuchsia::sys::StartupInfo startup_info) {
  std::unique_ptr<sys::ServiceDirectory> incoming_services;

  // Component manager generates |flat_namespace|, so things are horribly broken
  // if |flat_namespace| is malformed.
  CHECK_EQ(startup_info.flat_namespace.directories.size(),
           startup_info.flat_namespace.paths.size());

  // Find the /svc directory and wrap it into a sys::ServiceDirectory.
  for (size_t i = 0; i < startup_info.flat_namespace.paths.size(); ++i) {
    if (startup_info.flat_namespace.paths[i] == kServiceDirectoryPath) {
      incoming_services = std::make_unique<sys::ServiceDirectory>(
          std::move(startup_info.flat_namespace.directories[i]));
      break;
    }
  }

  if (!incoming_services) {
    LOG(WARNING) << "Component started without a service directory";

    // Create a dummy ServiceDirectory with a channel that's not
    // connected on the other end.
    fidl::InterfaceHandle<fuchsia::io::Directory> dummy_directory;
    std::ignore = dummy_directory.NewRequest();
    incoming_services =
        std::make_unique<sys::ServiceDirectory>(std::move(dummy_directory));
  }

  component_context_ =
      std::make_unique<sys::ComponentContext>(std::move(incoming_services));
  outgoing_directory_request_ =
      std::move(startup_info.launch_info.directory_request);
}

void StartupContext::ServeOutgoingDirectory() {
  DCHECK(outgoing_directory_request_);
  component_context_->outgoing()->Serve(std::move(outgoing_directory_request_));
}

}  // namespace base
