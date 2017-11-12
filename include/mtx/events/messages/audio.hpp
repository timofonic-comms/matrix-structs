#pragma once

#include <json.hpp>
#include <string>

#include "../common.hpp"

using json = nlohmann::json;

namespace common = mtx::common;

namespace mtx {
namespace events {
namespace msg {

struct Audio
{
        // A description of the audio or some kind of content description
        // for accessibility.
        std::string body;
        // Must be 'm.audio'.
        std::string msgtype;
        // The matrix URL of the audio clip.
        std::string url;
        // Metadata for the audio clip referred to in url.
        common::AudioInfo info;
};

void
from_json(const json &obj, Audio &content)
{
        content.body    = obj.at("body").get<std::string>();
        content.msgtype = obj.at("msgtype").get<std::string>();
        content.url     = obj.at("url").get<std::string>();

        if (obj.find("info") != obj.end())
                content.info = obj.at("info").get<common::AudioInfo>();
}

void
to_json(json &obj, const Audio &content)
{
        obj["msgtype"] = "m.audio";
        obj["body"]    = content.body;
        obj["url"]     = content.url;
        obj["info"]    = content.info;
}

} // namespace msg
} // namespace events
} // namespace mtx
