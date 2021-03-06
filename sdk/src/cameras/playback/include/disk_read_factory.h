// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#pragma once
#include <memory>
#include "file/file.h"
#include "linux/disk_read_linux.h"
#include "windows/disk_read_windows.h"
#include "rs/utils/log_utils.h"

namespace rs
{
    namespace playback
    {
        class disk_read_factory
        {

        public:
            static rs::core::status create_disk_read(const char *file_name, std::unique_ptr<disk_read_interface> &disk_read)
            {
                auto file_ = std::unique_ptr<rs::core::file>(new rs::core::file());

                auto status = file_->open(file_name, rs::core::open_file_option::read);
                if (status != rs::core::status_no_error) return status;

                /* Get the file header */
                file_->set_position(0, rs::core::move_method::begin);

                uint32_t nbytesRead;
                int32_t file_type_id;
                file_->read_bytes(&file_type_id, sizeof(file_type_id), nbytesRead);

                if (file_type_id == UID('R', 'S', 'L', 'X'))
                {
                    LOG_INFO("create disk read for Linux file format")
                    disk_read = std::unique_ptr<disk_read_interface>(new disk_read_linux(file_name));
                    return disk_read->init();
                }

                if (file_type_id == UID('R', 'S', 'C', 'F'))
                {
                    LOG_INFO("create disk read for Windows file format")
                    disk_read = std::unique_ptr<disk_read_interface>(new disk_read_windows(file_name));
                    return disk_read->init();
                }
                LOG_ERROR("failed to create disk read")
                return rs::core::status_file_read_failed;
            }
        };
    }
}
