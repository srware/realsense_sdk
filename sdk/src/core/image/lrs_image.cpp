// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#include "rs/core/lrs_image.h"
#include "rs/utils/librealsense_conversion_utils.h"

using namespace rs::utils;

namespace rs
{
    namespace core
    {
        lrs_image::lrs_image(rs::frame &frame,
                             image_interface::flag flags,
                             smart_ptr<metadata_interface> metadata)
            : image_base(metadata), m_flags(flags)
        {
            m_frame.swap(frame);
        }

        image_info lrs_image::query_info() const
        {
            image_info info;
            info.format = utils::convert_pixel_format(m_frame.get_format());
            info.height = m_frame.get_height();
            info.width = m_frame.get_width();
            info.pitch = m_frame.get_stride();
            return info;
        }

        uint64_t lrs_image::query_time_stamp() const
        {
            return static_cast<uint64_t>(m_frame.get_timestamp());
        }

        image_interface::flag lrs_image::query_flags() const
        {
            return m_flags;
        }

        const void * lrs_image::query_data() const
        {
            return m_frame.get_data();
        }

        stream_type lrs_image::query_stream_type() const
        {
            //the frame const cast can be remove if librealsense made get_stream_type const
            return utils::convert_stream_type(const_cast<rs::frame*>(&m_frame)->get_stream_type());
        }
    }
}


