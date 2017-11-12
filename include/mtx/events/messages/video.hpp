#pragma once

#include <json.hpp>
#include <string>

#include "../common.hpp"

using json = nlohmann::json;

namespace common = mtx::common;

namespace mtx {
namespace events {
namespace msg {

struct Video
{
        // A description of the video or some kind of content description
        // for accessibility.
        std::string body;
        // Must be 'm.video'.
        std::string msgtype;
        // The matrix URL of the video clip.
        std::string url;
        // Metadata for the video clip referred to in url.
        common::VideoInfo info;
};

void
from_json(const json &obj, Video &content)
{
        content.body    = obj.at("body").get<std::string>();
        content.msgtype = obj.at("msgtype").get<std::string>();
        content.url     = obj.at("url").get<std::string>();

        if (obj.find("info") != obj.end())
                content.info = obj.at("info").get<common::VideoInfo>();
}

void
to_json(json &obj, const Video &content)
{
        obj["msgtype"] = "m.video";
        obj["body"]    = content.body;
        obj["url"]     = content.url;
        obj["info"]    = content.info;
}

} // namespace msg
} // namespace events
} // namespace mtx
