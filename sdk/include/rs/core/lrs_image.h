// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#pragma once
#include <librealsense/rs.hpp>
#include "image_base.h"

namespace rs
{
    namespace core
    {
        /**
         * @brief The lrs_image class
         * implements the sdk image interface for a frame defined by librealsense.
         * see complete documantation in the interface declaration.
         */
        class lrs_image : public image_base
        {
        public:
            lrs_image(const lrs_image &) = delete;
            lrs_image & operator = (const lrs_image &) = delete;

            lrs_image(rs::frame &frame,
                      image_interface::flag flags,
                      rs::utils::smart_ptr<metadata_interface> metadata);
            image_info query_info(void) const override;
            uint64_t query_time_stamp(void) const override;
            flag query_flags(void) const override;
            const void * query_data(void) const override;
            stream_type query_stream_type() const override;
        private:
            rs::frame m_frame;
            image_interface::flag m_flags;
        };
    }
}
